/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  Copyright (c) 2014 by Maxime Carpentieri
  
  Private-use only! (you need to ask for a commercial-use)
 
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
  
  Private-use only! (you need to ask for a commercial-use)
*/

// Android remote control (pfod App)
// For a detailed specification of the pfodApp protocol, please visit:  http://www.forward.com.au/pfod/

#include "pfod.h"
#include "robot.h"
#include "adcman.h"
#include "imu.h"
#include "perimeter.h"

RemoteControl::RemoteControl(){
  pfodCmdComplete = false;
  pfodCmd = "";
  pfodState = PFOD_OFF;
  testmode = 0;
  nextPlotTime = 0;  
  perimeterCaptureIdx = 0;  
}

void RemoteControl::setRobot(Robot *aRobot){
  this->robot = aRobot;
}

void RemoteControl::initSerial(int baudrate){
  Bluetooth.begin(baudrate);   // pfod app  
}

float RemoteControl::stringToFloat(String &s){
  float v;
  char tmp[20];  
  s.toCharArray(tmp, sizeof(tmp));
  v = atof(tmp);    
  //v = strtod(tmp, NULL);
  /*Console.print(s);
  Console.print("=");
  Console.println(v, 6);   */
  return v;
}

void RemoteControl::sendYesNo(int value){
  if (value == 1) Bluetooth.print("YES");
    else Bluetooth.print("NO");
}

void RemoteControl::sendOnOff(int value){
   if (value == 1) Bluetooth.print("ON");
    else Bluetooth.print("OFF");
}

void RemoteControl::sendTimer(ttimer_t timer){
  if (timer.active) Bluetooth.print(F("(X)  "));
    else Bluetooth.print(F("(   )  "));          
  Bluetooth.print(time2str(timer.startTime));
  Bluetooth.print("-");
  Bluetooth.print(time2str(timer.stopTime));
  Bluetooth.println();
  if (timer.daysOfWeek == B1111111){
    Bluetooth.print(F("every day"));
  } else {
    int counter= 0;  
    for (int j=0; j < 7; j++){
      if ((timer.daysOfWeek >> j) & 1) {
        if (counter != 0) Bluetooth.print(",");
        Bluetooth.print(dayOfWeek[j]);              
        counter++;      
      }
    }
  }
}


// NOTE: pfodApp rev57 changed slider protocol:  displayValue = (sliderValue + offset) * scale
void RemoteControl::sendSlider(String cmd, String title, float value, String unit, double scale, float maxvalue, float minvalue){
  Bluetooth.print("|"); 
  Bluetooth.print(cmd);  
  Bluetooth.print("~");    
  Bluetooth.print(title);
  Bluetooth.print(" `");      
  Bluetooth.print(((int)(value/scale)));
  Bluetooth.print("`");  
  Bluetooth.print(((int)(maxvalue/scale)));
  Bluetooth.print("`");
  Bluetooth.print(((int)(minvalue/scale)));
  Bluetooth.print("~ ~");
  if (scale == 10) Bluetooth.print("10");
    else if (scale == 1) Bluetooth.print("1");
    else if (scale == 0.1) Bluetooth.print("0.1");
    else if (scale == 0.01) Bluetooth.print("0.01");
    else if (scale == 0.001) Bluetooth.print("0.001");
    else if (scale == 0.0001) Bluetooth.print("0.0001");
}

void RemoteControl::sendPIDSlider(String cmd, String title, PID &pid, double scale, float maxvalue){
  sendSlider(cmd + "p", title + "_P", pid.Kp, "", scale, maxvalue);
  sendSlider(cmd + "i", title + "_I", pid.Ki, "", scale, maxvalue);
  sendSlider(cmd + "d", title + "_D", pid.Kd, "", scale, maxvalue);  
}

void RemoteControl::processSlider(String result, float &value, double scale){
  int idx = result.indexOf('`');
  String s = result.substring(idx + 1);      
  float v = stringToFloat(s);
  value = v * scale;  
}

void RemoteControl::processPIDSlider(String result, String cmd, PID &pid, double scale, float maxvalue){
  int idx = result.indexOf('`');
  String s = result.substring(idx + 1);      
  //Console.println(tmp);
  float v = stringToFloat(s);
  if (pfodCmd.startsWith(cmd + "p")){
    pid.Kp = v * scale;
    if (pid.Kp < scale) pid.Kp = 0.0;
  }
  else if (pfodCmd.startsWith(cmd + "i")){
    pid.Ki = v * scale;
    if (pid.Ki < scale) pid.Ki = 0.0;
  }
  else if (pfodCmd.startsWith(cmd + "d")){ 
    pid.Kd = v * scale;      
    if (pid.Kd < scale) pid.Kd = 0.0;
  }
}


void RemoteControl::processSlider(String result, long &value, double scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}

void RemoteControl::processSlider(String result, int &value, double scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}

void RemoteControl::processSlider(String result, byte &value, double scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}

void RemoteControl::processSlider(String result, short &value, double scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}
    
void RemoteControl::sendMainMenu(boolean update){
  if (update) Bluetooth.print("{:"); else {
    Bluetooth.print(F("{.Ardumower"));  
    Bluetooth.print(" (");
    Bluetooth.print(robot->name);
    Bluetooth.print(")");
  }
  Bluetooth.print(F("|r~Commands|n~Manual|s~Settings|in~Info|c~Test compass|m1~Log sensors|yp~Plot"));
  Bluetooth.println(F("|y4~Error counters|y9~ADC calibration}"));        
}

void RemoteControl::sendADCMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.ADC calibration`1000"));         
  Bluetooth.print(F("|c1~Calibrate (perimeter sender, charger must be off) "));
  for (int ch=0; ch < 16; ch++){   
    int16_t adcMin = ADCMan.getADCMin(A0+ch);
    int16_t adcMax = ADCMan.getADCMax(A0+ch);
    int16_t adcOfs = ADCMan.getADCOfs(A0+ch);    
    Bluetooth.print(F("|zz~AD"));
    Bluetooth.print(ch);
    Bluetooth.print(" min=");
    Bluetooth.print(adcMin);
    Bluetooth.print(" max=");
    Bluetooth.print(adcMax);
    Bluetooth.print(" diff=");
    Bluetooth.print(adcMax-adcMin);    
    Bluetooth.print(" ofs=");
    Bluetooth.print(adcOfs);            
  }
  Bluetooth.println("}");
}  


void RemoteControl::sendPlotMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Plot"));           
  Bluetooth.print(F("|y7~Sensors|y5~Sensor counters|y3~IMU|y6~Perimeter|y8~GPS"));   
  Bluetooth.println(F("|y1~Battery|y2~Odometry2D|y11~Motor control|y10~GPS2D}"));
}  


void RemoteControl::sendSettingsMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Settings"));         
  Bluetooth.print(F("|sz~Save settings|s1~Motor|s2~Mow|s3~Bumper|s4~Sonar|s5~Perimeter|s6~Lawn sensor|s7~IMU|s8~R/C"));
  Bluetooth.println(F("|s9~Battery|s10~Station|s11~Odometry|s13~Rain|s15~Drop sensor|s14~GPS|i~Timer|s12~Date/time|sx~Factory settings}"));
}  

void RemoteControl::sendErrorMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Error counters`1000"));         
  Bluetooth.print(F("|z00~Reset counters"));
  Bluetooth.print(F("|zz~ADC calibration "));
  Bluetooth.print(robot->errorCounterMax[ERR_ADC_CALIB]);
  Bluetooth.print(F("|zz~Charger "));
  Bluetooth.print(robot->errorCounterMax[ERR_CHARGER]);
  Bluetooth.print(F("|zz~Battery "));
  Bluetooth.print(robot->errorCounterMax[ERR_BATTERY]);
  Bluetooth.print(F("|zz~Motor left "));
  Bluetooth.print(robot->errorCounterMax[ERR_MOTOR_LEFT]);
  Bluetooth.print(F("|zz~Motor right "));
  Bluetooth.print(robot->errorCounterMax[ERR_MOTOR_RIGHT]);
  Bluetooth.print(F("|zz~Motor mow "));
  Bluetooth.print(robot->errorCounterMax[ERR_MOTOR_MOW]);  
  Bluetooth.print(F("|zz~Mow sense "));
  Bluetooth.print(robot->errorCounterMax[ERR_MOW_SENSE]);
  Bluetooth.print(F("|zz~Odometry left "));
  Bluetooth.print(robot->errorCounterMax[ERR_ODOMETRY_LEFT]);
  Bluetooth.print(F("|zz~Odometry right "));
  Bluetooth.print(robot->errorCounterMax[ERR_ODOMETRY_RIGHT]);
  Bluetooth.print(F("|zz~Perimeter timeout "));
  Bluetooth.print(robot->errorCounterMax[ERR_PERIMETER_TIMEOUT]);
  Bluetooth.print(F("|zz~Perimeter tracking "));
  Bluetooth.print(robot->errorCounterMax[ERR_TRACKING]);    
  Bluetooth.print(F("|zz~IMU comm "));
  Bluetooth.print(robot->errorCounterMax[ERR_IMU_COMM]);
  Bluetooth.print(F("|zz~IMU calibration "));
  Bluetooth.print(robot->errorCounterMax[ERR_IMU_CALIB]);    
  Bluetooth.print(F("|zz~IMU tilt "));
  Bluetooth.print(robot->errorCounterMax[ERR_IMU_TILT]);
  Bluetooth.print(F("|zz~RTC comm "));
  Bluetooth.print(robot->errorCounterMax[ERR_RTC_COMM]);
  Bluetooth.print(F("|zz~RTC data "));
  Bluetooth.print(robot->errorCounterMax[ERR_RTC_DATA]);
  Bluetooth.print(F("|zz~GPS comm "));
  Bluetooth.print(robot->errorCounterMax[ERR_GPS_COMM]);  
  Bluetooth.print(F("|zz~GPS data "));
  Bluetooth.print(robot->errorCounterMax[ERR_GPS_DATA]);
  Bluetooth.print(F("|zz~Robot stucked "));
  Bluetooth.print(robot->errorCounterMax[ERR_STUCK]);
  Bluetooth.print(F("|zz~EEPROM data "));
  Bluetooth.print(robot->errorCounterMax[ERR_EEPROM_DATA]); 
  Bluetooth.println("}");
}  

