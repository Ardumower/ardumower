#include "motorcontrol.h"
#include "common.h"
#include <stdlib.h>
#include <math.h>
#include "config.h"


MotorControl::MotorControl(){
  motorSpeedMaxRpm = 18;
  motorSpeedMaxPwm = 255;

  motorLeftPID.Kp       = 0.87;    // motor wheel PID controller
  motorLeftPID.Ki       = 0.29;
  motorLeftPID.Kd       = 0.25;

/*  odometryTicksPerRevolution = 20;   // encoder ticks per one full resolution
  odometryTicksPerCm = 0.5;    // encoder ticks per cm
  odometryWheelBaseCm = 14;    // wheel-to-wheel distance (cm)
  motorLeftSwapDir = false;
  motorRightSwapDir = false;*/

  odometryTicksPerRevolution = 1060;   // encoder ticks per one full resolution
  odometryTicksPerCm = 13.49;  // encoder ticks per cm
  odometryWheelBaseCm = 36;    // wheel-to-wheel distance (cm)
  motorLeftSwapDir = true;
//  motorLeftSwapDir = false;
  motorRightSwapDir = false;
//  motorRightSwapDir = true;

  // MC33926 current:  5V / 1024 ADC counts,  525 mV per A  => 9.3 mA per ADC step
  motorSenseRightScale = 9.3;  // motor right sense scale (mA=(ADC-zero) * scale)
  motorSenseLeftScale  = 9.3;  // motor left sense scale  (mA=(ADC-zero) * scale)
  motorVoltageDC = 24.0;

  motorEfficiencyMin = 200;
}


void MotorControl::setup(){
  Console.println(F("MotorControl::setup"));
  printCSV(true);
  motion = MOTION_STOP;
  enableSpeedControl = enableStallDetection = enableErrorDetection = true;
  motorLeftPWMCurr = motorRightPWMCurr = 0;
  lastOdometryTime = lastMotorControlTime = lastMotorCurrentTime = lastMotorRunTime = nextMotorPrintTime = 0;
  odometryLeftTicksZeroCounter = odometryRightTicksZeroCounter = 0;
  motorLeftError = motorRightError = false;
  motorLeftStalled = motorRightStalled = false;
  leftRightCompensation = 0;

  setSpeedPWM(0, 0);
}

void MotorControl::resetStalled(){
  motorLeftStalled = motorRightStalled = false;
  Console.println(F("STALL RESET"));
}

// motor driver
void MotorControl::setDriverPWM(int leftMotorPWM, int rightMotorPWM){
}

void MotorControl::checkFault(){
}

void MotorControl::resetFault(){
}

void MotorControl::run(){
  unsigned long TaC = millis() - lastMotorRunTime;    // sampling time in millis
  if (TaC < 50) return;
  lastMotorRunTime = millis();

  readOdometry();
  if (enableSpeedControl) {
    switch (motion){
      case MOTION_SPEED:
        break;
      case MOTION_LINE_SPEED:
        break;
      case MOTION_LINE_DISTANCE:
        distanceToTargetCm = abs(odometryDistanceCmCurr - odometryDistanceCmSet);
        if (distanceToTargetCm < 20.0) {
          Console.println(F("reached destination"));
          motorLeftSpeedRpmSet = motorRightSpeedRpmSet = 0;
          motion = MOTION_STOP;
        }
        /*if (odometryDistanceCmCurr > odometryDistanceCmSet) {
          Console.println(F("reached destination (overshoot)"));
          motorLeftSpeedRpmSet = motorRightSpeedRpmSet = 0;
          motion = MOTION_STOP;
        }*/
        break;
      case MOTION_ROTATE_ANGLE:
        angleToTargetRad = abs(distancePI(odometryThetaRadCurr, odometryThetaRadSet));
        if (angleToTargetRad < M_PI/4){
          Console.println(F("reached angle"));
          motorLeftSpeedRpmSet = motorRightSpeedRpmSet = 0;
          motion = MOTION_STOP;
        }
        break;
    }
    speedControl();
  }
  readCurrent();
  checkFault();
  if ( (motion != MOTION_STOP) || (motorLeftPWMCurr > 0) || (motorRightPWMCurr > 0) ) {
    if (millis() >= nextMotorPrintTime){
      nextMotorPrintTime = millis() + 500;
      print();
      Console.println("");
    }
  }
  printCSV(false);
}


