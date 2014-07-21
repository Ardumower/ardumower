/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
 
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
*/

// Android remote control (pfod App)

#include "pfod.h"
#include "robot.h"
#include "adcman.h"
#include "imu.h"
#include "perimeter.h"

RemoteControl::RemoteControl(Robot *aRobot){
  robot = aRobot;
  pfodCmdComplete = false;
  pfodCmd = "";
  pfodState = PFOD_OFF;
  testmode = 0;
  nextPlotTime = 0;  
  perimeterCaptureIdx = 0;  
}

void RemoteControl::initSerial(int baudrate){
  Serial2.begin(baudrate);   // pfod app  
}

float RemoteControl::stringToFloat(String &s){
  float v;
  char tmp[20];  
  s.toCharArray(tmp, sizeof(tmp));
  v = atof(tmp);    
  //v = strtod(tmp, NULL);
  /*Serial.print(s);
  Serial.print("=");
  Serial.println(v, 6);   */
  return v;
}

void RemoteControl::sendYesNo(int value){
  if (value == 1) Serial2.print("YES");
    else Serial2.print("NO");
}

void RemoteControl::sendOnOff(int value){
   if (value == 1) Serial2.print("ON");
    else Serial2.print("OFF");
}

void RemoteControl::sendTimer(ttimer_t timer){
  if (timer.active) Serial2.print(F("(X)  "));
    else Serial2.print(F("(   )  "));          
  Serial2.print(time2str(timer.startTime));
  Serial2.print("-");
  Serial2.print(time2str(timer.stopTime));
  Serial2.println();
  if (timer.daysOfWeek == B1111111){
    Serial2.print(F("every day"));
  } else {
    int counter= 0;  
    for (int j=0; j < 7; j++){
      if ((timer.daysOfWeek >> j) & 1) {
        if (counter != 0) Serial2.print(",");
        Serial2.print(dayOfWeek[j]);              
        counter++;      
      }
    }
  }
}

void RemoteControl::sendSlider(String cmd, String title, float value, String unit, float scale, float maxvalue, float minvalue){
  Serial2.print("|"); 
  Serial2.print(cmd);  
  Serial2.print("~");    
  Serial2.print(title);
  Serial2.print(" `");      
  Serial2.print(((int)(value/scale)));
  Serial2.print("`");  
  Serial2.print(((int)(maxvalue/scale)));
  Serial2.print("`");
  Serial2.print(((int)(minvalue/scale)));
  Serial2.print("~ ~");
  if (scale == 10) Serial2.print("10");
    else if (scale == 1) Serial2.print("1");
    else if (scale == 0.1) Serial2.print("0.1");
    else if (scale == 0.01) Serial2.print("0.01");
    else if (scale == 0.001) Serial2.print("0.001");
    else if (scale == 0.0001) Serial2.print("0.0001");
}

void RemoteControl::sendPIDSlider(String cmd, String title, PID &pid, float scale, float maxvalue){
  sendSlider(cmd + "p", title + "_P", pid.Kp, "", scale, maxvalue);
  sendSlider(cmd + "i", title + "_I", pid.Ki, "", scale, maxvalue);
  sendSlider(cmd + "d", title + "_D", pid.Kd, "", scale, maxvalue);  
}

void RemoteControl::processSlider(String result, float &value, float scale){
  int idx = result.indexOf('`');
  String s = result.substring(idx + 1);      
  float v = stringToFloat(s);
  value = v * scale;  
}

void RemoteControl::processPIDSlider(String result, String cmd, PID &pid, float scale, float maxvalue){
  int idx = result.indexOf('`');
  String s = result.substring(idx + 1);      
  //Serial.println(tmp);
  float v = stringToFloat(s);
  if (pfodCmd.startsWith(cmd + "p")) pid.Kp = v * scale;
    else if (pfodCmd.startsWith(cmd + "i")) pid.Ki = v * scale;
    else if (pfodCmd.startsWith(cmd + "d")) pid.Kd = v * scale;      
}


void RemoteControl::processSlider(String result, long &value, float scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}

void RemoteControl::processSlider(String result, int &value, float scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}

void RemoteControl::processSlider(String result, byte &value, float scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}

void RemoteControl::processSlider(String result, short &value, float scale){
  float v;
  processSlider(result, v, scale);
  value = v;
}
    
void RemoteControl::sendMainMenu(boolean update){
  if (update) Serial2.print("{:"); else {
    Serial2.print(F("{.Ardumower"));  
    Serial2.print(" (");
    Serial2.print(robot->name);
    Serial2.print(")");
  }
  Serial2.print(F("|r~Commands|n~Manual|s~Settings|in~Info|c~Test compass|ardumag~Monitor compass|yp~Plot"));
  Serial2.println(F("|y4~Error counters}"));        
}

void RemoteControl::sendPlotMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Plot"));           
  Serial2.print(F("|y7~Sensors|y5~Sensor counters|y3~IMU|y6~Perimeter|y8~GPS"));   
  Serial2.println(F("|y1~Battery|y2~Odometry}"));
}  


void RemoteControl::sendSettingsMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Settings"));         
  Serial2.print(F("|s1~Motor|s2~Mow|s3~Bumper|s4~Sonar|s5~Perimeter|s6~Lawn sensor|s7~IMU|s8~R/C"));
  Serial2.println(F("|s9~Battery|s10~Station|s11~Odometry|i~Timer|s12~Date/time|sx~Factory settings|sz~Save}"));
}  

