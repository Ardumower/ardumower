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
#include "ardumower.h"
#include "adcman.h"

boolean pfodCmdComplete = false;
String pfodCmd = "";
byte pfodState = PFOD_OFF;
int testmode = 0;
unsigned long nextPlotTime = 0;
int8_t perimeterCapture[32]; 
int perimeterCaptureIdx = 0;

void initSerialPfod(int baudrate){
  Serial2.begin(baudrate);   // pfod app  
}

double stringToDouble(String &s){
  double v;
  char tmp[20];  
  s.toCharArray(tmp, sizeof(tmp));
  v = atof(tmp);    
  //v = strtod(tmp, NULL);
  /*Serial.print(s);
  Serial.print("=");
  Serial.println(v, 6);   */
  return v;
}

void sendYesNo(int value){
  if (value == 1) Serial2.print("YES");
    else Serial2.print("NO");
}

void sendOnOff(int value){
   if (value == 1) Serial2.print("ON");
    else Serial2.print("OFF");
}

void sendTimer(ttimer_t timer){
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

void sendSlider(String cmd, String title, double value, String unit, double scale, double maxvalue, double minvalue = 0){
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

void sendPIDSlider(String cmd, String title, pid_params_t &pid, double scale, double maxvalue){
  sendSlider(cmd + "p", title + "_P", pid.Kp, "", scale, maxvalue);
  sendSlider(cmd + "i", title + "_I", pid.Ki, "", scale, maxvalue);
  sendSlider(cmd + "d", title + "_D", pid.Kd, "", scale, maxvalue);  
}

void processSlider(String result, double &value, double scale){
  int idx = result.indexOf('`');
  String s = result.substring(idx + 1);      
  double v = stringToDouble(s);
  value = v * scale;  
}

void processPIDSlider(String result, String cmd, pid_params_t &pid, double scale, double maxvalue){
  int idx = result.indexOf('`');
  String s = result.substring(idx + 1);      
  //Serial.println(tmp);
  double v = stringToDouble(s);
  if (pfodCmd.startsWith(cmd + "p")) pid.Kp = v * scale;
    else if (pfodCmd.startsWith(cmd + "i")) pid.Ki = v * scale;
    else if (pfodCmd.startsWith(cmd + "d")) pid.Kd = v * scale;      
}


void processSlider(String result, long &value, double scale){
  double v;
  processSlider(result, v, scale);
  value = v;
}

void processSlider(String result, int &value, double scale){
  double v;
  processSlider(result, v, scale);
  value = v;
}

void processSlider(String result, byte &value, double scale){
  double v;
  processSlider(result, v, scale);
  value = v;
}

void processSlider(String result, short &value, double scale){
  double v;
  processSlider(result, v, scale);
  value = v;
}
    
void sendMainMenu(boolean update){
  if (update) Serial2.print("{:"); else {
    Serial2.print(F("{.Ardumower"));  
    Serial2.print(" (");
    Serial2.print(configName);
    Serial2.print(")");
  }
  Serial2.print(F("|r~Commands|n~Manual|s~Settings|in~Info|c~Test compass|ardumag~Monitor compass|yp~Plot"));
  Serial2.println(F("|y4~Error counters}"));        
}

void sendPlotMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Plot"));           
  Serial2.print(F("|y7~Sensors|y5~Sensor counters|y3~IMU|y6~Perimeter|y8~GPS"));   
  Serial2.println(F("|y1~Battery|y2~Odometry}"));
}  


void sendSettingsMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Settings"));         
  Serial2.print(F("|s1~Motor|s2~Mow|s3~Bumper|s4~Sonar|s5~Perimeter|s6~Lawn sensor|s7~IMU|s8~R/C"));
  Serial2.println(F("|s9~Battery|s10~Station|s11~Odometry|i~Timer|s12~Date/time|sx~Factory settings|sz~Save}"));
}  

void sendErrorMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Error counters`1000"));         
  Serial2.print(F("|zz~Mow sense "));
  Serial2.print(errorCounterMax[ERR_MOW_SENSE]);
  Serial2.print(F("|zz~IMU comm "));
  Serial2.print(errorCounterMax[ERR_IMU_COMM]);
  Serial2.print(F("|zz~IMU tilt "));
  Serial2.print(errorCounterMax[ERR_IMU_TILT]);
  Serial2.print(F("|zz~Perimeter timeout "));
  Serial2.print(errorCounterMax[ERR_PERIMETER_TIMEOUT]);
  Serial2.print(F("|zz~RTC comm "));
  Serial2.print(errorCounterMax[ERR_RTC_COMM]);
  Serial2.print(F("|zz~RTC data "));
  Serial2.print(errorCounterMax[ERR_RTC_DATA]);
  Serial2.println("}");
}  

void sendMotorMenu(boolean update){  
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Motor`1000"));     
  Serial2.println(F("|a00~Overload Counter l, r "));
  Serial2.print(motorLeftSenseCounter);  
  Serial2.print(", ");
  Serial2.print(motorRightSenseCounter);  
  Serial2.println(F("|a01~Power in Watt l, r "));    
  Serial2.print(motorLeftSense);
  Serial2.print(", ");  
  Serial2.print(motorRightSense);
  Serial2.println(F("|a05~motor current in mA l, r "));    
  Serial2.print(motorLeftSenseCurrent);
  Serial2.print(", ");  
  Serial2.print(motorRightSenseCurrent);      
  sendSlider("a02", F("Power max"), motorPowerMax, "", 0.1, 40);  
  sendSlider("a03", F("calibrate left motor "), motorLeftSenseCurrent, "", 1, 1000, 0);       
  sendSlider("a04", F("calibrate right motor"), motorRightSenseCurrent, "", 1, 1000, 0);      
  Serial2.println(F("|a05~Speed l, r"));    
  Serial2.print(motorLeftPWM);
  Serial2.print(", ");  
  Serial2.print(motorRightPWM);   
  sendSlider("a06", F("Speed max"), motorSpeedMax, "", 1, 255);    
  sendSlider("a11", F("Accel"), motorAccel, "", 0.001, 0.05);    
  sendSlider("a07", F("Roll time max"), motorRollTimeMax, "", 1, 8000);     
  sendSlider("a08", F("Reverse time"), motorReverseTime, "", 1, 8000);     
  sendSlider("a09", F("Forw time max"), motorForwTimeMax, "", 10, 80000);       
  sendSlider("a12", F("Bidir speed ratio 1"), motorBiDirSpeedRatio1, "", 0.01, 1.0);       
  sendSlider("a13", F("Bidir speed ratio 2"), motorBiDirSpeedRatio2, "", 0.01, 1.0);       
  Serial2.println(F("|a10~Testing is"));    
  switch (testmode){
    case 0: Serial2.print(F("OFF")); break;
    case 1: Serial2.print(F("Left motor forw")); break;
    case 2: Serial2.print(F("Right motor forw")); break;
  }
  Serial2.println(F("|a14~for config file:"));    
  Serial2.println(F("motorSenseScale l, r"));
  Serial2.print(motorSenseLeftScale);
  Serial2.print(", ");  
  Serial2.print(motorSenseRightScale);   
  Serial2.println("}");            
}

void processMotorMenu(String pfodCmd){      
  if (pfodCmd.startsWith("a02")) processSlider(pfodCmd, motorPowerMax, 0.1);

    else if (pfodCmd.startsWith("a03")){
      processSlider(pfodCmd, motorLeftSenseCurrent, 1);
      motorSenseLeftScale = motorLeftSenseCurrent / max(0,(double)motorLeftSenseADC);                  
}
    else if (pfodCmd.startsWith("a04")){
      processSlider(pfodCmd, motorRightSenseCurrent, 1);
      motorSenseRightScale = motorRightSenseCurrent / max(0,(double)motorRightSenseADC); 
}      
    else if (pfodCmd.startsWith("a06")) processSlider(pfodCmd, motorSpeedMax, 1);
    else if (pfodCmd.startsWith("a07")) processSlider(pfodCmd, motorRollTimeMax, 1);    
    else if (pfodCmd.startsWith("a08")) processSlider(pfodCmd, motorReverseTime, 1);
    else if (pfodCmd.startsWith("a09")) processSlider(pfodCmd, motorForwTimeMax, 10);
    else if (pfodCmd.startsWith("a11")) processSlider(pfodCmd, motorAccel, 0.001);    
    else if (pfodCmd.startsWith("a12")) processSlider(pfodCmd, motorBiDirSpeedRatio1, 0.01);    
    else if (pfodCmd.startsWith("a13")) processSlider(pfodCmd, motorBiDirSpeedRatio2, 0.01);    
    else if (pfodCmd == "a10") { 
      testmode = (testmode + 1) % 3;
      switch (testmode){
        case 0: setNextState(STATE_OFF,0); break;
        case 1: setNextState(STATE_MANUAL,0); motorRightSpeed = 0; motorLeftSpeed = motorSpeedMax; break;
        case 2: setNextState(STATE_MANUAL,0); motorLeftSpeed  = 0; motorRightSpeed = motorSpeedMax; break;      
      }
    }
  sendMotorMenu(true);
}
  
void sendMowMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Mow`1000"));               
  Serial2.print(F("|o00~Overload Counter "));
  Serial2.print(motorMowSenseCounter);    
  Serial2.print(F("|o01~Power in Watt "));  
  Serial2.print(motorMowSense);  
  Serial2.print(F("|o11~current in mA "));  
  Serial2.print(motorMowSenseCurrent);  
  sendSlider("o02", F("Power max"), motorMowPowerMax, "", 0.1, 100);         
  sendSlider("o03", F("calibrate mow motor "), motorMowSenseCurrent, "", 1, 3000, 0);          
  Serial2.print(F("|o04~Speed "));
  Serial2.print(motorMowPWM);      
  sendSlider("o05", F("Speed max"), motorMowSpeedMax, "", 1, 255);       
  Serial2.print(F("|o06~Modulate "));
  sendYesNo(motorMowModulate);      
  Serial2.print(F("|o07~RPM "));
  Serial2.print(motorMowRpm);    
  sendSlider("o08", F("RPM set"), motorMowRPM, "", 1, 8000);     
  sendPIDSlider("o09", "RPM", motorMowPid, 0.0001, 0.2);      
  Serial2.println(F("|o10~Testing is"));    
  switch (testmode){
    case 0: Serial2.print(F("OFF")); break;
    case 1: Serial2.print(F("Motor ON")); break;
  }
  Serial2.println(F("|o04~for config file:"));    
  Serial2.println(F("motorMowSenseScale:"));
  Serial2.print(motorMowSenseScale);  
  Serial2.println("}");              
}

void processMowMenu(String pfodCmd){      
  if (pfodCmd.startsWith("o02")) processSlider(pfodCmd, motorMowPowerMax, 0.1);
    else if (pfodCmd.startsWith("o03")){
            processSlider(pfodCmd, motorMowSenseCurrent, 1);
            motorMowSenseScale = motorMowSenseCurrent / max(0,(double)motorMowSenseADC);
         } 
    else if (pfodCmd.startsWith("o05")) processSlider(pfodCmd, motorMowSpeedMax, 1);
    else if (pfodCmd == "o06") motorMowModulate = !motorMowModulate;    
    else if (pfodCmd.startsWith("o08")) processSlider(pfodCmd, motorMowRPM, 1);    
    else if (pfodCmd.startsWith("o09")) processPIDSlider(pfodCmd, "o09", motorMowPid, 0.0001, 0.2);
    else if (pfodCmd == "o10") { 
      testmode = (testmode + 1) % 2;
      switch (testmode){
        case 0: setNextState(STATE_OFF,0); break;
        case 1: setNextState(STATE_MANUAL,0); motorMowEnable = true; break;
      }
    }    
  sendMowMenu(true);
}

void sendBumperMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Bumper`1000"));         
  Serial2.print(F("|b00~Use "));
  sendYesNo(bumperUse);    
  Serial2.println(F("|b01~Counter l, r "));
  Serial2.print(bumperLeftCounter);  
  Serial2.print(", ");
  Serial2.print(bumperRightCounter);  
  Serial2.println(F("|b02~Value l, r "));
  Serial2.print(bumperLeft);
  Serial2.print(", ");
  Serial2.print(bumperRight);  
  Serial2.println("}");                
}

void processBumperMenu(String pfodCmd){      
  if (pfodCmd == "b00") bumperUse = !bumperUse;    
  sendBumperMenu(true);
}

void sendSonarMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Sonar`1000"));         
  Serial2.print(F("|d00~Use "));
  sendYesNo(sonarUse);
  Serial2.print(F("|d01~Counter "));
  Serial2.print(sonarDistCounter);    
  Serial2.println(F("|d02~Value l, c, r"));
  Serial2.print(sonarDistLeft);
  Serial2.print(", ");
  Serial2.print(sonarDistCenter);
  Serial2.print(", ");
  Serial2.print(sonarDistRight);  
  sendSlider("d03", F("Trigger below"), sonarTriggerBelow, "", 1, 3000);       
  Serial2.println("}");                
}

void processSonarMenu(String pfodCmd){      
  if (pfodCmd == "d00") sonarUse = !sonarUse;
    else if (pfodCmd.startsWith("d03")) processSlider(pfodCmd, sonarTriggerBelow, 1);
  sendSonarMenu(true);
}

void sendPerimeterMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Perimeter`1000"));         
  Serial2.print(F("|e00~Use "));
  sendYesNo(perimeterUse);  
  Serial2.println(F("|e02~Value l, r"));
  Serial2.print(perimeterLeft);
  Serial2.print(", ");
  Serial2.print(perimeterRight);    
  sendSlider("e05", F("Track roll time"), perimeterTrackRollTime, "", 1, 8000);       
  sendSlider("e06", F("Track rev time"), perimeterTrackRevTime, "", 1, 8000);         
  sendPIDSlider("e07", F("Track"), perimeterPid, 0.1, 100);  
  Serial2.println("}");                
}

void processPerimeterMenu(String pfodCmd){      
  if (pfodCmd == "e00") perimeterUse = !perimeterUse;
    else if (pfodCmd.startsWith("e05")) processSlider(pfodCmd, perimeterTrackRollTime, 1);
    else if (pfodCmd.startsWith("e06")) processSlider(pfodCmd, perimeterTrackRevTime, 1);
    else if (pfodCmd.startsWith("e07")) processPIDSlider(pfodCmd, "e07", perimeterPid, 0.1, 100);    
  sendPerimeterMenu(true);
}

void sendLawnSensorMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Lawn sensor`1000"));         
  Serial2.print(F("|f00~Use "));
  sendYesNo(lawnSensorUse);  
  Serial2.print(F("|f01~Counter "));
  Serial2.print(lawnSensorCounter);      
  Serial2.println(F("|f02~Value f, b"));
  Serial2.print(lawnSensorFront); 
  Serial2.print(", "); 
  Serial2.print(lawnSensorBack);   
  Serial2.println("}");                
}

void processLawnSensorMenu(String pfodCmd){      
  if (pfodCmd == "f00") lawnSensorUse = !lawnSensorUse;
  sendLawnSensorMenu(true);
}

void sendImuMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.IMU`1000"));         
  Serial2.print(F("|g00~Use "));  
  sendYesNo(imuUse);
  Serial2.print(F("|g01~Yaw "));
  Serial2.print(imuYaw/PI*180);
  Serial2.print(F(" deg"));  
  Serial2.print(F("|g02~Pitch "));
  Serial2.print(imuPitch/PI*180);
  Serial2.print(F(" deg"));  
  Serial2.print(F("|g03~Roll "));
  Serial2.print(imuRoll/PI*180);
  Serial2.print(F(" deg"));  
  Serial2.print(F("|g04~Correct dir "));
  sendYesNo(imuCorrectDir);  
  sendPIDSlider("g05", F("Dir"), imuDirPid, 0.1, 20);
  sendPIDSlider("g06", F("Roll"), imuRollPid, 0.1, 30);    
  Serial2.print(F("|g07~Start Com Cal Dev"));
  Serial2.println("}");                
}

void processImuMenu(String pfodCmd){      
  if (pfodCmd == "g00" ) imuUse = !imuUse;
    else if (pfodCmd == "g04" ) imuCorrectDir = !imuCorrectDir;
    else if (pfodCmd.startsWith("g05")) processPIDSlider(pfodCmd, "g05", imuDirPid, 0.1, 20);    
    else if (pfodCmd.startsWith("g06")) processPIDSlider(pfodCmd, "g06", imuRollPid, 0.1, 30);    
    else if (pfodCmd == "g07") imu.calibComDeviation();
  sendImuMenu(true);
}

void sendRemoteMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Remote R/C`1000"));         
  Serial2.print(F("|h00~Use "));
  sendYesNo(remoteUse);  
  Serial2.println("}");                
}

void processRemoteMenu(String pfodCmd){      
  if (pfodCmd == "h00" ) remoteUse = !remoteUse;    
  sendRemoteMenu(true);
}

void sendBatteryMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Battery`1000"));           
  Serial2.print(F("|j00~Battery "));
  Serial2.print(batVoltage);
  Serial2.print(" V");
  Serial2.print(F("|j01~Monitor "));  
  sendYesNo(batMonitor);
  sendSlider("j05", F("Calibrate battery V "), batVoltage, "", 0.01, 0, 30);   
  sendSlider("j02", F("Go home if below"), batGoHomeIfBelow, "", 0.1, (batFull*0.72), batFull);  // for Sony Konion cells 4.2V * 0,72= 3.024V which is pretty safe to use 
  sendSlider("j03", F("Switch off if below"), batSwitchOffIfBelow, "", 0.1, (batFull*0.72), batFull);  
  Serial2.print(F("|j04~Charge "));
  Serial2.print(chgVoltage);
  Serial2.print("V ");
  Serial2.print(chgCurrent);
  Serial2.print("A");
  sendSlider("j06", F("Charge sense zero"), chgSenseZero, "", 1, 600, 400);       
  sendSlider("j08", F("Charge factor"), chgFactor, "", 0.01, 10);     
  Serial2.println(F("|j09~for config file: "));
  Serial2.print("batSenseZero ");
  Serial2.println(batSenseZero);
  Serial2.print("batFactor ");  
  Serial2.print(batFactor);  
  Serial2.println("}");
}

void processBatteryMenu(String pfodCmd){      
  if (pfodCmd == "j01") batMonitor = !batMonitor;
    else if (pfodCmd.startsWith("j02")) processSlider(pfodCmd, batGoHomeIfBelow, 0.1);
    else if (pfodCmd.startsWith("j03")) processSlider(pfodCmd, batSwitchOffIfBelow, 0.1); 
    else if (pfodCmd.startsWith("j05")) {
      if (batVoltage < 8){        
     //   processSlider(pfodCmd, batVoltage, 0.1);
        batSenseZero = batADC;        
      } else {        
        processSlider(pfodCmd, batVoltage, 0.01);
        batFactor = batVoltage / max(0, (((double)batADC)-batSenseZero));        
      }      
    }
    //else if (pfodCmd.startsWith("j05")) processSlider(pfodCmd, batSenseZero, 1);
    else if (pfodCmd.startsWith("j06")) processSlider(pfodCmd, chgSenseZero, 1);
    //else if (pfodCmd.startsWith("j07")) processSlider(pfodCmd, batFactor, 0.01);    
    else if (pfodCmd.startsWith("j08")) processSlider(pfodCmd, chgFactor, 0.01);    
  sendBatteryMenu(true);
}

void sendStationMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Station`1000"));         
  sendSlider("k00", F("Reverse time"), stationRevTime, "", 1, 8000);     
  sendSlider("k01", F("Roll time"), stationRollTime, "", 1, 8000);       
  sendSlider("k02", F("Forw time"), stationForwTime, "", 1, 8000);         
  Serial2.println("}");                
}

void processStationMenu(String pfodCmd){      
  if (pfodCmd.startsWith("k00")) processSlider(pfodCmd, stationRevTime, 1);
    else if (pfodCmd.startsWith("k01")) processSlider(pfodCmd, stationRollTime, 1);
    else if (pfodCmd.startsWith("k02")) processSlider(pfodCmd, stationForwTime, 1);
  sendStationMenu(true);
}

void sendOdometryMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Odometry`1000"));         
  Serial2.print(F("|l00~Use "));
  sendYesNo(odometryUse);  
  Serial2.print(F("|l01~Value l, r "));
  Serial2.print(odometryLeft);
  Serial2.print(", "); 
  Serial2.print(odometryRight);  
  sendSlider("l01", F("Ticks per cm"), odometryTicksPerCm, "", 0.1, 30);       
  sendSlider("l02", F("Wheel base cm"), odometryWheelBaseCm, "", 0.1, 50);         
  Serial2.println("}");                
}


void processOdometryMenu(String pfodCmd){      
  if (pfodCmd == "l00") odometryUse = !odometryUse;
    else if (pfodCmd.startsWith("l01")) processSlider(pfodCmd, odometryTicksPerCm, 0.1);
    else if (pfodCmd.startsWith("l02")) processSlider(pfodCmd, odometryWheelBaseCm, 0.1);    
  sendOdometryMenu(true);
}

void sendDateTimeMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Date/time"));         
  Serial2.print("|t00~");  
  Serial2.print(date2str(datetime.date));  
  Serial2.print(", ");
  Serial2.print(time2str(datetime.time));  
  sendSlider("t01", dayOfWeek[datetime.date.dayOfWeek], datetime.date.dayOfWeek, "", 1, 6, 0);       
  sendSlider("t02", "Day ", datetime.date.day, "", 1, 31, 1);       
  sendSlider("t03", "Month ", datetime.date.month, "", 1, 12, 1);       
  sendSlider("t04", "Year ", datetime.date.year, "", 1, 2020, 2013);       
  sendSlider("t05", "Hour ", datetime.time.hour, "", 1, 23, 0);       
  sendSlider("t06", "Minute ", datetime.time.minute, "", 1, 59, 0);           
  Serial2.println("}");                
}

void processDateTimeMenu(String pfodCmd){      
  if (pfodCmd.startsWith("t01")) processSlider(pfodCmd, datetime.date.dayOfWeek, 1);    
    else if (pfodCmd.startsWith("t02")) processSlider(pfodCmd, datetime.date.day, 1);
    else if (pfodCmd.startsWith("t03")) processSlider(pfodCmd, datetime.date.month, 1);
    else if (pfodCmd.startsWith("t04")) processSlider(pfodCmd, datetime.date.year, 1);
    else if (pfodCmd.startsWith("t05")) processSlider(pfodCmd, datetime.time.hour, 1);
    else if (pfodCmd.startsWith("t06")) processSlider(pfodCmd, datetime.time.minute, 1);    
  sendDateTimeMenu(true);
  setActuator(ACT_RTC, 0);            
}

void sendTimerDetailMenu(int timerIdx, boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Details"));         
  Serial2.print("|p0");
  Serial2.print(timerIdx);
  Serial2.print("~Use ");  
  sendYesNo(timer[timerIdx].active);        
  int startm = time2minutes(timer[timerIdx].startTime);
  int stopm = time2minutes(timer[timerIdx].stopTime);
  String sidx = String(timerIdx);
  sendSlider("p1"+sidx, F("Start hour "), timer[timerIdx].startTime.hour, "", 1, 23, 0);       
  sendSlider("p2"+sidx, F("Start minute "), timer[timerIdx].startTime.minute, "", 1, 59, 0);         
  sendSlider("p3"+sidx, F("Stop hour "), timer[timerIdx].stopTime.hour, "", 1, 23, 0);       
  sendSlider("p4"+sidx, F("Stop minute "), timer[timerIdx].stopTime.minute, "", 1, 59, 0);             
  for (int i=0; i < 7; i++){
    Serial2.print("|p5");
    Serial2.print(timerIdx);    
    Serial2.print(i);    
    Serial2.print("~");
    if ((timer[timerIdx].daysOfWeek >> i) & 1) Serial2.print("(X)  ");
      else Serial2.print("(  )  ");   
    Serial2.print(dayOfWeek[i]);              
  }
  Serial2.print("|p9");
  Serial2.print(timerIdx);
  Serial2.print(F("~Set to current time"));  
  Serial2.println("}");                      
}