void MotorControl::readOdometry(){
  unsigned long TaC = millis() - lastOdometryTime;    // sampling time in millis
  lastOdometryTime = millis();
  if (TaC > 1000) TaC = 1;
  static int lastOdoLeft = 0;
  static int lastOdoRight = 0;
  int odoLeft = odometryLeftTicks;
  int odoRight = odometryRightTicks;
  unsigned long leftTime = odometryLeftTickTime;
  unsigned long rightTime = odometryRightTickTime;
  int ticksLeft = odoLeft - lastOdoLeft;
  int ticksRight = odoRight - lastOdoRight;
  lastOdoLeft = odoLeft;
  lastOdoRight = odoRight;
  double left_cm = ((double)ticksLeft) / ((double)odometryTicksPerCm);
  double right_cm = ((double)ticksRight) / ((double)odometryTicksPerCm);
  double avg_cm  = (left_cm + right_cm) / 2.0;
  double wheel_theta = (left_cm - right_cm) / ((double)odometryWheelBaseCm);
  odometryThetaRadCurr = scalePI( odometryThetaRadCurr + wheel_theta );
  odometryDistanceCmCurr += avg_cm;
  odometryXcmCurr += avg_cm * sin(odometryThetaRadCurr);
  odometryYcmCurr += avg_cm * cos(odometryThetaRadCurr);

  float smooth = 0.0;
  if (ticksLeft != 0) {
    motorLeftRpmCurr  = motorLeftRpmCurr * smooth + (1.0-smooth) *  60.0/((double)odometryTicksPerRevolution)/ (((double)leftTime)/1000.0/1000.0);
    odometryLeftTicksZeroCounter = 0;
  } else {
    odometryLeftTicksZeroCounter++;
    //Console.println(F("LEFT TICKS ZERO"));
    if (odometryLeftTicksZeroCounter > 10) motorLeftRpmCurr = 0;     // ensures rpm gets zero
  }
  if (motorLeftPWMCurr < 0) motorLeftRpmCurr *= -1;

  if (ticksRight != 0) {
    motorRightRpmCurr  = motorRightRpmCurr * smooth + (1.0-smooth) * 60.0 / ((double)odometryTicksPerRevolution)/ (((double)rightTime)/1000.0/1000.0);
    odometryRightTicksZeroCounter = 0;
  } else {
    odometryRightTicksZeroCounter++;
    //Console.println(F("RIGHT TICKS ZERO"));
    if (odometryRightTicksZeroCounter > 10) motorRightRpmCurr = 0;   // ensures rpm gets zero
  }
  if (motorRightPWMCurr < 0) motorRightRpmCurr *= -1;

 //motorLeftRpmCurr  = double ((( ((double)ticksLeft) / ((double)odometryTicksPerRevolution)) / ((double)(TaC))) * 60000.0);
 //motorRightRpmCurr = double ((( ((double)ticksRight) / ((double)odometryTicksPerRevolution)) / ((double)(TaC))) * 60000.0);
}


void MotorControl::speedControl(){
  unsigned long TaC = millis() - lastMotorControlTime;    // sampling time in millis
  if (TaC < 50) return;
  lastMotorControlTime = millis();
  if (TaC > 500) TaC = 1;
  //double TaS = ((double)TaC) / 1000.0;
  motorLeftPID.w = motorLeftSpeedRpmSet;               // SET
  motorRightPID.w = motorRightSpeedRpmSet;               // SET
  float RLdiff = (abs(motorLeftRpmCurr) - abs(motorRightRpmCurr)) / motorLeftRpmCurr;

  switch (motion){
    case MOTION_LINE_SPEED:
    case MOTION_LINE_DISTANCE:
      if ( RLdiff > 0.7 )
        motorLeftPID.w = motorRightRpmCurr;
      else if (RLdiff < -0.7)
        motorRightPID.w = motorLeftRpmCurr;
      break;
    case MOTION_ROTATE_ANGLE:
      if ( RLdiff > 0.2 )
        motorLeftPID.w = -motorRightRpmCurr;
      else if (RLdiff < -0.2 )
        motorRightPID.w = -motorLeftRpmCurr;
      break;
  }

  motorLeftPID.x = motorLeftRpmCurr;                 // CURRENT
//   motorLeftPID.w = motorLeftSpeedRpmSet;               // SET
  motorLeftPID.y_min = -motorSpeedMaxPwm;        // CONTROL-MIN
  motorLeftPID.y_max = motorSpeedMaxPwm;     // CONTROL-MAX
  motorLeftPID.max_output = motorSpeedMaxPwm;    // LIMIT
  motorLeftPID.compute();
  int leftSpeed = motorLeftPWMCurr + motorLeftPID.y;
  if (motorLeftSpeedRpmSet >= 0) leftSpeed = min( max(0, leftSpeed), motorSpeedMaxPwm);
  if (motorLeftSpeedRpmSet < 0) leftSpeed = max(-motorSpeedMaxPwm, min(0, leftSpeed));

  motorRightPID.Kp = motorLeftPID.Kp;
  motorRightPID.Ki = motorLeftPID.Ki;
  motorRightPID.Kd = motorLeftPID.Kd;
  motorRightPID.x = motorRightRpmCurr;               // IST
//  motorRightPID.w = motorRightSpeedRpmSet;             // SOLL
  motorRightPID.y_min = -motorSpeedMaxPwm;       // Regel-MIN
  motorRightPID.y_max = motorSpeedMaxPwm;        // Regel-MAX
  motorRightPID.max_output = motorSpeedMaxPwm;   // Begrenzung
  motorRightPID.compute();
  int rightSpeed = motorRightPWMCurr + motorRightPID.y;
  if (motorRightSpeedRpmSet >= 0) rightSpeed = min( max(0, rightSpeed), motorSpeedMaxPwm);
  if (motorRightSpeedRpmSet < 0) rightSpeed = max(-motorSpeedMaxPwm, min(0, rightSpeed));

  if ( (abs(motorLeftPID.x)  < 2) && (motorLeftPID.w  == 0) ) leftSpeed = 0; // ensures PWM is really zero
  if ( (abs(motorRightPID.x) < 2) && (motorRightPID.w == 0) ) rightSpeed = 0; // ensures PWM is really zero
  setSpeedPWM( leftSpeed, rightSpeed );
}