void RemoteControl::sendErrorMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Error counters`1000"));         
  Serial2.print(F("|zz~Mow sense "));
  Serial2.print(robot->errorCounterMax[ERR_MOW_SENSE]);
  Serial2.print(F("|zz~IMU comm "));
  Serial2.print(robot->errorCounterMax[ERR_IMU_COMM]);
  Serial2.print(F("|zz~IMU tilt "));
  Serial2.print(robot->errorCounterMax[ERR_IMU_TILT]);
  Serial2.print(F("|zz~Perimeter timeout "));
  Serial2.print(robot->errorCounterMax[ERR_PERIMETER_TIMEOUT]);
  Serial2.print(F("|zz~RTC comm "));
  Serial2.print(robot->errorCounterMax[ERR_RTC_COMM]);
  Serial2.print(F("|zz~RTC data "));
  Serial2.print(robot->errorCounterMax[ERR_RTC_DATA]);
  Serial2.println("}");
}  

void RemoteControl::sendMotorMenu(boolean update){  
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Motor`1000"));     
  Serial2.println(F("|a00~Overload Counter l, r "));
  Serial2.print(robot->motorLeftSenseCounter);  
  Serial2.print(", ");
  Serial2.print(robot->motorRightSenseCounter);  
  Serial2.println(F("|a01~Power in Watt l, r "));    
  Serial2.print(robot->motorLeftSense);
  Serial2.print(", ");  
  Serial2.print(robot->motorRightSense);
  Serial2.println(F("|a05~motor current in mA l, r "));    
  Serial2.print(robot->motorLeftSenseCurrent);
  Serial2.print(", ");  
  Serial2.print(robot->motorRightSenseCurrent);      
  sendSlider("a02", F("Power max"), robot->motorPowerMax, "", 0.1, 40);  
  sendSlider("a03", F("calibrate left motor "), robot->motorLeftSenseCurrent, "", 1, 1000, 0);       
  sendSlider("a04", F("calibrate right motor"), robot->motorRightSenseCurrent, "", 1, 1000, 0);      
  Serial2.println(F("|a05~Speed l, r"));    
  Serial2.print(robot->motorLeftPWM);
  Serial2.print(", ");  
  Serial2.print(robot->motorRightPWM);   
  sendSlider("a06", F("Speed max in rpm"), robot->motorSpeedMax, "", 1, 100);    
  sendSlider("a15", F("Speed max in pwm"), robot->motorSpeedMaxPwm, "", 1, 255);    
  sendSlider("a11", F("Accel"), robot->motorAccel, "", 0.001, 0.05);    
  sendSlider("a07", F("Roll time max"), robot->motorRollTimeMax, "", 1, 8000);     
  sendSlider("a08", F("Reverse time"), robot->motorReverseTime, "", 1, 8000);     
  sendSlider("a09", F("Forw time max"), robot->motorForwTimeMax, "", 10, 80000);       
  sendSlider("a12", F("Bidir speed ratio 1"), robot->motorBiDirSpeedRatio1, "", 0.01, 1.0);       
  sendSlider("a13", F("Bidir speed ratio 2"), robot->motorBiDirSpeedRatio2, "", 0.01, 1.0);       
  Serial2.println(F("|a10~Testing is"));    
  switch (testmode){
    case 0: Serial2.print(F("OFF")); break;
    case 1: Serial2.print(F("Left motor forw")); break;
    case 2: Serial2.print(F("Right motor forw")); break;
  }
  Serial2.println(F("|a14~for config file:"));    
  Serial2.println(F("motorSenseScale l, r"));
  Serial2.print(robot->motorSenseLeftScale);
  Serial2.print(", ");  
  Serial2.print(robot->motorSenseRightScale);   
  Serial2.println("}");            
}

void RemoteControl::processMotorMenu(String pfodCmd){      
  if (pfodCmd.startsWith("a02")) processSlider(pfodCmd, robot->motorPowerMax, 0.1);

    else if (pfodCmd.startsWith("a03")){
      processSlider(pfodCmd, robot->motorLeftSenseCurrent, 1);
      robot->motorSenseLeftScale = robot->motorLeftSenseCurrent / max(0,(float)robot->motorLeftSenseADC);                  
}
    else if (pfodCmd.startsWith("a04")){
      processSlider(pfodCmd, robot->motorRightSenseCurrent, 1);
      robot->motorSenseRightScale = robot->motorRightSenseCurrent / max(0,(float)robot->motorRightSenseADC); 
}      
    else if (pfodCmd.startsWith("a06")) processSlider(pfodCmd, robot->motorSpeedMax, 1);
    else if (pfodCmd.startsWith("a15")) processSlider(pfodCmd, robot->motorSpeedMaxPwm, 1);
    else if (pfodCmd.startsWith("a07")) processSlider(pfodCmd, robot->motorRollTimeMax, 1);    
    else if (pfodCmd.startsWith("a08")) processSlider(pfodCmd, robot->motorReverseTime, 1);
    else if (pfodCmd.startsWith("a09")) processSlider(pfodCmd, robot->motorForwTimeMax, 10);
    else if (pfodCmd.startsWith("a11")) processSlider(pfodCmd, robot->motorAccel, 0.001);    
    else if (pfodCmd.startsWith("a12")) processSlider(pfodCmd, robot->motorBiDirSpeedRatio1, 0.01);    
    else if (pfodCmd.startsWith("a13")) processSlider(pfodCmd, robot->motorBiDirSpeedRatio2, 0.01);    
    else if (pfodCmd == "a10") { 
      testmode = (testmode + 1) % 3;
      switch (testmode){
        case 0: robot->setNextState(STATE_OFF,0); break;
        case 1: robot->setNextState(STATE_MANUAL,0); robot->motorRightSpeed = 0; robot->motorLeftSpeed = robot->motorSpeedMax; break;
        case 2: robot->setNextState(STATE_MANUAL,0); robot->motorLeftSpeed  = 0; robot->motorRightSpeed = robot->motorSpeedMax; break;      
      }
    }
  sendMotorMenu(true);
}
  