void processTimerDetailMenu(String pfodCmd){      
  timehm_t time;
  boolean checkStop = false;
  boolean checkStart = false;
  int startmin, stopmin;
  int timerIdx = pfodCmd[2]-'0';
  if (pfodCmd.startsWith("p0")) timer[timerIdx].active = !timer[timerIdx].active;
    else if (pfodCmd.startsWith("p1")) { processSlider(pfodCmd, timer[timerIdx].startTime.hour, 1); checkStop = true; }
    else if (pfodCmd.startsWith("p2")) { processSlider(pfodCmd, timer[timerIdx].startTime.minute, 1); checkStop = true; }
    else if (pfodCmd.startsWith("p3")) { processSlider(pfodCmd, timer[timerIdx].stopTime.hour, 1); checkStart = true; }      
    else if (pfodCmd.startsWith("p4")) { processSlider(pfodCmd, timer[timerIdx].stopTime.minute, 1); checkStart = true; }        
    else if (pfodCmd.startsWith("p9")) {       
      timer[timerIdx].startTime = datetime.time; checkStop = true;      
      timer[timerIdx].daysOfWeek = (1 << datetime.date.dayOfWeek);      
    }
    else if (pfodCmd.startsWith("p5")) {
      int day = pfodCmd[3]-'0';
      timer[timerIdx].daysOfWeek = timer[timerIdx].daysOfWeek ^ (1 << day);
    }
    if (checkStop){
      // adjust start time
      startmin = min(1434, time2minutes(timer[timerIdx].startTime));
      minutes2time(startmin, time);
      timer[timerIdx].startTime = time;
      // check stop time
      stopmin  = time2minutes(timer[timerIdx].stopTime);
      stopmin = max(stopmin, startmin + 5);       
      minutes2time(stopmin, time);
      timer[timerIdx].stopTime = time;
    } else if (checkStart){
      // adjust stop time
      stopmin = max(5, time2minutes(timer[timerIdx].stopTime));
      minutes2time(stopmin, time);
      timer[timerIdx].stopTime = time;      
      // check start time
      startmin = time2minutes(timer[timerIdx].startTime);      
      startmin = min(startmin, stopmin - 5);       
      minutes2time(startmin, time);
      timer[timerIdx].startTime = time;
    }
  sendTimerDetailMenu(timerIdx, true);  
}

void sendTimerMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Timer"));         
  Serial2.print(F("|i99~Use "));
  sendYesNo(timerUse);      
  for (int i=0; i < MAX_TIMERS; i++){
    Serial2.print("|i0");
    Serial2.print(i);
    Serial2.print("~");
    sendTimer(timer[i]);    
  }
  Serial2.println("}");                
}

void processTimerMenu(String pfodCmd){      
  if (pfodCmd.startsWith("i0")) {
    int timerIdx = pfodCmd[2]-'0';
    sendTimerDetailMenu(timerIdx, false);  
  } else {
    if (pfodCmd.startsWith("i99")) timerUse = !timerUse;
    sendTimerMenu(true);
  }  
}

void sendFactorySettingsMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.println(F("{.Factory settings"));
  Serial2.print(F("|x0~Set factory settings (requires reboot)"));
  Serial2.println("}");
}

void processFactorySettingsMenu(String pfodCmd){      
  if (pfodCmd == "x0") deleteUserSettings();
  sendFactorySettingsMenu(true);
}