void RemoteControl::processErrorMenu(String pfodCmd){      
  if (pfodCmd == "z00") {
    robot->resetErrorCounters();
    robot->setNextState(STATE_OFF, 0);
  }
  sendErrorMenu(true);
}


void RemoteControl::sendMotorMenu(boolean update){  
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Motor`1000"));     
  Bluetooth.println(F("|a00~Overload Counter l, r "));
  Bluetooth.print(robot->motorLeftSenseCounter);  
  Bluetooth.print(", ");
  Bluetooth.print(robot->motorRightSenseCounter);  
  Bluetooth.println(F("|a01~Power in Watt l, r "));    
  Bluetooth.print(robot->motorLeftSense);
  Bluetooth.print(", ");  
  Bluetooth.print(robot->motorRightSense);
  Bluetooth.println(F("|a05~motor current in mA l, r "));    
  Bluetooth.print(robot->motorLeftSenseCurrent);
  Bluetooth.print(", ");  
  Bluetooth.print(robot->motorRightSenseCurrent);      
  //Console.print("motorpowermax=");
  //Console.println(robot->motorPowerMax);
  sendSlider("a02", F("Power max"), robot->motorPowerMax, "", 0.1, 100);  
  sendSlider("a03", F("calibrate left motor "), robot->motorLeftSenseCurrent, "", 1, 1000, 0);       
  sendSlider("a04", F("calibrate right motor"), robot->motorRightSenseCurrent, "", 1, 1000, 0);      
  Bluetooth.print(F("|a05~Speed l, r"));    
  Bluetooth.print(robot->motorLeftPWMCurr);
  Bluetooth.print(", ");  
  Bluetooth.print(robot->motorRightPWMCurr);   
  sendSlider("a06", F("Speed max in rpm"), robot->motorSpeedMaxRpm, "", 1, 100);    
  sendSlider("a15", F("Speed max in pwm"), robot->motorSpeedMaxPwm, "", 1, 255);      
  sendSlider("a11", F("Accel"), robot->motorAccel, "", 1, 2000, 500);  
  sendSlider("a18", F("Power ignore time"), robot->motorPowerIgnoreTime, "", 1, 8000);     
  sendSlider("a07", F("Roll time max"), robot->motorRollTimeMax, "", 1, 8000); 
  sendSlider("a19", F("Roll time min"), robot->motorRollTimeMin, "", 1, (robot->motorRollTimeMax - 500)); 
  sendSlider("a08", F("Reverse time"), robot->motorReverseTime, "", 1, 8000);     
  sendSlider("a09", F("Forw time max"), robot->motorForwTimeMax, "", 10, 80000);       
  sendSlider("a12", F("Bidir speed ratio 1"), robot->motorBiDirSpeedRatio1, "", 0.01, 1.0);       
  sendSlider("a13", F("Bidir speed ratio 2"), robot->motorBiDirSpeedRatio2, "", 0.01, 1.0);       
  sendPIDSlider("a14", "RPM", robot->motorLeftPID, 0.01, 3.0);        
  Bluetooth.println(F("|a10~Testing is"));    
  switch (testmode){
    case 0: Bluetooth.print(F("OFF")); break;
    case 1: Bluetooth.print(F("Left motor forw")); break;
    case 2: Bluetooth.print(F("Right motor forw")); break;
  }
  Bluetooth.print(F("|a14~for config file:"));    
  Bluetooth.print(F("motorSenseScale l, r"));
  Bluetooth.print(robot->motorSenseLeftScale);
  Bluetooth.print(", ");  
  Bluetooth.print(robot->motorSenseRightScale);
  Bluetooth.print(F("|a16~Swap left direction "));
  sendYesNo(robot->motorLeftSwapDir);
  Bluetooth.print(F("|a17~Swap right direction "));
  sendYesNo(robot->motorRightSwapDir);
  Bluetooth.println("}");            
}

void RemoteControl::processMotorMenu(String pfodCmd){      
  if (pfodCmd.startsWith("a02")) { processSlider(pfodCmd, robot->motorPowerMax, 0.1);
    //Console.print("motorpowermax=");
    //Console.println(robot->motorPowerMax);
  }

    else if (pfodCmd.startsWith("a03")){
      processSlider(pfodCmd, robot->motorLeftSenseCurrent, 1);
      robot->motorSenseLeftScale = robot->motorLeftSenseCurrent / max(0,(float)robot->motorLeftSenseADC);                  
}
    else if (pfodCmd.startsWith("a04")){
      processSlider(pfodCmd, robot->motorRightSenseCurrent, 1);
      robot->motorSenseRightScale = robot->motorRightSenseCurrent / max(0,(float)robot->motorRightSenseADC); 
}      
    else if (pfodCmd.startsWith("a06")) processSlider(pfodCmd, robot->motorSpeedMaxRpm, 1);
    else if (pfodCmd.startsWith("a15")) processSlider(pfodCmd, robot->motorSpeedMaxPwm, 1);
    else if (pfodCmd.startsWith("a07")) processSlider(pfodCmd, robot->motorRollTimeMax, 1); 
    else if (pfodCmd.startsWith("a19")) processSlider(pfodCmd, robot->motorRollTimeMin, 1); 
    else if (pfodCmd.startsWith("a08")) processSlider(pfodCmd, robot->motorReverseTime, 1);
    else if (pfodCmd.startsWith("a09")) processSlider(pfodCmd, robot->motorForwTimeMax, 10);
    else if (pfodCmd.startsWith("a11")) processSlider(pfodCmd, robot->motorAccel, 1);    
    else if (pfodCmd.startsWith("a12")) processSlider(pfodCmd, robot->motorBiDirSpeedRatio1, 0.01);    
    else if (pfodCmd.startsWith("a13")) processSlider(pfodCmd, robot->motorBiDirSpeedRatio2, 0.01);    
    else if (pfodCmd.startsWith("a14")) processPIDSlider(pfodCmd, "a14", robot->motorLeftPID, 0.01, 3.0);
    else if (pfodCmd.startsWith("a16")) robot->motorLeftSwapDir = !robot->motorLeftSwapDir;
    else if (pfodCmd.startsWith("a17")) robot->motorRightSwapDir = !robot->motorRightSwapDir;  
    else if (pfodCmd.startsWith("a18")) processSlider(pfodCmd, robot->motorPowerIgnoreTime, 1);        
    else if (pfodCmd == "a10") { 
      testmode = (testmode + 1) % 3;
      switch (testmode){
        case 0: robot->setNextState(STATE_OFF,0); break;
        case 1: robot->setNextState(STATE_MANUAL,0); robot->motorRightSpeedRpmSet = 0; robot->motorLeftSpeedRpmSet = robot->motorSpeedMaxRpm; break;
        case 2: robot->setNextState(STATE_MANUAL,0); robot->motorLeftSpeedRpmSet  = 0; robot->motorRightSpeedRpmSet = robot->motorSpeedMaxRpm; break;      
      }
    }
  sendMotorMenu(true);
}
  
void RemoteControl::sendMowMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Mow`1000"));               
  Bluetooth.print(F("|o00~Overload Counter "));
  Bluetooth.print(robot->motorMowSenseCounter);    
  Bluetooth.print(F("|o01~Power in Watt "));  
  Bluetooth.print(robot->motorMowSense);  
  Bluetooth.print(F("|o11~current in mA "));  
  Bluetooth.print(robot->motorMowSenseCurrent);  
  sendSlider("o02", F("Power max"), robot->motorMowPowerMax, "", 0.1, 100);         
  sendSlider("o03", F("calibrate mow motor "), robot->motorMowSenseCurrent, "", 1, 3000, 0);          
  Bluetooth.print(F("|o04~Speed "));
  Bluetooth.print(robot->motorMowPWMCurr);      
  sendSlider("o05", F("Speed max"), robot->motorMowSpeedMaxPwm, "", 1, 255);       
  if (robot->developerActive) {
    Bluetooth.print(F("|o06~Modulate "));
    sendYesNo(robot->motorMowModulate);
  }      
  Bluetooth.print(F("|o07~RPM "));
  Bluetooth.print(robot->motorMowRpmCurr);    
  sendSlider("o08", F("RPM set"), robot->motorMowRPMSet, "", 1, 4500);     
  sendPIDSlider("o09", "RPM", robot->motorMowPID, 0.01, 1.0);      
  Bluetooth.println(F("|o10~Testing is"));    
  switch (testmode){
    case 0: Bluetooth.print(F("OFF")); break;
    case 1: Bluetooth.print(F("Motor ON")); break;
  }
  Bluetooth.println(F("|o04~for config file:"));    
  Bluetooth.println(F("motorMowSenseScale:"));
  Bluetooth.print(robot->motorMowSenseScale);  
  Bluetooth.println("}");              
}