void RemoteControl::sendMowMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Mow`1000"));               
  Serial2.print(F("|o00~Overload Counter "));
  Serial2.print(robot->motorMowSenseCounter);    
  Serial2.print(F("|o01~Power in Watt "));  
  Serial2.print(robot->motorMowSense);  
  Serial2.print(F("|o11~current in mA "));  
  Serial2.print(robot->motorMowSenseCurrent);  
  sendSlider("o02", F("Power max"), robot->motorMowPowerMax, "", 0.1, 100);         
  sendSlider("o03", F("calibrate mow motor "), robot->motorMowSenseCurrent, "", 1, 3000, 0);          
  Serial2.print(F("|o04~Speed "));
  Serial2.print(robot->motorMowPWM);      
  sendSlider("o05", F("Speed max"), robot->motorMowSpeedMax, "", 1, 255);       
  Serial2.print(F("|o06~Modulate "));
  sendYesNo(robot->motorMowModulate);      
  Serial2.print(F("|o07~RPM "));
  Serial2.print(robot->motorMowRpm);    
  sendSlider("o08", F("RPM set"), robot->motorMowRPM, "", 1, 8000);     
  sendPIDSlider("o09", "RPM", robot->motorMowPid, 0.0001, 0.2);      
  Serial2.println(F("|o10~Testing is"));    
  switch (testmode){
    case 0: Serial2.print(F("OFF")); break;
    case 1: Serial2.print(F("Motor ON")); break;
  }
  Serial2.println(F("|o04~for config file:"));    
  Serial2.println(F("motorMowSenseScale:"));
  Serial2.print(robot->motorMowSenseScale);  
  Serial2.println("}");              
}

void RemoteControl::processMowMenu(String pfodCmd){      
  if (pfodCmd.startsWith("o02")) processSlider(pfodCmd, robot->motorMowPowerMax, 0.1);
    else if (pfodCmd.startsWith("o03")){
            processSlider(pfodCmd, robot->motorMowSenseCurrent, 1);
            robot->motorMowSenseScale = robot->motorMowSenseCurrent / max(0,(float)robot->motorMowSenseADC);
         } 
    else if (pfodCmd.startsWith("o05")) processSlider(pfodCmd, robot->motorMowSpeedMax, 1);
    else if (pfodCmd == "o06") robot->motorMowModulate = !robot->motorMowModulate;    
    else if (pfodCmd.startsWith("o08")) processSlider(pfodCmd, robot->motorMowRPM, 1);    
    else if (pfodCmd.startsWith("o09")) processPIDSlider(pfodCmd, "o09", robot->motorMowPid, 0.0001, 0.2);
    else if (pfodCmd == "o10") { 
      testmode = (testmode + 1) % 2;
      switch (testmode){
        case 0: robot->setNextState(STATE_OFF,0); break;
        case 1: robot->setNextState(STATE_MANUAL,0); robot->motorMowEnable = true; break;
      }
    }    
  sendMowMenu(true);
}

void RemoteControl::sendBumperMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Bumper`1000"));         
  Serial2.print(F("|b00~Use "));
  sendYesNo(robot->bumperUse);    
  Serial2.println(F("|b01~Counter l, r "));
  Serial2.print(robot->bumperLeftCounter);  
  Serial2.print(", ");
  Serial2.print(robot->bumperRightCounter);  
  Serial2.println(F("|b02~Value l, r "));
  Serial2.print(robot->bumperLeft);
  Serial2.print(", ");
  Serial2.print(robot->bumperRight);  
  Serial2.println("}");                
}

void RemoteControl::processBumperMenu(String pfodCmd){      
  if (pfodCmd == "b00") robot->bumperUse = !robot->bumperUse;    
  sendBumperMenu(true);
}

void RemoteControl::sendSonarMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Sonar`1000"));         
  Serial2.print(F("|d00~Use "));
  sendYesNo(robot->sonarUse);
  Serial2.print(F("|d01~Counter "));
  Serial2.print(robot->sonarDistCounter);    
  Serial2.println(F("|d02~Value l, c, r"));
  Serial2.print(robot->sonarDistLeft);
  Serial2.print(", ");
  Serial2.print(robot->sonarDistCenter);
  Serial2.print(", ");
  Serial2.print(robot->sonarDistRight);  
  sendSlider("d03", F("Trigger below"), robot->sonarTriggerBelow, "", 1, 3000);       
  Serial2.println("}");                
}

void RemoteControl::processSonarMenu(String pfodCmd){      
  if (pfodCmd == "d00") robot->sonarUse = !robot->sonarUse;
    else if (pfodCmd.startsWith("d03")) processSlider(pfodCmd, robot->sonarTriggerBelow, 1);
  sendSonarMenu(true);
}

void RemoteControl::sendPerimeterMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Perimeter`1000"));         
  Serial2.print(F("|e00~Use "));
  sendYesNo(robot->perimeterUse);  
  Serial2.println(F("|e02~Value l, r"));
  Serial2.print(robot->perimeterLeft);
  Serial2.print(", ");
  Serial2.print(robot->perimeterRight);    
  sendSlider("e05", F("Track roll time"), robot->perimeterTrackRollTime, "", 1, 8000);       
  sendSlider("e06", F("Track rev time"), robot->perimeterTrackRevTime, "", 1, 8000);         
  sendPIDSlider("e07", F("Track"), robot->perimeterPid, 0.1, 100);  
  Serial2.println("}");                
}

void RemoteControl::processPerimeterMenu(String pfodCmd){      
  if (pfodCmd == "e00") robot->perimeterUse = !robot->perimeterUse;
    else if (pfodCmd.startsWith("e05")) processSlider(pfodCmd, robot->perimeterTrackRollTime, 1);
    else if (pfodCmd.startsWith("e06")) processSlider(pfodCmd, robot->perimeterTrackRevTime, 1);
    else if (pfodCmd.startsWith("e07")) processPIDSlider(pfodCmd, "e07", robot->perimeterPid, 0.1, 100);    
  sendPerimeterMenu(true);
}