// forward speed: 0..+255
// reverse speed: 0..-255
void MotorControl::setSpeedPWM(int leftPWM, int rightPWM){
  if ((motorLeftStalled) || (motorRightStalled)){
    if ((leftPWM != 0) || (rightPWM != 0)) return;
  }
  if (leftPWM == 0) motorLeftSensePower = 0;
  if (rightPWM == 0) motorRightSensePower = 0;
  motorLeftPWMCurr = leftPWM;
  motorRightPWMCurr = rightPWM;
  if (motorLeftSwapDir) leftPWM *= -1;
  if (motorRightSwapDir) rightPWM *= -1;
  setDriverPWM( max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, leftPWM)),
                max(-motorSpeedMaxPwm, min(motorSpeedMaxPwm, rightPWM)) );
}

void MotorControl::setSpeedRpm(int leftRpm, int rightRpm){
  motorLeftSpeedRpmSet = leftRpm;
  motorRightSpeedRpmSet = rightRpm;
  motorLeftSpeedRpmSet = max(-motorSpeedMaxRpm, min(motorSpeedMaxRpm, motorLeftSpeedRpmSet));
  motorRightSpeedRpmSet = max(-motorSpeedMaxRpm, min(motorSpeedMaxRpm, motorRightSpeedRpmSet));
  motion = MOTION_SPEED;
  motorRightPID.reset();
  motorLeftPID.reset();
  leftRightCompensation = 0;
}



void MotorControl::stopImmediately(){
  setSpeedPWM(0, 0);
  leftRightCompensation = 0;
  motorRightPID.reset();
  motorLeftPID.reset();
  motorLeftSpeedRpmSet = motorRightSpeedRpmSet = 0;
  motion = MOTION_STOP;
}

void MotorControl::travelLineSpeedRpm(int speedRpm){
  motorLeftSpeedRpmSet = motorRightSpeedRpmSet = speedRpm;
  leftRightCompensation = 0;
  motorRightPID.reset();
  motorLeftPID.reset();
  motion = MOTION_LINE_SPEED;
}

void MotorControl::travelLineDistance(int distanceCm, int speedRpm){
  motion = MOTION_LINE_DISTANCE;
  odometryDistanceCmSet = odometryDistanceCmCurr + distanceCm;
  leftRightCompensation = 0;
  motorRightPID.reset();
  motorLeftPID.reset();
  Console.print(F("target distance="));
  Console.println(odometryDistanceCmSet);
  if (distanceCm < 0)
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = -speedRpm;
  else
    motorLeftSpeedRpmSet = motorRightSpeedRpmSet = speedRpm;
}

void MotorControl::rotate(float angleRad, int speedRpm){
  motion = MOTION_ROTATE_ANGLE;
  odometryThetaRadSet = scalePI(odometryThetaRadCurr + angleRad);
  leftRightCompensation = 0;
  motorRightPID.reset();
  motorLeftPID.reset();
  Console.print(F("target angle="));
  Console.println(odometryThetaRadSet/M_PI*180.0);
  if (angleRad < 0){
    motorLeftSpeedRpmSet  = -speedRpm;
    motorRightSpeedRpmSet = speedRpm;
  } else {
    motorLeftSpeedRpmSet  = speedRpm;
    motorRightSpeedRpmSet = -speedRpm;
  }
}