void RemoteControl::processMowMenu(String pfodCmd){      
  if (pfodCmd.startsWith("o02")) processSlider(pfodCmd, robot->motorMowPowerMax, 0.1);
    else if (pfodCmd.startsWith("o03")){
            processSlider(pfodCmd, robot->motorMowSenseCurrent, 1);
            robot->motorMowSenseScale = robot->motorMowSenseCurrent / max(0,(float)robot->motorMowSenseADC);
         } 
    else if (pfodCmd.startsWith("o05")) processSlider(pfodCmd, robot->motorMowSpeedMaxPwm, 1);
    else if (pfodCmd == "o06") robot->motorMowModulate = !robot->motorMowModulate;    
    else if (pfodCmd.startsWith("o08")) processSlider(pfodCmd, robot->motorMowRPMSet, 1);    
    else if (pfodCmd.startsWith("o09")) processPIDSlider(pfodCmd, "o09", robot->motorMowPID, 0.01, 1.0);
    else if (pfodCmd == "o10") { 
      testmode = (testmode + 1) % 2;
      switch (testmode){
        case 0: robot->setNextState(STATE_OFF,0);robot->motorMowRpmCurr = 0; robot->motorMowEnable = false; break;
        case 1: robot->setNextState(STATE_MANUAL,0); robot->motorMowEnable = true; break;
      }
    }    
  sendMowMenu(true);
}

void RemoteControl::sendBumperMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Bumper`1000"));         
  Bluetooth.print(F("|b00~Use "));
  sendYesNo(robot->bumperUse);    
  Bluetooth.println(F("|b01~Counter l, r "));
  Bluetooth.print(robot->bumperLeftCounter);  
  Bluetooth.print(", ");
  Bluetooth.print(robot->bumperRightCounter);  
  Bluetooth.println(F("|b02~Value l, r "));
  Bluetooth.print(robot->bumperLeft);
  Bluetooth.print(", ");
  Bluetooth.print(robot->bumperRight);  
  Bluetooth.println("}");                
}

void RemoteControl::sendDropMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Drop`1000"));         
  Bluetooth.print(F("|u00~Use "));
  sendYesNo(robot->dropUse);    
  Bluetooth.println(F("|u01~Counter l, r "));
  Bluetooth.print(robot->dropLeftCounter);  
  Bluetooth.print(", ");
  Bluetooth.print(robot->dropRightCounter);  
  Bluetooth.println(F("|u02~Value l, r "));
  Bluetooth.print(robot->dropLeft);
  Bluetooth.print(", ");
  Bluetooth.print(robot->dropRight);  
  Bluetooth.println("}");                
}


void RemoteControl::processBumperMenu(String pfodCmd){      
  if (pfodCmd == "b00") robot->bumperUse = !robot->bumperUse;    
  sendBumperMenu(true);
}

void RemoteControl::processDropMenu(String pfodCmd){      
  if (pfodCmd == "u00") robot->dropUse = !robot->dropUse;    
  sendDropMenu(true);
}


void RemoteControl::sendSonarMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Sonar`1000"));         
  Bluetooth.print(F("|d00~Use "));
  sendYesNo(robot->sonarUse);
  Bluetooth.print(F("|d04~Use left "));
  sendYesNo(robot->sonarLeftUse);
  Bluetooth.print(F("|d05~Use center "));
  sendYesNo(robot->sonarCenterUse);
  Bluetooth.print(F("|d06~Use right "));
  sendYesNo(robot->sonarRightUse);
  Bluetooth.print(F("|d01~Counter "));
  Bluetooth.print(robot->sonarDistCounter);    
  Bluetooth.println(F("|d02~Value l, c, r"));
  Bluetooth.print(robot->sonarDistLeft);
  Bluetooth.print(", ");
  Bluetooth.print(robot->sonarDistCenter);
  Bluetooth.print(", ");
  Bluetooth.print(robot->sonarDistRight);  
  sendSlider("d03", F("Trigger below"), robot->sonarTriggerBelow, "", 1, 3000);       
  Bluetooth.println("}");                
}

void RemoteControl::processSonarMenu(String pfodCmd){      
  if (pfodCmd == "d00") robot->sonarUse = !robot->sonarUse;
    else if (pfodCmd.startsWith("d03")) processSlider(pfodCmd, robot->sonarTriggerBelow, 1);
    else if (pfodCmd == "d04") robot->sonarLeftUse = !robot->sonarLeftUse;
    else if (pfodCmd == "d05") robot->sonarCenterUse = !robot->sonarCenterUse;
    else if (pfodCmd == "d06") robot->sonarRightUse = !robot->sonarRightUse;
  sendSonarMenu(true);
}

void RemoteControl::sendPerimeterMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Perimeter`1000"));         
  Bluetooth.print(F("|e00~Use "));
  sendYesNo(robot->perimeterUse);  
  Bluetooth.println(F("|e02~Value"));
  Bluetooth.print(robot->perimeterMag);
  if (robot->perimeterMag < 0) Bluetooth.print(" (inside)");
    else Bluetooth.print(" (outside)");     
  sendSlider("e08", F("Timed-out if below smag"), robot->perimeter.timedOutIfBelowSmag, "", 1, 2000);  
  sendSlider("e14", F("Timeout (s) if not inside"), robot->perimeter.timeOutSecIfNotInside, "", 1, 20, 1);  
  sendSlider("e04", F("Trigger timeout"), robot->perimeterTriggerTimeout, "", 1, 2000);
  sendSlider("e05", F("Perimeter out roll time max"), robot->perimeterOutRollTimeMax, "", 1, 8000);       
  sendSlider("e06", F("Perimeter out roll time min"), robot->perimeterOutRollTimeMin, "", 1, 8000); 
  sendSlider("e15", F("Perimeter out reverse time"), robot->perimeterOutRevTime, "", 1, 8000); 
  sendSlider("e16", F("Perimeter tracking roll time"), robot->perimeterTrackRollTime, "", 1, 8000); 
  sendSlider("e17", F("Perimeter tracking reverse time"), robot->perimeterTrackRevTime, "", 1, 8000); 
  sendSlider("e11", F("Transition timeout"), robot->trackingPerimeterTransitionTimeOut, "", 1, 5000);
  sendSlider("e12", F("Track error timeout"), robot->trackingErrorTimeOut, "", 1, 10000);             
  sendPIDSlider("e07", F("Track"), robot->perimeterPID, 0.1, 100);  
  Bluetooth.print(F("|e09~Use differential signal "));
  sendYesNo(robot->perimeter.useDifferentialPerimeterSignal);    
  Bluetooth.print(F("|e10~Swap coil polarity "));
  sendYesNo(robot->perimeter.swapCoilPolarity);
  Bluetooth.print(F("|e13~Block inner wheel  "));
  sendYesNo(robot->trackingBlockInnerWheelWhilePerimeterStruggling);
  Bluetooth.println("}");                
}

void RemoteControl::processPerimeterMenu(String pfodCmd){      
  if (pfodCmd == "e00") robot->perimeterUse = !robot->perimeterUse;
    else if (pfodCmd.startsWith("e04")) processSlider(pfodCmd, robot->perimeterTriggerTimeout, 1);  
    else if (pfodCmd.startsWith("e05")) processSlider(pfodCmd, robot->perimeterOutRollTimeMax, 1);
    else if (pfodCmd.startsWith("e06")) processSlider(pfodCmd, robot->perimeterOutRollTimeMin, 1);
    else if (pfodCmd.startsWith("e15")) processSlider(pfodCmd, robot->perimeterOutRevTime, 1);
    else if (pfodCmd.startsWith("e16")) processSlider(pfodCmd, robot->perimeterTrackRollTime, 1);
    else if (pfodCmd.startsWith("e17")) processSlider(pfodCmd, robot->perimeterTrackRevTime, 1);
    else if (pfodCmd.startsWith("e07")) processPIDSlider(pfodCmd, "e07", robot->perimeterPID, 0.1, 100);    
    else if (pfodCmd.startsWith("e08")) processSlider(pfodCmd, robot->perimeter.timedOutIfBelowSmag, 1);    
    else if (pfodCmd.startsWith("e09")) robot->perimeter.useDifferentialPerimeterSignal = !robot->perimeter.useDifferentialPerimeterSignal;
    else if (pfodCmd.startsWith("e10")) robot->perimeter.swapCoilPolarity = !robot->perimeter.swapCoilPolarity;
    else if (pfodCmd.startsWith("e11")) processSlider(pfodCmd, robot->trackingPerimeterTransitionTimeOut, 1);
    else if (pfodCmd.startsWith("e12")) processSlider(pfodCmd, robot->trackingErrorTimeOut, 1);
    else if (pfodCmd.startsWith("e13")) robot->trackingBlockInnerWheelWhilePerimeterStruggling = !robot->trackingBlockInnerWheelWhilePerimeterStruggling;          
    else if (pfodCmd.startsWith("e14")) processSlider(pfodCmd, robot->perimeter.timeOutSecIfNotInside, 1);     
  sendPerimeterMenu(true);
}