void RemoteControl::sendLawnSensorMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Lawn sensor`1000"));         
  Serial2.print(F("|f00~Use "));
  sendYesNo(robot->lawnSensorUse);  
  Serial2.print(F("|f01~Counter "));
  Serial2.print(robot->lawnSensorCounter);      
  Serial2.println(F("|f02~Value f, b"));
  Serial2.print(robot->lawnSensorFront); 
  Serial2.print(", "); 
  Serial2.print(robot->lawnSensorBack);   
  Serial2.println("}");                
}

void RemoteControl::processLawnSensorMenu(String pfodCmd){      
  if (pfodCmd == "f00") robot->lawnSensorUse = !robot->lawnSensorUse;
  sendLawnSensorMenu(true);
}

void RemoteControl::sendImuMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.IMU`1000"));         
  Serial2.print(F("|g00~Use "));  
  sendYesNo(robot->imuUse);
  Serial2.print(F("|g01~Yaw "));
  Serial2.print(robot->imuYaw/PI*180);
  Serial2.print(F(" deg"));  
  Serial2.print(F("|g02~Pitch "));
  Serial2.print(robot->imuPitch/PI*180);
  Serial2.print(F(" deg"));  
  Serial2.print(F("|g03~Roll "));
  Serial2.print(robot->imuRoll/PI*180);
  Serial2.print(F(" deg"));  
  Serial2.print(F("|g04~Correct dir "));
  sendYesNo(robot->imuCorrectDir);  
  sendPIDSlider("g05", F("Dir"), robot->imuDirPid, 0.1, 20);
  sendPIDSlider("g06", F("Roll"), robot->imuRollPid, 0.1, 30);    
  Serial2.print(F("|g07~Start Com Cal Dev"));
  Serial2.println("}");                
}

void RemoteControl::processImuMenu(String pfodCmd){      
  if (pfodCmd == "g00" ) robot->imuUse = !robot->imuUse;
    else if (pfodCmd == "g04" ) robot->imuCorrectDir = !robot->imuCorrectDir;
    else if (pfodCmd.startsWith("g05")) processPIDSlider(pfodCmd, "g05", robot->imuDirPid, 0.1, 20);    
    else if (pfodCmd.startsWith("g06")) processPIDSlider(pfodCmd, "g06", robot->imuRollPid, 0.1, 30);    
    else if (pfodCmd == "g07") robot->imuCalibComDeviation();
  sendImuMenu(true);
}

void RemoteControl::sendRemoteMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Remote R/C`1000"));         
  Serial2.print(F("|h00~Use "));
  sendYesNo(robot->remoteUse);  
  Serial2.println("}");                
}

void RemoteControl::processRemoteMenu(String pfodCmd){      
  if (pfodCmd == "h00" ) robot->remoteUse = !robot->remoteUse;    
  sendRemoteMenu(true);
}

void RemoteControl::sendBatteryMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Battery`1000"));           
  Serial2.print(F("|j00~Battery "));
  Serial2.print(robot->batVoltage);
  Serial2.print(" V");
  Serial2.print(F("|j01~Monitor "));  
  sendYesNo(robot->batMonitor);
  sendSlider("j05", F("Calibrate battery V "), robot->batVoltage, "", 0.01, 30, 0);   
  sendSlider("j02", F("Go home if below"), robot->batGoHomeIfBelow, "", 0.1, robot->batFull, (robot->batFull*0.72));  // for Sony Konion cells 4.2V * 0,72= 3.024V which is pretty safe to use 
  sendSlider("j03", F("Switch off if below"), robot->batSwitchOffIfBelow, "", 0.1, robot->batFull, (robot->batFull*0.72));  
  Serial2.print(F("|j04~Charge "));
  Serial2.print(robot->chgVoltage);
  Serial2.print("V ");
  Serial2.print(robot->chgCurrent);
  Serial2.print("A");
  sendSlider("j06", F("Charge sense zero"), robot->chgSenseZero, "", 1, 600, 400);       
  sendSlider("j08", F("Charge factor"), robot->chgFactor, "", 0.01, 10);     
  Serial2.println(F("|j09~for config file: "));
  Serial2.print("batSenseZero ");
  Serial2.println(robot->batSenseZero);
  Serial2.print("batFactor ");  
  Serial2.print(robot->batFactor);  
  Serial2.println("}");
}

void RemoteControl::processBatteryMenu(String pfodCmd){      
  if (pfodCmd == "j01") robot->batMonitor = !robot->batMonitor;
    else if (pfodCmd.startsWith("j02")) processSlider(pfodCmd, robot->batGoHomeIfBelow, 0.1);
    else if (pfodCmd.startsWith("j03")) processSlider(pfodCmd, robot->batSwitchOffIfBelow, 0.1); 
    else if (pfodCmd.startsWith("j05")) {
      if (robot->batVoltage < 8){        
        robot->batSenseZero = robot->batADC;        
      } else {        
        processSlider(pfodCmd, robot->batVoltage, 0.01);
        robot->batFactor = robot->batVoltage / max(0, (((float)robot->batADC)-robot->batSenseZero));        
      }      
    }
    else if (pfodCmd.startsWith("j06")) processSlider(pfodCmd, robot->chgSenseZero, 1);   
    else if (pfodCmd.startsWith("j08")) processSlider(pfodCmd, robot->chgFactor, 0.01);    
  sendBatteryMenu(true);
}