void sendInfoMenu(boolean update){
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

void sendCommandMenu(boolean update){  
  if (update) Serial2.print("{:"); else Serial2.print(F("{.Commands`5000"));  
  Serial2.print(F("|ro~OFF|ra~Auto mode|rc~RC mode|"));
  Serial2.print(F("rm~Mowing is "));  
  sendOnOff(motorMowEnable);  
  Serial2.print(F("|rp~Pattern is "));
  Serial2.print(mowPatternName[mowPatternCurr]);
  Serial2.print(F("|rh~Home|rk~Track|rs~State is "));         
  Serial2.print(stateName[stateCurr]);
  Serial2.print(F("|rr~Auto rotate is "));
  Serial2.print(motorLeftPWM);      
  Serial2.print(F("|r1~User switch 1 is "));         
  sendOnOff(userSwitch1);  
  Serial2.print(F("|r2~User switch 2 is "));         
  sendOnOff(userSwitch2);  
  Serial2.print(F("|r3~User switch 3 is "));         
  sendOnOff(userSwitch3);  
  Serial2.print("}");
  Serial2.println();
}

void processCommandMenu(String pfodCmd){
  if (pfodCmd == "ro"){
    // cmd: off      
    setNextState(STATE_OFF, 0);          
    sendCommandMenu(true);
  } else if (pfodCmd == "rh"){
    // cmd: home      
    setNextState(STATE_PERI_FIND, 0);                      
    sendCommandMenu(true);
  } else if (pfodCmd == "rr"){
    setNextState(STATE_MANUAL, 0);
    motorLeftSpeed += 10; motorRightSpeed = -motorLeftSpeed;      
    sendCommandMenu(true);  
} else if (pfodCmd == "rk"){
    // cmd: track perimeter      
    setNextState(STATE_PERI_TRACK, 0);                      
    sendCommandMenu(true);
  } else if (pfodCmd == "ra"){
    // cmd: start auto mowing      
    motorMowEnable = true;      
    setNextState(STATE_FORWARD, 0);                
    sendCommandMenu(true);
  } else if (pfodCmd == "rc"){      
    // cmd: start remote control (RC)      
    motorMowEnable = true;
    motorMowModulate = false;                
    setNextState(STATE_REMOTE, 0);    
    sendCommandMenu(true);
  } else if (pfodCmd == "rm"){
    // cmd: mower motor on/off      
    motorMowEnable = !motorMowEnable;      
    sendCommandMenu(true);
  } else if (pfodCmd == "rs"){
    // cmd: state
    sendCommandMenu(true);
  } else if (pfodCmd == "rp"){
    // cmd: pattern
    mowPatternCurr = (mowPatternCurr + 1 ) % 3;      
    setNextState(STATE_OFF, 0);            
    sendCommandMenu(true);
  } else if (pfodCmd == "r1"){
    userSwitch1 = !userSwitch1;
    setUserSwitches();
    sendCommandMenu(true);
  } else if (pfodCmd == "r2"){
    userSwitch2 = !userSwitch2;
    setUserSwitches();
    sendCommandMenu(true);
  } else if (pfodCmd == "r3"){
    userSwitch3 = !userSwitch3;
    setUserSwitches();
    sendCommandMenu(true);
  } 
}


void sendManualMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.println(F("{^Manual navigation`1000"));
  Serial2.print(F("|nl~Left|nr~Right|nf~Forward"));
  if (   ((motorLeftSpeed  < 5)  && (motorLeftSpeed  > -5))
     &&  ((motorRightSpeed < 5)  && (motorRightSpeed > -5))  ){
    Serial2.print(F("|nb~Reverse"));
  } else Serial2.print(F("|ns~Stop"));  
  Serial2.print(F("|nm~Mow is "));
  sendOnOff(motorMowEnable);  
  Serial2.println("}");
}

void sendCompassMenu(boolean update){
  if (update) Serial2.print("{:"); else Serial2.println(F("{^Compass`1000"));
  Serial2.print(F("|cw~West|ce~East|cn~North "));
  Serial2.print(imuYaw/PI*180);
  Serial2.println(F("|cs~South|cm~Mow}"));  
}

void processCompassMenu(String pfodCmd){
 if (pfodCmd == "cm"){
    motorMowEnable = !motorMowEnable;            
    sendCompassMenu(true);
  } else if (pfodCmd == "cn"){      
    imuRollHeading = 0;
    setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  } else if (pfodCmd == "cs"){
    imuRollHeading = PI;
    setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  } else if (pfodCmd == "cw"){
    imuRollHeading = -PI/2;
    setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  } else if (pfodCmd == "ce"){
    imuRollHeading = PI/2;
    setNextState(STATE_ROLL_WAIT, 0);            
    sendCompassMenu(true);
  }
}

void processManualMenu(String pfodCmd){
  if (pfodCmd == "nl"){
    // manual: left
    setNextState(STATE_MANUAL, 0);          
    double sign = 1.0;
    if (motorLeftSpeed < 0) sign = -1.0;      
    if (sign*motorLeftSpeed >= sign*motorRightSpeed) motorLeftSpeed  = sign * motorSpeedMax/2;      
        else motorLeftSpeed /= 2; 
    motorRightSpeed = sign * motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nr"){      
    // manual: right
    setNextState(STATE_MANUAL, 0);          
    double sign = 1.0;
    if (motorRightSpeed < 0) sign = -1.0;
    if (sign*motorRightSpeed >= sign*motorLeftSpeed) motorRightSpeed  = sign* motorSpeedMax/2;
        else motorRightSpeed /= 2;            
    motorLeftSpeed  = sign * motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nf"){
    // manual: forward
    setNextState(STATE_MANUAL, 0);          
    motorLeftSpeed  = motorSpeedMax;
    motorRightSpeed = motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nb"){
    // manual: reverse
    setNextState(STATE_MANUAL, 0);          
    motorLeftSpeed  = -motorSpeedMax;
    motorRightSpeed = -motorSpeedMax;
    sendManualMenu(true);
  } else if (pfodCmd == "nm"){
    // manual: mower ON/OFF
    motorMowEnable = !motorMowEnable;            
    sendManualMenu(true);
  } else if (pfodCmd == "ns"){
    // manual: stop
    //setNextState(STATE_OFF, 0);          
    motorLeftSpeed  =  motorRightSpeed = 0;      
    sendManualMenu(true);
  }  
}

void processSettingsMenu(String pfodCmd){   
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
      else if (pfodCmd == "sz") { saveUserSettings(); sendSettingsMenu(true); }
      else sendSettingsMenu(true);  
}      