void RemoteControl::sendLawnSensorMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Lawn sensor`1000"));         
  Bluetooth.print(F("|f00~Use "));
  sendYesNo(robot->lawnSensorUse);  
  Bluetooth.print(F("|f01~Counter "));
  Bluetooth.print(robot->lawnSensorCounter);      
  Bluetooth.println(F("|f02~Value f, b"));
  Bluetooth.print(robot->lawnSensorFront); 
  Bluetooth.print(", "); 
  Bluetooth.print(robot->lawnSensorBack);   
  Bluetooth.println("}");                
}

void RemoteControl::processLawnSensorMenu(String pfodCmd){      
  if (pfodCmd == "f00") robot->lawnSensorUse = !robot->lawnSensorUse;
  sendLawnSensorMenu(true);
}

void RemoteControl::sendRainMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Rain`1000"));         
  Bluetooth.print(F("|m00~Use "));
  sendYesNo(robot->rainUse);  
  Bluetooth.print(F("|m01~Counter "));
  Bluetooth.print(robot->rainCounter);      
  Bluetooth.println(F("|m02~Value"));
  Bluetooth.print(robot->rain); 
  Bluetooth.println("}");                
}

void RemoteControl::processRainMenu(String pfodCmd){      
  if (pfodCmd == "m00") robot->rainUse = !robot->rainUse;
  sendRainMenu(true);
}

void RemoteControl::sendGPSMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.GPS`1000"));         
  Bluetooth.print(F("|q00~Use "));
  sendYesNo(robot->gpsUse);
  sendSlider("q01", F("Stucked if GPS speed is below"), robot->stuckedIfGpsSpeedBelow, "", 0.1, 3); 
  sendSlider("q02", F("GPS speed ignore time"), robot->gpsSpeedIgnoreTime, "", 1, 10000, robot->motorReverseTime);       
  Bluetooth.println("}");                
}

void RemoteControl::processGPSMenu(String pfodCmd){      
  if (pfodCmd == "q00") robot->gpsUse = !robot->gpsUse;
  else if (pfodCmd.startsWith("q01")) processSlider(pfodCmd, robot->stuckedIfGpsSpeedBelow, 0.1);  
  else if (pfodCmd.startsWith("q02")) processSlider(pfodCmd, robot->gpsSpeedIgnoreTime, 1);  
  sendGPSMenu(true);
}


void RemoteControl::sendImuMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.IMU`1000"));         
  Bluetooth.print(F("|g00~Use "));  
  sendYesNo(robot->imuUse);
  Bluetooth.print(F("|g01~Yaw "));
  Bluetooth.print(robot->imu.ypr.yaw/PI*180);
  Bluetooth.print(F(" deg"));  
  Bluetooth.print(F("|g09~DriveHeading "));
  Bluetooth.print(robot->imuDriveHeading/PI*180);
  Bluetooth.print(F(" deg"));  
  Bluetooth.print(F("|g02~Pitch "));
  Bluetooth.print(robot->imu.ypr.pitch/PI*180);
  Bluetooth.print(F(" deg"));  
  Bluetooth.print(F("|g03~Roll "));
  Bluetooth.print(robot->imu.ypr.roll/PI*180);
  Bluetooth.print(F(" deg"));  
  Bluetooth.print(F("|g04~Correct dir "));
  sendYesNo(robot->imuCorrectDir);  
  sendPIDSlider("g05", F("Dir"), robot->imuDirPID, 0.1, 20);
  sendPIDSlider("g06", F("Roll"), robot->imuRollPID, 0.1, 30);    
  Bluetooth.print(F("|g07~Acc cal next side"));
  Bluetooth.print(F("|g08~Com cal start/stop"));  
  Bluetooth.println("}");                
}

void RemoteControl::processImuMenu(String pfodCmd){      
  if (pfodCmd == "g00" ) robot->imuUse = !robot->imuUse;
    else if (pfodCmd == "g04" ) robot->imuCorrectDir = !robot->imuCorrectDir;
    else if (pfodCmd.startsWith("g05")) processPIDSlider(pfodCmd, "g05", robot->imuDirPID, 0.1, 20);    
    else if (pfodCmd.startsWith("g06")) processPIDSlider(pfodCmd, "g06", robot->imuRollPID, 0.1, 30);    
    else if (pfodCmd == "g07") robot->imu.calibAccNextAxis();
    else if (pfodCmd == "g08") robot->imu.calibComStartStop();
  sendImuMenu(true);
}

void RemoteControl::sendRemoteMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Remote R/C`1000"));         
  Bluetooth.print(F("|h00~Use "));
  sendYesNo(robot->remoteUse);  
  Bluetooth.println("}");                
}

void RemoteControl::processRemoteMenu(String pfodCmd){      
  if (pfodCmd == "h00" ) robot->remoteUse = !robot->remoteUse;    
  sendRemoteMenu(true);
}

void RemoteControl::sendBatteryMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Battery`1000"));           
  Bluetooth.print(F("|j00~Battery "));
  Bluetooth.print(robot->batVoltage);
  Bluetooth.print(" V");
  Bluetooth.print(F("|j01~Monitor "));  
  sendYesNo(robot->batMonitor);
  if (robot->developerActive) sendSlider("j05", F("Calibrate batFactor "), robot->batFactor, "", 0.01, 1.0);   
  //Console.print("batFactor=");
  //Console.println(robot->batFactor);  
  sendSlider("j02", F("Go home if below Volt"), robot->batGoHomeIfBelow, "", 0.1, robot->batFull, (robot->batFull*0.72));  // for Sony Konion cells 4.2V * 0,72= 3.024V which is pretty safe to use 
  sendSlider("j12", F("Switch off if idle minutes"), robot->batSwitchOffIfIdle, "", 1, 300, 1);  
  sendSlider("j03", F("Switch off if below Volt"), robot->batSwitchOffIfBelow, "", 0.1, robot->batFull, (robot->batFull*0.72));  
  Bluetooth.print(F("|j04~Charge "));
  Bluetooth.print(robot->chgVoltage);
  Bluetooth.print("V ");
  Bluetooth.print(robot->chgCurrent);
  Bluetooth.print("A");
  sendSlider("j09", F("Calibrate batChgFactor"), robot->batChgFactor, "", 0.01, 1.0);       
  sendSlider("j06", F("Charge sense zero"), robot->chgSenseZero, "", 1, 600, 400);       
  sendSlider("j08", F("Charge factor"), robot->chgFactor, "", 0.01, 80);       
  sendSlider("j10", F("charging starts if Voltage is below"), robot->startChargingIfBelow, "", 0.1, robot->batFull);       
  sendSlider("j11", F("Battery is fully charged if current is below"), robot->batFullCurrent, "", 0.1, robot->batChargingCurrentMax);       
  Bluetooth.println("}");
}

void RemoteControl::processBatteryMenu(String pfodCmd){      
  if (pfodCmd == "j01") robot->batMonitor = !robot->batMonitor;
    else if (pfodCmd.startsWith("j02")) {
      processSlider(pfodCmd, robot->batGoHomeIfBelow, 0.1);
      //Console.print("gohomeifbelow=");
      //Console.println(robot->batGoHomeIfBelow);
    }
    else if (pfodCmd.startsWith("j03")) processSlider(pfodCmd, robot->batSwitchOffIfBelow, 0.1); 
    else if (pfodCmd.startsWith("j05")) processSlider(pfodCmd, robot->batFactor, 0.01);
    else if (pfodCmd.startsWith("j06")) processSlider(pfodCmd, robot->chgSenseZero, 1);   
    else if (pfodCmd.startsWith("j08")) processSlider(pfodCmd, robot->chgFactor, 0.01);    
    else if (pfodCmd.startsWith("j09")) processSlider(pfodCmd, robot->batChgFactor, 0.01);
    else if (pfodCmd.startsWith("j10")) processSlider(pfodCmd, robot->startChargingIfBelow, 0.1);
    else if (pfodCmd.startsWith("j11")) processSlider(pfodCmd, robot->batFullCurrent, 0.1);
    else if (pfodCmd.startsWith("j12")) processSlider(pfodCmd, robot->batSwitchOffIfIdle, 1);
  sendBatteryMenu(true);
}