void RemoteControl::sendStationMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Station`1000"));         
  sendSlider("k00", F("Reverse time"), robot->stationRevTime, "", 1, 8000);     
  sendSlider("k01", F("Roll time"), robot->stationRollTime, "", 1, 8000);       
  sendSlider("k02", F("Forw time"), robot->stationForwTime, "", 1, 8000);         
  Serial2.println("}");                
}

void RemoteControl::processStationMenu(String pfodCmd){      
  if (pfodCmd.startsWith("k00")) processSlider(pfodCmd, robot->stationRevTime, 1);
    else if (pfodCmd.startsWith("k01")) processSlider(pfodCmd, robot->stationRollTime, 1);
    else if (pfodCmd.startsWith("k02")) processSlider(pfodCmd, robot->stationForwTime, 1);
  sendStationMenu(true);
}

void RemoteControl::sendOdometryMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Odometry`1000"));         
  Serial2.print(F("|l00~Use "));
  sendYesNo(robot->odometryUse);  
  Serial2.print(F("|l01~Value l, r "));
  Serial2.print(robot->odometryLeft);
  Serial2.print(", "); 
  Serial2.println(robot->odometryRight); 
  Serial2.println(F("|l03~RPM Motor l, r "));
  Serial2.print(robot->motorLeftRpm);
  Serial2.print(", "); 
  Serial2.println(robot->motorRightRpm);
  sendSlider("l04", F("Ticks per one full revolution"), robot->odometryTicksPerRevolution, "", 1, 2000);       
  sendSlider("l01", F("Ticks per cm"), robot->odometryTicksPerCm, "", 0.1, 30);       
  sendSlider("l02", F("Wheel base cm"), robot->odometryWheelBaseCm, "", 0.1, 50);         
  Serial2.println("}");                
}


void RemoteControl::processOdometryMenu(String pfodCmd){      
  if (pfodCmd == "l00") robot->odometryUse = !robot->odometryUse;
    else if (pfodCmd.startsWith("l01")) processSlider(pfodCmd, robot->odometryTicksPerCm, 0.1);
    else if (pfodCmd.startsWith("l02")) processSlider(pfodCmd, robot->odometryWheelBaseCm, 0.1); 
    else if (pfodCmd.startsWith("l04")) processSlider(pfodCmd, robot->odometryTicksPerRevolution, 1);    
   
  sendOdometryMenu(true);
}

void RemoteControl::sendDateTimeMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Date/time"));         
  Serial2.print("|t00~");  
  Serial2.print(date2str(robot->datetime.date));  
  Serial2.print(", ");
  Serial2.print(time2str(robot->datetime.time));  
  sendSlider("t01", dayOfWeek[robot->datetime.date.dayOfWeek], robot->datetime.date.dayOfWeek, "", 1, 6, 0);       
  sendSlider("t02", "Day ", robot->datetime.date.day, "", 1, 31, 1);       
  sendSlider("t03", "Month ", robot->datetime.date.month, "", 1, 12, 1);       
  sendSlider("t04", "Year ", robot->datetime.date.year, "", 1, 2020, 2013);       
  sendSlider("t05", "Hour ", robot->datetime.time.hour, "", 1, 23, 0);       
  sendSlider("t06", "Minute ", robot->datetime.time.minute, "", 1, 59, 0);           
  Serial2.println("}");                
}

void RemoteControl::processDateTimeMenu(String pfodCmd){      
  if (pfodCmd.startsWith("t01")) processSlider(pfodCmd, robot->datetime.date.dayOfWeek, 1);    
    else if (pfodCmd.startsWith("t02")) processSlider(pfodCmd, robot->datetime.date.day, 1);
    else if (pfodCmd.startsWith("t03")) processSlider(pfodCmd, robot->datetime.date.month, 1);
    else if (pfodCmd.startsWith("t04")) processSlider(pfodCmd, robot->datetime.date.year, 1);
    else if (pfodCmd.startsWith("t05")) processSlider(pfodCmd, robot->datetime.time.hour, 1);
    else if (pfodCmd.startsWith("t06")) processSlider(pfodCmd, robot->datetime.time.minute, 1);    
  sendDateTimeMenu(true);
  robot->setActuator(ACT_RTC, 0);            
}

void RemoteControl::sendTimerDetailMenu(int timerIdx, boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Details"));         
  Serial2.print("|p0");
  Serial2.print(timerIdx);
  Serial2.print("~Use ");  
  sendYesNo(robot->timer[timerIdx].active);        
  int startm = time2minutes(robot->timer[timerIdx].startTime);
  int stopm = time2minutes(robot->timer[timerIdx].stopTime);
  String sidx = String(timerIdx);
  sendSlider("p1"+sidx, F("Start hour "), robot->timer[timerIdx].startTime.hour, "", 1, 23, 0);       
  sendSlider("p2"+sidx, F("Start minute "), robot->timer[timerIdx].startTime.minute, "", 1, 59, 0);         
  sendSlider("p3"+sidx, F("Stop hour "), robot->timer[timerIdx].stopTime.hour, "", 1, 23, 0);       
  sendSlider("p4"+sidx, F("Stop minute "), robot->timer[timerIdx].stopTime.minute, "", 1, 59, 0);             
  for (int i=0; i < 7; i++){
    Serial2.print("|p5");
    Serial2.print(timerIdx);    
    Serial2.print(i);    
    Serial2.print("~");
    if ((robot->timer[timerIdx].daysOfWeek >> i) & 1) Serial2.print("(X)  ");
      else Serial2.print("(  )  ");   
    Serial2.print(dayOfWeek[i]);              
  }
  Serial2.print("|p9");
  Serial2.print(timerIdx);
  Serial2.print(F("~Set to current time"));  
  Serial2.println("}");                      
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
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Timer"));         
  Serial2.print(F("|i99~Use "));
  sendYesNo(robot->timerUse);      
  for (int i=0; i < MAX_TIMERS; i++){
    Serial2.print("|i0");
    Serial2.print(i);
    Serial2.print("~");
    sendTimer(robot->timer[i]);    
  }
  Serial2.println("}");                
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
  if (update) Serial2.print("{:"); else Serial2.println(F("{.Factory settings"));
  Serial2.print(F("|x0~Set factory settings (requires reboot)"));
  Serial2.println("}");
}