void processArduMagResult(String pfodCmd){  
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
    double value = stringToDouble(s);    
    /*Serial.print("type=");
    Serial.print(type);
    Serial.print(", i=");
    Serial.print(i);
    Serial.print(", j=");
    Serial.print(j);
    Serial.print(", value=");
    Serial.println(value);*/
    imu.setComCalParam(type, i, j, value);
    if ((type == 1) && (i==2) && (j==2)) beep(2, false);
  }    
}

// process pfodState
void pfodLoop(){  
  if (pfodState == PFOD_ARDU_MAG){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;      
      // output raw compass values (ArduMag state)
      Serial2.print(imuComX);
      Serial2.print("\t");
      Serial2.print(imuComY);
      Serial2.print("\t");
      Serial2.println(imuComZ);    
    }
  } else if (pfodState == PFOD_MONITOR){
    printInfo(Serial2);
    //Serial2.println("test");
  } else if (pfodState == PFOD_PLOT_BAT){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 60000;
      Serial2.print(((unsigned long)millis()/60000));
      Serial2.print(",");
      Serial2.print(batVoltage);
      Serial2.print(",");
      Serial2.print(chgVoltage);
      Serial2.print(",");
      Serial2.print(chgCurrent);         
      Serial2.print(",");
      Serial2.println(batCapacity);         
    }
  } else if (pfodState == PFOD_PLOT_ODO){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 500;
      Serial2.print(odometryX);
      Serial2.print(",");
      Serial2.println(odometryY);
    }
  } else if (pfodState == PFOD_PLOT_IMU){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Serial2.print((double(millis())/1000.0f));
      Serial2.print(",");
      Serial2.print(imuYaw/PI*180);
      Serial2.print(",");
      Serial2.print(imuPitch/PI*180);
      Serial2.print(",");
      Serial2.print(imuRoll/PI*180);
      Serial2.print(",");
      Serial2.print(accMin.x);
      Serial2.print(",");
      Serial2.print(accMax.x);
      Serial2.print(",");
      Serial2.print(accMin.y);
      Serial2.print(",");
      Serial2.print(accMax.y);
      Serial2.print(",");
      Serial2.print(accMin.z);
      Serial2.print(",");
      Serial2.println(accMax.z);
    }
  } else if (pfodState == PFOD_PLOT_SENSOR_COUNTERS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Serial2.print((double(millis())/1000.0f));
      Serial2.print(",");
      Serial2.print(stateCurr);
      Serial2.print(",");
      Serial2.print(motorLeftSenseCounter);
      Serial2.print(",");
      Serial2.print(motorRightSenseCounter);
      Serial2.print(",");
      Serial2.print(motorMowSenseCounter);
      Serial2.print(",");
      Serial2.print(bumperLeftCounter);
      Serial2.print(",");
      Serial2.print(bumperRightCounter);
      Serial2.print(",");
      Serial2.print(sonarDistCounter);
      Serial2.print(",");
      Serial2.print(perimeterLeftCounter);
      Serial2.print(",");
      Serial2.println(lawnSensorCounter);
    }
  } else if (pfodState == PFOD_PLOT_SENSORS){
    if (millis() >= nextPlotTime){
      nextPlotTime = millis() + 200;
      Serial2.print((double(millis())/1000.0f));
      Serial2.print(",");
      Serial2.print(stateCurr);
      Serial2.print(",");
      Serial2.print(motorLeftSense);
      Serial2.print(",");
      Serial2.print(motorRightSense);
      Serial2.print(",");
      Serial2.print(motorMowSense);
      Serial2.print(",");
      Serial2.print(sonarDistLeft);
      Serial2.print(",");
      Serial2.print(sonarDistCenter);
      Serial2.print(",");
      Serial2.print(sonarDistRight);
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
        Serial2.print(perimeterLeft);
        Serial2.print(",");
        Serial2.print(Perimeter.getSmoothMagnitude());
        Serial2.print(",");
        Serial2.print(Perimeter.isInside());
        Serial2.print(",");
        Serial2.print(perimeterLeftCounter);
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
      gps.f_get_position(&lat, &lon, &age);
      Serial2.print((double(millis())/1000.0f));
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
      Serial2.println(lon);
    }
  }
}

// process serial input from pfod App
void readSerialPfod(){
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
          beep(1, false);
          Serial2.println(F("{=monitor compass}")); 
          pfodState = PFOD_ARDU_MAG;
        }      
        else if (pfodCmd == "m1") {
          // set monitor counter state
          Serial2.println(F("{=monitor counters}")); 
          consoleMode = CONSOLE_SENSOR_COUNTERS;
          pfodState = PFOD_MONITOR;
        }  
        else if (pfodCmd == "m2"){
          // set monitor values state
          Serial2.println(F("{=monitor values}")); 
          consoleMode = CONSOLE_SENSOR_VALUES;
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
          Serial2.println(F("{=IMU`300|time s`0|yaw`1|pitch`2|roll`3|accX-`4|accX+`5|accY-`6|accY+`7|accZ-`8|accZ+`9}"));         
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