void RemoteControl::sendStationMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Station`1000"));         
  sendSlider("k00", F("Reverse time"), robot->stationRevTime, "", 1, 8000);     
  sendSlider("k01", F("Roll time"), robot->stationRollTime, "", 1, 8000);       
  sendSlider("k02", F("Forw time"), robot->stationForwTime, "", 1, 8000);         
  sendSlider("k03", F("Station reverse check time"), robot->stationCheckTime, "", 1, 8000);         
  Bluetooth.println("}");                
}

void RemoteControl::processStationMenu(String pfodCmd){      
  if (pfodCmd.startsWith("k00")) processSlider(pfodCmd, robot->stationRevTime, 1);
    else if (pfodCmd.startsWith("k01")) processSlider(pfodCmd, robot->stationRollTime, 1);
    else if (pfodCmd.startsWith("k02")) processSlider(pfodCmd, robot->stationForwTime, 1);
    else if (pfodCmd.startsWith("k03")) processSlider(pfodCmd, robot->stationCheckTime, 1);
  sendStationMenu(true);
}

void RemoteControl::sendOdometryMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Odometry2D`1000"));         
  Bluetooth.print(F("|l00~Use "));
  sendYesNo(robot->odometryUse);  
  Bluetooth.print(F("|l01~Value l, r "));
  Bluetooth.print(robot->odometryLeft);
  Bluetooth.print(", "); 
  Bluetooth.println(robot->odometryRight); 
  Bluetooth.println(F("|l03~RPM Motor l, r "));
  Bluetooth.print(robot->motorLeftRpmCurr);
  Bluetooth.print(", "); 
  Bluetooth.println(robot->motorRightRpmCurr);
  sendSlider("l04", F("Ticks per one full revolution"), robot->odometryTicksPerRevolution, "", 1, 2000);       
  sendSlider("l01", F("Ticks per cm"), robot->odometryTicksPerCm, "", 0.1, 30);       
  sendSlider("l02", F("Wheel base cm"), robot->odometryWheelBaseCm, "", 0.1, 50);  
  Bluetooth.print(F("|l08~Use two-way encoder "));
  sendYesNo(robot->twoWayOdometrySensorUse);
  Bluetooth.print(F("|l05~Swap left direction "));
  sendYesNo(robot->odometryLeftSwapDir);
  Bluetooth.print(F("|l06~Swap right direction "));
  sendYesNo(robot->odometryRightSwapDir);
  Bluetooth.println("}");                
}


void RemoteControl::processOdometryMenu(String pfodCmd){      
  if (pfodCmd == "l00") robot->odometryUse = !robot->odometryUse;
    else if (pfodCmd.startsWith("l01")) processSlider(pfodCmd, robot->odometryTicksPerCm, 0.1);
    else if (pfodCmd.startsWith("l02")) processSlider(pfodCmd, robot->odometryWheelBaseCm, 0.1); 
    else if (pfodCmd.startsWith("l04")) processSlider(pfodCmd, robot->odometryTicksPerRevolution, 1);
    else if (pfodCmd.startsWith("l05")) robot->odometryLeftSwapDir = !robot->odometryLeftSwapDir;     
    else if (pfodCmd.startsWith("l06")) robot->odometryRightSwapDir = !robot->odometryRightSwapDir;
    else if (pfodCmd.startsWith("l08")) robot->twoWayOdometrySensorUse = !robot->twoWayOdometrySensorUse;    
  sendOdometryMenu(true);
}

void RemoteControl::sendDateTimeMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Date/time"));         
  Bluetooth.print("|t00~");  
  Bluetooth.print(date2str(robot->datetime.date));  
  Bluetooth.print(", ");
  Bluetooth.print(time2str(robot->datetime.time));  
  sendSlider("t01", dayOfWeek[robot->datetime.date.dayOfWeek], robot->datetime.date.dayOfWeek, "", 1, 6, 0);       
  sendSlider("t02", "Day ", robot->datetime.date.day, "", 1, 31, 1);       
  sendSlider("t03", "Month ", robot->datetime.date.month, "", 1, 12, 1);       
  sendSlider("t04", "Year ", robot->datetime.date.year, "", 1, 2020, 2013);       
  sendSlider("t05", "Hour ", robot->datetime.time.hour, "", 1, 23, 0);       
  sendSlider("t06", "Minute ", robot->datetime.time.minute, "", 1, 59, 0);           
  Bluetooth.println("}");                
}

void RemoteControl::processDateTimeMenu(String pfodCmd){      
  if (pfodCmd.startsWith("t01")) processSlider(pfodCmd, robot->datetime.date.dayOfWeek, 1);    
    else if (pfodCmd.startsWith("t02")) processSlider(pfodCmd, robot->datetime.date.day, 1);
    else if (pfodCmd.startsWith("t03")) processSlider(pfodCmd, robot->datetime.date.month, 1);
    else if (pfodCmd.startsWith("t04")) processSlider(pfodCmd, robot->datetime.date.year, 1);
    else if (pfodCmd.startsWith("t05")) processSlider(pfodCmd, robot->datetime.time.hour, 1);
    else if (pfodCmd.startsWith("t06")) processSlider(pfodCmd, robot->datetime.time.minute, 1);    
  sendDateTimeMenu(true);
  Console.print(F("setting RTC datetime: "));
  Console.println(date2str(robot->datetime.date));  
  robot->setActuator(ACT_RTC, 0);            
}

void RemoteControl::sendTimerDetailMenu(int timerIdx, boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Details"));         
  Bluetooth.print("|p0");
  Bluetooth.print(timerIdx);
  Bluetooth.print("~Use ");  
  sendYesNo(robot->timer[timerIdx].active);        
  int startm = time2minutes(robot->timer[timerIdx].startTime);
  int stopm = time2minutes(robot->timer[timerIdx].stopTime);
  String sidx = String(timerIdx);
  sendSlider("p1"+sidx, F("Start hour "), robot->timer[timerIdx].startTime.hour, "", 1, 23, 0);       
  sendSlider("p2"+sidx, F("Start minute "), robot->timer[timerIdx].startTime.minute, "", 1, 59, 0);         
  sendSlider("p3"+sidx, F("Stop hour "), robot->timer[timerIdx].stopTime.hour, "", 1, 23, 0);       
  sendSlider("p4"+sidx, F("Stop minute "), robot->timer[timerIdx].stopTime.minute, "", 1, 59, 0);             
  for (int i=0; i < 7; i++){
    Bluetooth.print("|p5");
    Bluetooth.print(timerIdx);    
    Bluetooth.print(i);    
    Bluetooth.print("~");
    if ((robot->timer[timerIdx].daysOfWeek >> i) & 1) Bluetooth.print("(X)  ");
      else Bluetooth.print("(  )  ");   
    Bluetooth.print(dayOfWeek[i]);              
  }
  Bluetooth.print("|p9");
  Bluetooth.print(timerIdx);
  Bluetooth.print(F("~Set to current time"));  
  Bluetooth.println("}");                      
}

void RemoteControl::processTimerDetailMenu(String pfodCmd){      
  timehm_t time;
  boolean checkStop = false;
  boolean checkStart = false;
  int startmin, stopmin;
  int timerIdx = pfodCmd[2]-'0';
  if (pfodCmd.startsWith("p0")) robot->timer[timerIdx].active = !robot->timer[timerIdx].active;
    else if (pfodCmd.startsWith("p1")) { processSlider(pfodCmd, robot->timer[timerIdx].startTime.hour, 1); checkStop = true; }
    else if (pfodCmd.startsWith("p2")) { processSlider(pfodCmd, robot->timer[timerIdx].startTime.minute, 1); checkStop = true; }
    else if (pfodCmd.startsWith("p3")) { processSlider(pfodCmd, robot->timer[timerIdx].stopTime.hour, 1); checkStart = true; }      
    else if (pfodCmd.startsWith("p4")) { processSlider(pfodCmd, robot->timer[timerIdx].stopTime.minute, 1); checkStart = true; }        
    else if (pfodCmd.startsWith("p9")) {       
      robot->timer[timerIdx].startTime = robot->datetime.time; checkStop = true;      
      robot->timer[timerIdx].daysOfWeek = (1 << robot->datetime.date.dayOfWeek);      
    }
    else if (pfodCmd.startsWith("p5")) {
      int day = pfodCmd[3]-'0';
      robot->timer[timerIdx].daysOfWeek = robot->timer[timerIdx].daysOfWeek ^ (1 << day);
    }
    if (checkStop){
      // adjust start time
      startmin = min(1434, time2minutes(robot->timer[timerIdx].startTime));
      minutes2time(startmin, time);
      robot->timer[timerIdx].startTime = time;
      // check stop time
      stopmin  = time2minutes(robot->timer[timerIdx].stopTime);
      stopmin = max(stopmin, startmin + 5);       
      minutes2time(stopmin, time);
      robot->timer[timerIdx].stopTime = time;
    } else if (checkStart){
      // adjust stop time
      stopmin = max(5, time2minutes(robot->timer[timerIdx].stopTime));
      minutes2time(stopmin, time);
      robot->timer[timerIdx].stopTime = time;      
      // check start time
      startmin = time2minutes(robot->timer[timerIdx].startTime);      
      startmin = min(startmin, stopmin - 5);       
      minutes2time(startmin, time);
      robot->timer[timerIdx].startTime = time;
    }
  sendTimerDetailMenu(timerIdx, true);  
}