void RemoteControl::processFactorySettingsMenu(String pfodCmd){      
  if (pfodCmd == "x0") robot->deleteUserSettings();
  sendFactorySettingsMenu(true);
}

void RemoteControl::sendInfoMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Info"));     
  Serial2.print(F("|d00~Ardumower v"));
  Serial2.print(verToString(VER)); 
  //Serial2.print("|d01~Perimeter v");
  //Serial2.print(verToString(readPerimeterVer())); 
  //Serial2.print("|d02~IMU v");  
  //Serial2.print(verToString(readIMUver())); 
  //Serial2.print("|d02~Stepper v");  
  //Serial2.print(verToString(readStepperVer())); 
  Serial2.println("}");        
}

void RemoteControl::sendCommandMenu(boolean update){  
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Commands`5000"));  
  Serial2.print(F("|ro~OFF|ra~Auto mode|rc~RC mode|"));
  Serial2.print(F("rm~Mowing is "));  
  sendOnOff(robot->motorMowEnable);  
  Serial2.print(F("|rp~Pattern is "));
  Serial2.print(robot->mowPatternName());
  Serial2.print(F("|rh~Home|rk~Track|rs~State is "));         
  Serial2.print(robot->stateName());
  Serial2.print(F("|rr~Auto rotate is "));
  Serial2.print(robot->motorLeftPWM);      
  Serial2.print(F("|r1~User switch 1 is "));         
  sendOnOff(robot->userSwitch1);  
  Serial2.print(F("|r2~User switch 2 is "));         
  sendOnOff(robot->userSwitch2);  
  Serial2.print(F("|r3~User switch 3 is "));         
  sendOnOff(robot->userSwitch3);  
  Serial2.print("}");
  Serial2.println();
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
    robot->motorLeftSpeed += 10; robot->motorRightSpeed = -robot->motorLeftSpeed;      
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
  if (update) Serial2.print("{:"); else Serial2.println(F("{^Manual navigation`1000"));
  Serial2.print(F("|nl~Left|nr~Right|nf~Forward"));
  if (   ((robot->motorLeftSpeed  < 5)  && (robot->motorLeftSpeed  > -5))
     &&  ((robot->motorRightSpeed < 5)  && (robot->motorRightSpeed > -5))  ){
    Serial2.print(F("|nb~Reverse"));
  } else Serial2.print(F("|ns~Stop"));  
  Serial2.print(F("|nm~Mow is "));
  sendOnOff(robot->motorMowEnable);  
  Serial2.println("}");
}

void RemoteControl::sendCompassMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.println(F("{^Compass`1000"));
  Serial2.print(F("|cw~West|ce~East|cn~North "));
  Serial2.print(robot->imuYaw/PI*180);
  Serial2.println(F("|cs~South|cm~Mow}"));  
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
    if (robot->motorLeftSpeed < 0) sign = -1.0;      
    if (sign*robot->motorLeftSpeed >= sign*robot->motorRightSpeed) robot->motorLeftSpeed  = sign * robot->motorSpeedMax/2;      
        else robot->motorLeftSpeed /= 2; 
    robot->motorRightSpeed = sign * robot->motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nr"){      
    // manual: right
    robot->setNextState(STATE_MANUAL, 0);          
    float sign = 1.0;
    if (robot->motorRightSpeed < 0) sign = -1.0;
    if (sign*robot->motorRightSpeed >= sign*robot->motorLeftSpeed) robot->motorRightSpeed  = sign* robot->motorSpeedMax/2;
        else robot->motorRightSpeed /= 2;            
    robot->motorLeftSpeed  = sign * robot->motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nf"){
    // manual: forward
    robot->setNextState(STATE_MANUAL, 0);          
    robot->motorLeftSpeed  = robot->motorSpeedMax;
    robot->motorRightSpeed = robot->motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nb"){
    // manual: reverse
    robot->setNextState(STATE_MANUAL, 0);          
    robot->motorLeftSpeed  = -robot->motorSpeedMax;
    robot->motorRightSpeed = -robot->motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nm"){
    // manual: mower ON/OFF
    robot->motorMowEnable = !robot->motorMowEnable;            
    sendManualMenu(true);
  } else if (pfodCmd == "ns"){
    // manual: stop
    //setNextState(STATE_OFF, 0);          
    robot->motorLeftSpeed  =  robot->motorRightSpeed = 0;      
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
      else if (pfodCmd == "sx") sendFactorySettingsMenu(false);
      else if (pfodCmd == "sz") { robot->saveUserSettings(); sendSettingsMenu(true); }
      else sendSettingsMenu(true);  
}      

void RemoteControl::processArduMagResult(String pfodCmd){  
  // format:  ardumagMij|float
  // examples: 
  //   ardumagB00|987.4565  
  //   ardumagA22|-34.998
  if (pfodCmd.startsWith("ardumag")) {
    int type;
    if (pfodCmd[7] == 'B') type = 0;
      else type = 1;
    int i = pfodCmd[8]-'0';
    int j = pfodCmd[9]-'0';
    String s = pfodCmd.substring(11);        
    //Serial.println(tmp);
    float value = stringToFloat(s);    
    /*Serial.print("type=");
    Serial.print(type);
    Serial.print(", i=");
    Serial.print(i);
    Serial.print(", j=");
    Serial.print(j);
    Serial.print(", value=");
    Serial.println(value);*/
    robot->imuSetComCalParam(type, i, j, value);
    if ((type == 1) && (i==2) && (j==2)) {
      robot->imuSaveCalib();
      robot->beep(2, false);      
    }
  }    
}