bool MotorControl::hasStopped(){
  return ( (motion == MOTION_STOP) && (abs(motorLeftPWMCurr) < 1) && (abs(motorRightPWMCurr) < 1) && (abs(motorRightRpmCurr) < 1) && (abs(motorLeftRpmCurr) < 1)  );
}


// read motor current
void MotorControl::readCurrent(){
    unsigned long TaC = millis() - lastMotorCurrentTime;    // sampling time in millis
    lastMotorCurrentTime = millis();
    if (TaC > 500) TaC = 1;
    double TaS = ((double)TaC) / 1000.0;

    //double smooth = 0.95;
    //double smooth = 0.9;

    int lastMotorLeftSenseADC  = motorLeftSenseADC;
    int lastMotorRightSenseADC = motorRightSenseADC;

    // read current - NOTE: MC33926 datasheets says: accuracy is better than 20% from 0.5 to 6.0 A
    //motorLeftSenseADC = ADCMan.read(pinMotorLeftSense);
    //motorRightSenseADC = ADCMan.read(pinMotorRightSense);

    /*Console.print(motorLeftSenseADC);
    Console.print(",");
    Console.println(motorRightSenseADC);*/

    // compute gradient
    motorLeftSenseGradient  =  (((double)motorLeftSenseADC)  - ((double)lastMotorLeftSenseADC))  / TaS;
    motorRightSenseGradient =  (((double)motorRightSenseADC) - ((double)lastMotorRightSenseADC)) / TaS;

    // compute motor current (mA)
    //double smooth = 0.0;
    double smooth = 0.5;
    motorRightSenseCurrent = motorRightSenseCurrent * smooth + ((double)motorRightSenseADC) * motorSenseRightScale * (1.0-smooth);
    motorLeftSenseCurrent  = motorLeftSenseCurrent  * smooth + ((double)motorLeftSenseADC)  * motorSenseLeftScale  * (1.0-smooth);

    // obstacle detection via motor torque (output power)
    // NOTE: at obstacles, our motors typically do not stall - they are too powerful, and just reduce speed (rotate through the lawn)
    // http://wiki.ardumower.de/images/9/96/Wheel_motor_diagram.png
    //
    float lastMotorLeftSensePower  = motorLeftSensePower;
    float lastMotorRightSensePower = motorRightSensePower;

    // compute motor output power (W) by calculating battery voltage, pwm duty cycle and motor current
    // P_output = U_Battery * pwmDuty * I_Motor
    smooth = 0.9;
    motorRightSensePower = motorRightSensePower * smooth + (1.0-smooth) * (motorRightSenseCurrent * motorVoltageDC * ((double)abs(motorRightPWMCurr)/255.0)  /1000);
    motorLeftSensePower  = motorLeftSensePower  * smooth + (1.0-smooth) * (motorLeftSenseCurrent  * motorVoltageDC * ((double)abs(motorLeftPWMCurr) /255.0)  /1000);

    // Ist es nicht aussagekraeftiger ueber die Beschleunigung?
    // Mit der PWM und der Odometrie gibst du eine soll Drehzahl = Soll Geschwindigkeit vor.
    // Wird die in einem bestimmten Rahmen nicht erreicht und dein Strom geht hoch hast du ein Hindernis.

    // compute efficiency (output rotation/input power)
    //smooth = 0.95;
    smooth = 0.9;
    motorLeftEfficiency  = motorLeftEfficiency  * smooth + (abs(motorLeftRpmCurr) / max(0.01f, fabs(motorLeftSensePower))   * 100.0) * (1.0-smooth);
    motorRightEfficiency = motorRightEfficiency * smooth + (abs(motorRightRpmCurr) / max(0.01f, fabs(motorRightSensePower)) * 100.0) * (1.0-smooth);

    // tracktion control
    // idea:     sigma_b = (Vf - Vu) / Vf    (break tracktion)
    //           sigma_a = (Vu - Vf) / Vu    (acceleration tracktion)
    // Vf: vehicle velocity
    // Vu: tire velocity

    if (enableStallDetection) {
      if (!motorLeftStalled){
       if ( (abs(motorLeftPWMCurr) > 0) && (motorLeftSensePower > 1) && (motorLeftEfficiency < motorEfficiencyMin)  ) {
         print();
         Console.print(F("  LEFT STALL"));
         Console.println();
         motorLeftStalled = true;
         stopImmediately();
       }
      }
      if (!motorRightStalled){
       if ( (abs(motorRightPWMCurr) > 0) && (motorRightSensePower > 1) && (motorRightEfficiency < motorEfficiencyMin) ) {
         print();
         Console.print(F("  RIGHT STALL"));
         Console.println();
         motorRightStalled = true;
         stopImmediately();
       }
      }
    }
}