void RemoteControl::sendTimerMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Timer"));         
  Bluetooth.print(F("|i99~Use "));
  sendYesNo(robot->timerUse);      
  for (int i=0; i < MAX_TIMERS; i++){
    Bluetooth.print("|i0");
    Bluetooth.print(i);
    Bluetooth.print("~");
    sendTimer(robot->timer[i]);    
  }
  Bluetooth.println("}");                
}

void RemoteControl::processTimerMenu(String pfodCmd){      
  if (pfodCmd.startsWith("i0")) {
    int timerIdx = pfodCmd[2]-'0';
    sendTimerDetailMenu(timerIdx, false);  
  } else {
    if (pfodCmd.startsWith("i99")) robot->timerUse = !robot->timerUse;
    sendTimerMenu(true);
  }  
}

void RemoteControl::sendFactorySettingsMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.println(F("{.Factory settings"));
  Bluetooth.print(F("|x0~Set factory settings (requires reboot)"));
  Bluetooth.println("}");
}

void RemoteControl::processFactorySettingsMenu(String pfodCmd){      
  if (pfodCmd == "x0") robot->deleteUserSettings();
  sendFactorySettingsMenu(true);
}

void RemoteControl::sendInfoMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Info` 1000"));     
  Bluetooth.print(F("|v00~Ardumower "));
  Bluetooth.print(VER); 
  Bluetooth.print(F("|v01~Developer "));  
  sendYesNo(robot->developerActive); 
  Bluetooth.print(F("|v04~Stats override "));  
  sendYesNo(robot->statsOverride);     
  Bluetooth.print(F("|v02~Mowing time trip (min) "));
  Bluetooth.print(robot->statsMowTimeMinutesTrip);    
  Bluetooth.print(F("|v03~Mowing time total (hrs) "));
  Bluetooth.print(robot->statsMowTimeHoursTotal);
  Bluetooth.print(F("|v05~Battery charging cycles "));
  Bluetooth.print(robot->statsBatteryChargingCounterTotal);    
  Bluetooth.print(F("|v06~Battery recharged capacity trip (mAh)"));
  Bluetooth.print(robot->statsBatteryChargingCapacityTrip);    
  Bluetooth.print(F("|v07~Battery recharged capacity total (Ah)"));
  Bluetooth.print(robot->statsBatteryChargingCapacityTotal / 1000);    
  Bluetooth.print(F("|v08~Battery recharged capacity average (mAh)"));
  Bluetooth.print(robot->statsBatteryChargingCapacityAverage);        
  //Bluetooth.print("|d01~Perimeter v");
  //Bluetooth.print(verToString(readPerimeterVer())); 
  //Bluetooth.print("|d02~IMU v");  
  //Bluetooth.print(verToString(readIMUver())); 
  //Bluetooth.print("|d02~Stepper v");  
  //Bluetooth.print(verToString(readStepperVer())); 
  Bluetooth.println("}");        
}

void RemoteControl::processInfoMenu(String pfodCmd){      
  if (pfodCmd == "v01") robot->developerActive = !robot->developerActive;
  if (pfodCmd == "v04") robot->statsOverride = !robot->statsOverride; robot->saveUserSettings();

  sendInfoMenu(true);
}

void RemoteControl::sendCommandMenu(boolean update){  
  if (update) Bluetooth.print("{:"); else Bluetooth.print(F("{.Commands`5000"));  
  Bluetooth.print(F("|ro~OFF|ra~Auto mode|rc~RC mode|"));
  Bluetooth.print(F("rm~Mowing is "));  
  sendOnOff(robot->motorMowEnable);  
  Bluetooth.print(F("|rp~Pattern is "));
  Bluetooth.print(robot->mowPatternName());
  Bluetooth.print(F("|rh~Home|rk~Track|rs~State is "));         
  Bluetooth.print(robot->stateName());
  Bluetooth.print(F("|rr~Auto rotate is "));
  Bluetooth.print(robot->motorLeftPWMCurr);      
  Bluetooth.print(F("|r1~User switch 1 is "));         
  sendOnOff(robot->userSwitch1);  
  Bluetooth.print(F("|r2~User switch 2 is "));         
  sendOnOff(robot->userSwitch2);  
  Bluetooth.print(F("|r3~User switch 3 is "));         
  sendOnOff(robot->userSwitch3);  
  Bluetooth.print("}");
  Bluetooth.println();
}

void RemoteControl::processCommandMenu(String pfodCmd){
  if (pfodCmd == "ro"){
    // cmd: off      
    robot->setNextState(STATE_OFF, 0);          
    sendCommandMenu(true);
  } else if (pfodCmd == "rh"){
    // cmd: home      
    robot->setNextState(STATE_PERI_FIND, 0);                      
    sendCommandMenu(true);
  } else if (pfodCmd == "rr"){
    robot->setNextState(STATE_MANUAL, 0);
    robot->motorLeftSpeedRpmSet += 10; robot->motorRightSpeedRpmSet = -robot->motorLeftSpeedRpmSet;      
    sendCommandMenu(true);  
} else if (pfodCmd == "rk"){
    // cmd: track perimeter      
    robot->setNextState(STATE_PERI_TRACK, 0);                      
    sendCommandMenu(true);
  } else if (pfodCmd == "ra"){
    // cmd: start auto mowing      
    robot->motorMowEnable = true;      
    robot->setNextState(STATE_FORWARD, 0);                
    sendCommandMenu(true);
  } else if (pfodCmd == "rc"){      
    // cmd: start remote control (RC)      
    robot->motorMowEnable = true;
    robot->motorMowModulate = false;                
    robot->setNextState(STATE_REMOTE, 0);    
    sendCommandMenu(true);
  } else if (pfodCmd == "rm"){
    // cmd: mower motor on/off
    if (robot->stateCurr == STATE_OFF || robot->stateCurr == STATE_MANUAL) robot->motorMowEnableOverride = false;
    else robot->motorMowEnableOverride = !robot->motorMowEnableOverride;     
    robot->motorMowEnable = !robot->motorMowEnable;      
    sendCommandMenu(true);
  } else if (pfodCmd == "rs"){
    // cmd: state
    sendCommandMenu(true);
  } else if (pfodCmd == "rp"){
    // cmd: pattern
    robot->mowPatternCurr = (robot->mowPatternCurr + 1 ) % 3;      
    robot->setNextState(STATE_OFF, 0);            
    sendCommandMenu(true);
  } else if (pfodCmd == "r1"){
    robot->userSwitch1 = !robot->userSwitch1;
    robot->setUserSwitches();
    sendCommandMenu(true);
  } else if (pfodCmd == "r2"){
    robot->userSwitch2 = !robot->userSwitch2;
    robot->setUserSwitches();
    sendCommandMenu(true);
  } else if (pfodCmd == "r3"){
    robot->userSwitch3 = !robot->userSwitch3;
    robot->setUserSwitches();
    sendCommandMenu(true);
  } 
}


void RemoteControl::sendManualMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.println(F("{^Manual navigation`1000"));
  Bluetooth.print(F("|nl~Left|nr~Right|nf~Forward"));
  if (   ((robot->motorLeftSpeedRpmSet  < 5)  && (robot->motorLeftSpeedRpmSet  > -5))
     &&  ((robot->motorRightSpeedRpmSet < 5)  && (robot->motorRightSpeedRpmSet > -5))  ){
    Bluetooth.print(F("|nb~Reverse"));
  } else Bluetooth.print(F("|ns~Stop"));  
  Bluetooth.print(F("|nm~Mow is "));
  sendOnOff(robot->motorMowEnable);  
  Bluetooth.println("}");
}

void RemoteControl::sendCompassMenu(boolean update){
  if (update) Bluetooth.print("{:"); else Bluetooth.println(F("{^Compass`1000"));
  Bluetooth.print(F("|cw~West|ce~East|cn~North "));
  Bluetooth.print(robot->imu.ypr.yaw/PI*180);
  Bluetooth.println(F("|cs~South|cm~Mow}"));  
}

void RemoteControl::processCompassMenu(String pfodCmd){
 if (pfodCmd == "cm"){
    robot->motorMowEnable = !robot->motorMowEnable;            
    sendCompassMenu(true);
  } else if (pfodCmd == "cn"){      
    robot->imuRollHeading = 0;
    robot->setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  } else if (pfodCmd == "cs"){
    robot->imuRollHeading = PI;
    robot->setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  } else if (pfodCmd == "cw"){
    robot->imuRollHeading = -PI/2;
    robot->setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  } else if (pfodCmd == "ce"){
    robot->imuRollHeading = PI/2;
    robot->setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  }
}