// process pfodState
void RemoteControl::run(){  
  if (pfodState == PFOD_ARDU_MAG){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;      
      // output raw compass values (ArduMag state)
      point_float_t v;
      robot->imuGetComRaw(v);
      Serial2.print(v.x);
      Serial2.print("\t");
      Serial2.print(v.y);
      Serial2.print("\t");
      Serial2.println(v.z);    
    }
  } else if (pfodState == PFOD_MONITOR){
    robot->printInfo(Serial2);
    //Serial2.println("test");
  } else if (pfodState == PFOD_PLOT_BAT){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 60000;
      Serial2.print(((unsigned long)millis()/60000));
      Serial2.print(",");
      Serial2.print(robot->batVoltage);
      Serial2.print(",");
      Serial2.print(robot->chgVoltage);
      Serial2.print(",");
      Serial2.print(robot->chgCurrent);         
      Serial2.print(",");
      Serial2.println(robot->batCapacity);         
    }
  } else if (pfodState == PFOD_PLOT_ODO){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 500;
      Serial2.print(robot->odometryX);
      Serial2.print(",");
      Serial2.println(robot->odometryY);
    }
  } else if (pfodState == PFOD_PLOT_IMU){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Serial2.print((float(millis())/1000.0f));
      Serial2.print(",");
      Serial2.print(robot->imuYaw/PI*180);
      Serial2.print(",");
      Serial2.print(robot->imuPitch/PI*180);
      Serial2.print(",");
      Serial2.println(robot->imuRoll/PI*180);
      //Serial2.print(",");
      /*Serial2.print(robot->imu.gyro.x/PI*180);
      Serial2.print(",");
      Serial2.print(robot->imu.gyro.y/PI*180);
      Serial2.print(",");
      Serial2.print(robot->imu.gyro.z/PI*180);
      Serial2.print(",");
      Serial2.print(robot->imu.gyroYpr.yaw/PI*180);
      Serial2.print(",");
      Serial2.print(robot->imu.gyroYpr.pitch/PI*180);
      Serial2.print(",");
      Serial2.print(robot->imu.gyroYpr.roll/PI*180);
      Serial2.print(",");            
      Serial2.print(robot->imu.acc.x);
      Serial2.print(",");
      Serial2.print(robot->imu.acc.y);
      Serial2.print(",");
      Serial2.print(robot->imu.acc.z);
      Serial2.print(",");
      Serial2.print(robot->imu.accGrav.x);
      Serial2.print(",");
      Serial2.print(robot->imu.accGrav.y);
      Serial2.print(",");
      Serial2.print(robot->imu.accGrav.z);
      Serial2.print(",");
      Serial2.print(robot->imu.com.x);
      Serial2.print(",");
      Serial2.print(robot->imu.com.y);
      Serial2.print(",");
      Serial2.println(robot->imu.com.z);*/
    }
  } else if (pfodState == PFOD_PLOT_SENSOR_COUNTERS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Serial2.print((float(millis())/1000.0f));
      Serial2.print(",");
      Serial2.print(robot->stateCurr);
      Serial2.print(",");
      Serial2.print(robot->motorLeftSenseCounter);
      Serial2.print(",");
      Serial2.print(robot->motorRightSenseCounter);
      Serial2.print(",");
      Serial2.print(robot->motorMowSenseCounter);
      Serial2.print(",");
      Serial2.print(robot->bumperLeftCounter);
      Serial2.print(",");
      Serial2.print(robot->bumperRightCounter);
      Serial2.print(",");
      Serial2.print(robot->sonarDistCounter);
      Serial2.print(",");
      Serial2.print(robot->perimeterLeftCounter);
      Serial2.print(",");
      Serial2.println(robot->lawnSensorCounter);
    }
  } else if (pfodState == PFOD_PLOT_SENSORS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Serial2.print((float(millis())/1000.0f));
      Serial2.print(",");
      Serial2.print(robot->stateCurr);
      Serial2.print(",");
      Serial2.print(robot->motorLeftSense);
      Serial2.print(",");
      Serial2.print(robot->motorRightSense);
      Serial2.print(",");
      Serial2.print(robot->motorMowSense);
      Serial2.print(",");
      Serial2.print(robot->sonarDistLeft);
      Serial2.print(",");
      Serial2.print(robot->sonarDistCenter);
      Serial2.print(",");
      Serial2.print(robot->sonarDistRight);
      Serial2.print(",");
      Serial2.println(Perimeter.isInside());
    }
  } else if (pfodState == PFOD_PLOT_PERIMETER){    
    if (millis() >= nextPlotTime){
      if (perimeterCaptureIdx == 32){
        if (ADCMan.isCaptureComplete(A5)){
          int8_t *samples = ADCMan.getCapture(A5);      
          memcpy(perimeterCapture, samples, 32);
          perimeterCaptureIdx = 0;
        }
      }
      if (perimeterCaptureIdx < 32){      
        nextPlotTime = millis() + 200;            
        Serial2.print(perimeterCapture[perimeterCaptureIdx]);          
        Serial2.print(",");                    
        Serial2.print(robot->perimeterLeft);
        Serial2.print(",");
        Serial2.print(Perimeter.getSmoothMagnitude());
        Serial2.print(",");
        Serial2.print(Perimeter.isInside());
        Serial2.print(",");
        Serial2.print(robot->perimeterLeftCounter);
        Serial2.print(",");        
        Serial2.println(!Perimeter.signalTimedOut());        
        perimeterCaptureIdx++;
      }
      /*int filterBin = Perimeter.getFilterBin();
      int binBandwidth = Perimeter.getFilterBandwidth();      
      for (int i=0; i < Perimeter.getFilterBinCount(); i++) {                
        Serial2.print(i * binBandwidth);
        Serial2.print(",");
        int mag = Perimeter.getSpectrum(i);        
          if ((i==0) || (i==Perimeter.getFilterBinCount()-1)) Serial2.print(0);
            else Serial2.print(mag);
        Serial2.print(",");
        if (i == filterBin) Serial2.println(60); 
            else Serial2.println(0);                    
      } */     
    }
  } else if (pfodState == PFOD_PLOT_GPS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      float lat, lon;
      unsigned long age;
      /*gps.f_get_position(&lat, &lon, &age);
      Serial2.print((float(millis())/1000.0f));
      Serial2.print(",");
      Serial2.print(gps.hdop());
      Serial2.print(",");
      Serial2.print(gps.satellites());
      Serial2.print(",");
      Serial2.print(gps.f_speed_kmph());
      Serial2.print(",");
      Serial2.print(gps.f_course());
      Serial2.print(",");
      Serial2.print(gps.f_altitude());
      Serial2.print(",");
      Serial2.print(lat);
      Serial2.print(",");
      Serial2.println(lon);*/
    }
  }
}