void MotorControl::printCSV(bool includeHeader){
    if (includeHeader) Console.println(F("millis,tickL,tickR,th,dist,setL,setR,curL,curR,errL,errR,pwmL,pwmR,maL,maR,gmaL,gmaR,pL,pR,effL,effR"));
    /*Console.print(millis());
    Console.print(",");
    Console.print(odometryLeftTicks);
    Console.print(",");
    Console.print(odometryRightTicks);
    Console.print(",");
    Console.print(odometryThetaRadCurr/PI*180.0);
    Console.print(",");
    Console.print(odometryDistanceCmCurr, 1);
    Console.print(",");
    Console.print(motorLeftSpeedRpmSet);
    Console.print(",");
    Console.print(motorRightSpeedRpmSet);
    Console.print(",");
    Console.print(motorLeftRpmCurr, 1);
    Console.print(",");
    Console.print(motorRightRpmCurr, 1);
    Console.print(",");    */
    Console.print(motorLeftPID.eold, 1);
    Console.print(",");
    Console.print(motorRightPID.eold, 1);
    Console.print(",");
    Console.print(motorLeftPID.Kp);
    Console.print(F(","));
    Console.print(motorLeftPID.Ki);
    Console.print(F(","));
    Console.print(motorLeftPID.Kd);
    Console.print(",");
    Console.print(leftRightCompensation);

    /*Console.print(",");
    Console.print(motorLeftPWMCurr, 0);
    Console.print(",");
    Console.print(motorRightPWMCurr, 0);
    Console.print(",");
    Console.print(motorLeftSenseCurrent, 0);
    Console.print(",");
    Console.print(motorRightSenseCurrent, 0);
    Console.print(",");
    Console.print(motorLeftSenseGradient, 0);
    Console.print(",");
    Console.print(motorRightSenseGradient, 0);
    Console.print(",");
    Console.print(motorLeftSensePower, 1);
    Console.print(",");
    Console.print(motorRightSensePower, 1);
    Console.print(",");
    Console.print(motorLeftEfficiency, 0);
    Console.print(",");
    Console.print(motorRightEfficiency, 0);        */
    Console.println();
}


void MotorControl::print(){
    return;
    Console.print(F(" ticks:"));
    Console.print(odometryLeftTicks);
    Console.print(",");
    Console.print(odometryRightTicks);
    Console.print(F("  th,dist:"));
    Console.print(odometryThetaRadCurr/M_PI*180.0);
    Console.print(",");
    Console.print(odometryDistanceCmCurr, 1);
    Console.print(F(" ## "));
    Console.print(angleToTargetRad/M_PI*180.0, 1);
    Console.print(",");
    Console.print(distanceToTargetCm, 1);
    Console.print(F("  set:"));
    Console.print(motorLeftSpeedRpmSet);
    Console.print(",");
    Console.print(motorRightSpeedRpmSet);
    Console.print(F("  cur:"));
    Console.print(motorLeftRpmCurr, 1);
    Console.print(",");
    Console.print(motorRightRpmCurr, 1);
    Console.print(F("  err:"));
    Console.print(motorLeftPID.eold, 1);
    Console.print(",");
    Console.print(motorRightPID.eold, 1);
    Console.print(F("  pwm:"));
    Console.print(motorLeftPWMCurr, 0);
    Console.print(",");
    Console.print(motorRightPWMCurr, 0);
    Console.print(F("  mA:"));
    Console.print(motorLeftSenseCurrent, 0);
    Console.print(",");
    Console.print(motorRightSenseCurrent, 0);
    Console.print(F(" ## "));
    Console.print(motorLeftSenseGradient, 0);
    Console.print(",");
    Console.print(motorRightSenseGradient, 0);
    Console.print(F("  P:"));
    Console.print(motorLeftSensePower, 1);
    Console.print(",");
    Console.print(motorRightSensePower, 1);
    Console.print(F("  eff:"));
    Console.print(motorLeftEfficiency, 0);
    Console.print(",");
    Console.print(motorRightEfficiency, 0);
    Console.print(F("  pid:"));
    Console.print(motorLeftPID.Kp);
    Console.print(F(","));
    Console.print(motorLeftPID.Ki);
    Console.print(F(","));
    Console.print(motorLeftPID.Kd);
    Console.print(F("  lrc:"));
    Console.print(leftRightCompensation);
}