void RemoteControl::processManualMenu(String pfodCmd){
  if (pfodCmd == "nl"){
    // manual: left
    robot->setNextState(STATE_MANUAL, 0);          
    float sign = 1.0;
    if (robot->motorLeftSpeedRpmSet < 0) sign = -1.0;      
    if (sign*robot->motorLeftSpeedRpmSet >= sign*robot->motorRightSpeedRpmSet) robot->motorLeftSpeedRpmSet  = sign * robot->motorSpeedMaxRpm/2;      
        else robot->motorLeftSpeedRpmSet /= 2; 
    robot->motorRightSpeedRpmSet = sign * robot->motorSpeedMaxRpm;
    sendManualMenu(true);
  } else if (pfodCmd == "nr"){      
    // manual: right
    robot->setNextState(STATE_MANUAL, 0);          
    float sign = 1.0;
    if (robot->motorRightSpeedRpmSet < 0) sign = -1.0;
    if (sign*robot->motorRightSpeedRpmSet >= sign*robot->motorLeftSpeedRpmSet) robot->motorRightSpeedRpmSet  = sign* robot->motorSpeedMaxRpm/2;
        else robot->motorRightSpeedRpmSet /= 2;            
    robot->motorLeftSpeedRpmSet  = sign * robot->motorSpeedMaxRpm;
    sendManualMenu(true);
  } else if (pfodCmd == "nf"){
    // manual: forward
    robot->setNextState(STATE_MANUAL, 0);          
    robot->motorLeftSpeedRpmSet  = robot->motorSpeedMaxRpm;
    robot->motorRightSpeedRpmSet = robot->motorSpeedMaxRpm;
    sendManualMenu(true);
  } else if (pfodCmd == "nb"){
    // manual: reverse
    robot->setNextState(STATE_MANUAL, 0);          
    robot->motorLeftSpeedRpmSet  = -robot->motorSpeedMaxRpm;
    robot->motorRightSpeedRpmSet = -robot->motorSpeedMaxRpm;
    sendManualMenu(true);
  } else if (pfodCmd == "nm"){
    // manual: mower ON/OFF
    robot->motorMowEnable = !robot->motorMowEnable;            
    sendManualMenu(true);
  } else if (pfodCmd == "ns"){
    // manual: stop
    //setNextState(STATE_OFF, 0);          
    robot->motorLeftSpeedRpmSet  =  robot->motorRightSpeedRpmSet = 0;      
    sendManualMenu(true);
  }  
}

void RemoteControl::processSettingsMenu(String pfodCmd){   
  if (pfodCmd == "s1") sendMotorMenu(false);
      else if (pfodCmd == "s2") sendMowMenu(false);
      else if (pfodCmd == "s3") sendBumperMenu(false);
      else if (pfodCmd == "s4") sendSonarMenu(false);
      else if (pfodCmd == "s5") sendPerimeterMenu(false);
      else if (pfodCmd == "s6") sendLawnSensorMenu(false);
      else if (pfodCmd == "s7") sendImuMenu(false);
      else if (pfodCmd == "s8") sendRemoteMenu(false);
      else if (pfodCmd == "s9") sendBatteryMenu(false);
      else if (pfodCmd == "s10") sendStationMenu(false);
      else if (pfodCmd == "s11") sendOdometryMenu(false);
      else if (pfodCmd == "s12") sendDateTimeMenu(false);      
      else if (pfodCmd == "s13") sendRainMenu(false);            
      else if (pfodCmd == "s15") sendDropMenu(false);
      else if (pfodCmd == "s14") sendGPSMenu(false);
      else if (pfodCmd == "sx") sendFactorySettingsMenu(false);
      else if (pfodCmd == "sz") { robot->saveUserSettings(); sendSettingsMenu(true); }
      else sendSettingsMenu(true);  
}      

// process pfodState
void RemoteControl::run(){  
  if (pfodState == PFOD_LOG_SENSORS){
      //robot->printInfo(Bluetooth);
      //Bluetooth.println("test");
      Bluetooth.print((float(millis())/1000.0f));
      Bluetooth.print(",");            
      Bluetooth.print(robot->motorLeftSense);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorRightSense);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorMowSense);
      Bluetooth.print(",");
      Bluetooth.print(robot->sonarDistLeft);
      Bluetooth.print(",");
      Bluetooth.print(robot->sonarDistCenter);
      Bluetooth.print(",");
      Bluetooth.print(robot->sonarDistRight);
      Bluetooth.print(",");
      Bluetooth.print(robot->perimeter.isInside(0));
      Bluetooth.print(",");            
      Bluetooth.print(robot->perimeterMag);
      Bluetooth.print(",");
      Bluetooth.print(robot->odometryLeft);
      Bluetooth.print(",");
      Bluetooth.print(robot->odometryRight);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.ypr.yaw/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.ypr.pitch/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.ypr.roll/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.gyro.x/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.gyro.y/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.gyro.z/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.acc.x);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.acc.y);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.acc.z);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.com.x);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.com.y);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.com.z);
      Bluetooth.print(",");
      float lat, lon;
      unsigned long age;
      robot->gps.f_get_position(&lat, &lon, &age);
      Bluetooth.print(robot->gps.hdop());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.satellites());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.f_speed_kmph());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.f_course());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.f_altitude());
      Bluetooth.print(",");
      Bluetooth.print(lat);
      Bluetooth.print(",");
      Bluetooth.print(lon);           
      Bluetooth.println();      
  } else if (pfodState == PFOD_PLOT_BAT){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 60000;
      Bluetooth.print(((unsigned long)millis()/60000));
      Bluetooth.print(",");
      Bluetooth.print(robot->batVoltage);
      Bluetooth.print(",");
      Bluetooth.print(robot->chgVoltage);
      Bluetooth.print(",");
      Bluetooth.print(robot->chgCurrent);         
      Bluetooth.print(",");
      Bluetooth.println(robot->batCapacity);         
    }
  } else if (pfodState == PFOD_PLOT_ODO2D){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 500;
      Bluetooth.print(robot->odometryX);
      Bluetooth.print(",");
      Bluetooth.println(robot->odometryY);
    }
  } else if (pfodState == PFOD_PLOT_IMU){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Bluetooth.print((float(millis())/1000.0f));
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.ypr.yaw/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.ypr.pitch/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.ypr.roll/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.gyro.x/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.gyro.y/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.gyro.z/PI*180);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.acc.x);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.acc.y);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.acc.z);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.com.x);
      Bluetooth.print(",");
      Bluetooth.print(robot->imu.com.y);
      Bluetooth.print(",");
      Bluetooth.println(robot->imu.com.z);
    }
  } else if (pfodState == PFOD_PLOT_SENSOR_COUNTERS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Bluetooth.print((float(millis())/1000.0f));
      Bluetooth.print(",");
      Bluetooth.print(robot->stateCurr);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorLeftSenseCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorRightSenseCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorMowSenseCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->bumperLeftCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->bumperRightCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->sonarDistCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->perimeterCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->lawnSensorCounter);
      Bluetooth.print(",");
      Bluetooth.print(robot->rainCounter);
      Bluetooth.print(",");      
      Bluetooth.print(robot->dropLeftCounter);
      Bluetooth.print(",");
      Bluetooth.println(robot->dropRightCounter);
    }
  } else if (pfodState == PFOD_PLOT_SENSORS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Bluetooth.print((float(millis())/1000.0f));
      Bluetooth.print(",");
      Bluetooth.print(robot->stateCurr);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorLeftSense);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorRightSense);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorMowSense);
      Bluetooth.print(",");
      Bluetooth.print(robot->sonarDistLeft);
      Bluetooth.print(",");
      Bluetooth.print(robot->sonarDistCenter);
      Bluetooth.print(",");
      Bluetooth.print(robot->sonarDistRight);
      Bluetooth.print(",");
      Bluetooth.print(robot->perimeter.isInside(0));
      Bluetooth.print(",");      
      Bluetooth.print(robot->lawnSensor);
      Bluetooth.print(",");      
      Bluetooth.print(robot->rain);
      Bluetooth.print(",");
      Bluetooth.print(robot->dropLeft);
      Bluetooth.print(",");
      Bluetooth.println(robot->dropRight);    
    }
  } else if (pfodState == PFOD_PLOT_PERIMETER){    
    if (millis() >= nextPlotTime){
      if (perimeterCaptureIdx == 32*3){
        if (ADCMan.isCaptureComplete(A5)){
          int8_t *samples = ADCMan.getCapture(A5);      
          memcpy(perimeterCapture, samples, 32);
          perimeterCaptureIdx = 0;
        }
      }
      if (perimeterCaptureIdx < 32*3){      
        nextPlotTime = millis() + 200;            
        Bluetooth.print(perimeterCapture[perimeterCaptureIdx / 3]);          
        Bluetooth.print(",");                    
        Bluetooth.print(robot->perimeterMag);
        Bluetooth.print(",");
        Bluetooth.print(robot->perimeter.getSmoothMagnitude(0));
        Bluetooth.print(",");
        Bluetooth.print(robot->perimeter.isInside(0));
        Bluetooth.print(",");
        Bluetooth.print(robot->perimeterCounter);
        Bluetooth.print(",");        
        Bluetooth.print(!robot->perimeter.signalTimedOut(0));        
        Bluetooth.print(",");                
        Bluetooth.println(robot->perimeter.getFilterQuality(0));                
        perimeterCaptureIdx++;
      }
    }
  } else if (pfodState == PFOD_PLOT_GPS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      float lat, lon;
      unsigned long age;
      robot->gps.f_get_position(&lat, &lon, &age);
      Bluetooth.print((float(millis())/1000.0f));
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.hdop());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.satellites());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.f_speed_kmph());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.f_course());
      Bluetooth.print(",");
      Bluetooth.print(robot->gps.f_altitude());
      Bluetooth.print(",");
      Bluetooth.print(lat);
      Bluetooth.print(",");
      Bluetooth.println(lon);
    }
  } else if (pfodState == PFOD_PLOT_GPS2D){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 500;
      Bluetooth.print(robot->gpsX);
      Bluetooth.print(",");
      Bluetooth.println(robot->gpsY);
    }
  } else if (pfodState == PFOD_PLOT_MOTOR){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 50;
      Bluetooth.print((float(millis())/1000.0f));
      Bluetooth.print(",");
      Bluetooth.print(robot->motorLeftRpmCurr);
      Bluetooth.print(",");
      Bluetooth.print(robot->motorRightRpmCurr);
      Bluetooth.print(",");
      //      Bluetooth.print(robot->motorLeftSpeedRpmSet);
      Bluetooth.print(robot->motorLeftPID.w);
      Bluetooth.print(",");            
      //      Bluetooth.print(robot->motorRightSpeedRpmSet);
      Bluetooth.print(robot->motorRightPID.w);
      Bluetooth.print(",");            
      Bluetooth.print(robot->motorLeftPWMCurr);      
      Bluetooth.print(",");                    
      Bluetooth.print(robot->motorRightPWMCurr);
      Bluetooth.print(",");                                  
      Bluetooth.print(robot->motorLeftPID.eold);      
      Bluetooth.print(",");                        
      Bluetooth.println(robot->motorRightPID.eold);            
    }
  }
}