// process serial input from pfod App
void RemoteControl::readSerial(){
  while(Serial2.available() > 0){
    if (Serial2.available() > 0) {
      char ch = Serial2.read();
      //Serial.print("pfod ch=");
      //Serial.println(ch);
      if (ch == '}') pfodCmdComplete = true; 
        else if (ch == '{') pfodCmd = "";
        else pfodCmd += ch;                
    }
    if (pfodCmdComplete) {
      Serial.print("pfod cmd=");
      Serial.println(pfodCmd);
      pfodState = PFOD_MENU;    
      if (pfodCmd == ".") sendMainMenu(false);      
        else if (pfodCmd == "ardumag") {
          // set compass calibration state (ArduMag)
          robot->beep(1, false);
          Serial2.println(F("{=monitor compass}")); 
          pfodState = PFOD_ARDU_MAG;
        }      
        else if (pfodCmd == "m1") {
          // set monitor counter state
          Serial2.println(F("{=monitor counters}")); 
          robot->consoleMode = CONSOLE_SENSOR_COUNTERS;
          pfodState = PFOD_MONITOR;
        }  
        else if (pfodCmd == "m2"){
          // set monitor values state
          Serial2.println(F("{=monitor values}")); 
          robot->consoleMode = CONSOLE_SENSOR_VALUES;
          pfodState = PFOD_MONITOR;
        } 
        else if (pfodCmd == "y1") {
          // plot battery
          Serial2.println(F("{=battery|time min`0|battery V`1|charge V`1|charge A`2|capacity Ah`3}")); 
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_BAT;
        }
        else if (pfodCmd == "y2") {
          // plot odometry
          Serial2.println(F("{=odometry|position`0~~~x|`~~~y}"));         
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_ODO;
        }
        else if (pfodCmd == "y3") {        
          // plot IMU
          Serial2.print(F("{=IMU`60|time s`0|yaw`1~180~-180|pitch`1|roll`1|gyroX`2~90~-90|gyroY`2|gyroZ`2|gyroY`3~180~-180|gyroP`3|gyroR`3|accX`4~2~-2|accY`4|accZ`4"));
          Serial2.println(F("|acgX`5~2~-2|acgY`5|acgZ`5|comX`6~600~-600|comY`6|comZ`6}"));         
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_IMU;
        }
        else if (pfodCmd == "y5") {        
          // plot sensor counters
          Serial2.print(F("{=Sensor counters`300|time s`0|state`1|motL`2|motR`3|motM`4|bumL`5|bumR`6"));
          Serial2.println(F("|son`7|peri`8|lawn`9}"));         
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_SENSOR_COUNTERS;
        }
        else if (pfodCmd == "y6") {
          // plot perimeter spectrum
          /*Serial2.print(F("{=Perimeter spectrum`"));
          Serial2.print(Perimeter.getFilterBinCount());
          Serial2.print(F("|freq (Hz)`0|magnitude`0~60~-1|selected band`0~60~-1}"));*/
          Serial2.println(F("{=Perimeter`128|sig`1|mag`2|smag`3|in`4|cnt`5|on`6}"));                   
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_PERIMETER;          
        }
        else if (pfodCmd == "y7") {
          // plot sensor values
          Serial2.println(F("{=Sensors`300|time s`0|state`1|motL`2|motR`3|motM`4|sonL`5|sonC`6|sonR`7|peri`8}"));
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_SENSORS;          
        }
        else if (pfodCmd == "y8") {
          // plot GPS 
          Serial2.println(F("{=GPS`300|time s`0|hdop`1|sat`2|spd`3|course`4|alt`5|lat`6|lon`7}"));
          nextPlotTime = 0;
          pfodState = PFOD_PLOT_GPS;          
        }
        else if (pfodCmd == "yp") sendPlotMenu(false);
        else if (pfodCmd == "y4")sendErrorMenu(false);
        else if (pfodCmd == "n") sendManualMenu(false);
        else if (pfodCmd == "s") sendSettingsMenu(false);      
        else if (pfodCmd == "r") sendCommandMenu(false);
        else if (pfodCmd == "c") sendCompassMenu(false);
        else if (pfodCmd == "t") sendDateTimeMenu(false);
        else if (pfodCmd == "i") sendTimerMenu(false);   
        else if (pfodCmd == "in") sendInfoMenu(false);        
        else if (pfodCmd.startsWith("ardumag")) processArduMagResult(pfodCmd);
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
        else if (pfodCmd.startsWith("t")) processDateTimeMenu(pfodCmd);  
        else if (pfodCmd.startsWith("i")) processTimerMenu(pfodCmd);      
        else if (pfodCmd.startsWith("p")) processTimerDetailMenu(pfodCmd);      
        else if (pfodCmd.startsWith("x")) processFactorySettingsMenu(pfodCmd);            
        else {
          // no match
          Serial2.println("{}");         
        }
      Serial2.flush();
      pfodCmd = "";
      pfodCmdComplete = false;
    }
  }  
}