// process serial input from pfod App
bool RemoteControl::readSerial(){
  bool res = false;
  while(Bluetooth.available() > 0){
    res = true;
    if (Bluetooth.available() > 0) {
      char ch = Bluetooth.read();
      //Console.print("pfod ch=");
      //Console.println(ch);
      if (ch == '}') pfodCmdComplete = true; 
        else if (ch == '{') pfodCmd = "";
        else pfodCmd += ch;                
    }
    if (pfodCmdComplete) {
      Console.print("pfod cmd=");
      Console.println(pfodCmd);
      pfodState = PFOD_MENU;    
      if (pfodCmd == ".") sendMainMenu(false);      
        else if (pfodCmd == "m1") {
          // log raw sensors
          Bluetooth.println(F("{=Log sensors}"));
          Bluetooth.print(F("time,leftsen,rightsen,mowsen,sonleft,soncenter,sonright,"));
          Bluetooth.print(F("perinside,permag,odoleft,odoright,yaw,pitch,roll,gyrox,gyroy,"));
          Bluetooth.print(F("gyroz,accx,accy,accz,comx,comy,comz,hdop,sats,gspeed,gcourse,"));
          Bluetooth.println(F("galt,lat,lon"));              
          pfodState = PFOD_LOG_SENSORS;
        }  
        else if (pfodCmd == "y1") {
          // plot battery
          Bluetooth.println(F("{=battery|time min`0|battery V`1|charge V`1|charge A`2|capacity Ah`3}")); 
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_BAT;
        }
        else if (pfodCmd == "y2") {
          // plot odometry 2d
          Bluetooth.println(F("{=odometry2d|position`0~~~x|`~~~y}"));         
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_ODO2D;
        }
        else if (pfodCmd == "y3") {        
          // plot IMU
          Bluetooth.print(F("{=IMU`60|time s`0|yaw`1~180~-180|pitch`1|roll`1|gyroX`2~90~-90|gyroY`2|gyroZ`2|accX`3~2~-2|accY`3|accZ`3"));
          Bluetooth.println(F("|comX`4~2~-2|comY`4|comZ`4}"));         
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_IMU;
        }
        else if (pfodCmd == "y5") {        
          // plot sensor counters
          Bluetooth.print(F("{=Sensor counters`300|time s`0|state`1|motL`2|motR`3|motM`4|bumL`5|bumR`6"));
          Bluetooth.println(F("|son`7|peri`8|lawn`9|rain`10|dropL`11|dropR`12}"));         
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_SENSOR_COUNTERS;
        }
        else if (pfodCmd == "y6") {
          // plot perimeter spectrum
          /*Bluetooth.print(F("{=Perimeter spectrum`"));
          Bluetooth.print(Perimeter.getFilterBinCount());
          Bluetooth.print(F("|freq (Hz)`0|magnitude`0~60~-1|selected band`0~60~-1}"));*/
          Bluetooth.println(F("{=Perimeter`128|sig`1|mag`2|smag`3|in`4|cnt`5|on`6|qty`7}"));                   
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_PERIMETER;          
        }
        else if (pfodCmd == "y7") {
          // plot sensor values
          Bluetooth.print(F("{=Sensors`300|time s`0|state`1|motL`2|motR`3|motM`4|sonL`5|sonC`6"));
          Bluetooth.println(F("|sonR`7|peri`8|lawn`9|rain`10|dropL`11|dropR`12}"));
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_SENSORS;          
        }
        else if (pfodCmd == "y8") {
          // plot GPS 
          Bluetooth.println(F("{=GPS`300|time s`0|hdop`1|sat`2|spd`3|course`4|alt`5|lat`6|lon`7}"));
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_GPS;          
        }
        else if (pfodCmd == "y10") {
          // plot GPS 2d
          Bluetooth.println(F("{=gps2d|position`0~~~x|`~~~y}"));         
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_GPS2D;
        }        
        else if (pfodCmd == "c1") {
          // ADC calibration          
          ADCMan.calibrate();
          robot->beep(2, false);      
        }
        else if (pfodCmd == "y11"){
          // motor control
          Bluetooth.println(F("{=Motor control`300|time s`0|lrpm_curr`1|rrpm_curr`2|lrpm_set`3|rrpm_set`4|lpwm`5|rpwm`6|lerr`7|rerr`8}"));                   
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_MOTOR;
        }              
        else if (pfodCmd == "yp") sendPlotMenu(false);
        else if (pfodCmd == "y4")sendErrorMenu(false);
        else if (pfodCmd == "y9")sendADCMenu(false);
        else if (pfodCmd == "n") sendManualMenu(false);
        else if (pfodCmd == "s") sendSettingsMenu(false);      
        else if (pfodCmd == "r") sendCommandMenu(false);
        else if (pfodCmd == "c") sendCompassMenu(false);
        else if (pfodCmd == "t") sendDateTimeMenu(false);
        else if (pfodCmd == "i") sendTimerMenu(false);   
        else if (pfodCmd == "in") sendInfoMenu(false);        
        else if (pfodCmd.startsWith("s")) processSettingsMenu(pfodCmd);
        else if (pfodCmd.startsWith("r")) processCommandMenu(pfodCmd);
        else if (pfodCmd.startsWith("c")) processCompassMenu(pfodCmd);
        else if (pfodCmd.startsWith("n")) processManualMenu(pfodCmd);    
        else if (pfodCmd.startsWith("a")) processMotorMenu(pfodCmd);       
        else if (pfodCmd.startsWith("o")) processMowMenu(pfodCmd);       
        else if (pfodCmd.startsWith("b")) processBumperMenu(pfodCmd);       
        else if (pfodCmd.startsWith("d")) processSonarMenu(pfodCmd);       
        else if (pfodCmd.startsWith("e")) processPerimeterMenu(pfodCmd);       
        else if (pfodCmd.startsWith("f")) processLawnSensorMenu(pfodCmd);       
        else if (pfodCmd.startsWith("g")) processImuMenu(pfodCmd);       
        else if (pfodCmd.startsWith("h")) processRemoteMenu(pfodCmd);             
        else if (pfodCmd.startsWith("j")) processBatteryMenu(pfodCmd);       
        else if (pfodCmd.startsWith("k")) processStationMenu(pfodCmd);       
        else if (pfodCmd.startsWith("l")) processOdometryMenu(pfodCmd);  
        else if (pfodCmd.startsWith("m")) processRainMenu(pfodCmd);               
        else if (pfodCmd.startsWith("q")) processGPSMenu(pfodCmd);                       
        else if (pfodCmd.startsWith("t")) processDateTimeMenu(pfodCmd);  
        else if (pfodCmd.startsWith("i")) processTimerMenu(pfodCmd);      
        else if (pfodCmd.startsWith("p")) processTimerDetailMenu(pfodCmd);      
        else if (pfodCmd.startsWith("x")) processFactorySettingsMenu(pfodCmd);
        else if (pfodCmd.startsWith("u")) processDropMenu(pfodCmd);            
        else if (pfodCmd.startsWith("v")) processInfoMenu(pfodCmd);                    
        else if (pfodCmd.startsWith("z")) processErrorMenu(pfodCmd);                    
        else {
          // no match
          Bluetooth.println("{}");         
        }
      Bluetooth.flush();
      pfodCmd = "";
      pfodCmdComplete = false;
    }
  }  
  return res;
}



