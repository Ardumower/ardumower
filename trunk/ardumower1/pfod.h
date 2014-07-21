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

#ifndef PFOD_H
#define PFOD_H

#include <Arduino.h>
#include "drivers.h"
#include "pid.h"

// pfodApp state
enum { PFOD_OFF, PFOD_MENU, PFOD_MONITOR, PFOD_ARDU_MAG,
       PFOD_PLOT_BAT, PFOD_PLOT_ODO, PFOD_PLOT_IMU, PFOD_PLOT_SENSOR_COUNTERS, PFOD_PLOT_SENSORS, PFOD_PLOT_PERIMETER, PFOD_PLOT_GPS };

class Robot;

class RemoteControl
{
  public:
    RemoteControl(Robot *aRobot);
    void initSerial(int baudrate);
    void readSerial();
    void run();    
  private:
    Robot *robot;    
    boolean pfodCmdComplete;
    String pfodCmd;
    byte pfodState;
    int testmode;
    unsigned long nextPlotTime;
    int8_t perimeterCapture[32]; 
    int perimeterCaptureIdx;        
    float stringToFloat(String &s);
    void sendYesNo(int value);
    void sendOnOff(int value);
    void sendTimer(ttimer_t timer);
    void sendSlider(String cmd, String title, float value, String unit, float scale, float maxvalue, float minvalue = 0);
    void sendPIDSlider(String cmd, String title, PID &pid, float scale, float maxvalue);
    void processSlider(String result, float &value, float scale);
    void processPIDSlider(String result, String cmd, PID &pid, float scale, float maxvalue);
    void processSlider(String result, long &value, float scale);
    void processSlider(String result, int &value, float scale);
    void processSlider(String result, byte &value, float scale);
    void processSlider(String result, short &value, float scale);
    void sendMainMenu(boolean update);
    void sendPlotMenu(boolean update);
    void sendSettingsMenu(boolean update);
    void sendErrorMenu(boolean update);
    void sendMotorMenu(boolean update);
    void processMotorMenu(String pfodCmd);
    void sendMowMenu(boolean update);
    void processMowMenu(String pfodCmd);
    void sendBumperMenu(boolean update);
    void processBumperMenu(String pfodCmd);
    void sendSonarMenu(boolean update);
    void processSonarMenu(String pfodCmd);
    void sendPerimeterMenu(boolean update);
    void processPerimeterMenu(String pfodCmd);
    void sendLawnSensorMenu(boolean update);
    void processLawnSensorMenu(String pfodCmd);
    void sendImuMenu(boolean update);
    void processImuMenu(String pfodCmd);      
    void sendRemoteMenu(boolean update);
    void processRemoteMenu(String pfodCmd);      
    void sendBatteryMenu(boolean update);
    void processBatteryMenu(String pfodCmd);
    void sendStationMenu(boolean update);
    void processStationMenu(String pfodCmd);
    void sendOdometryMenu(boolean update);
    void processOdometryMenu(String pfodCmd);      
    void sendDateTimeMenu(boolean update);
    void processDateTimeMenu(String pfodCmd);
    void sendTimerDetailMenu(int timerIdx, boolean update);
    void processTimerDetailMenu(String pfodCmd);
    void sendTimerMenu(boolean update);
    void processTimerMenu(String pfodCmd);
    void sendFactorySettingsMenu(boolean update);
    void processFactorySettingsMenu(String pfodCmd);
    void sendInfoMenu(boolean update);
    void sendCommandMenu(boolean update);
    void processCommandMenu(String pfodCmd);
    void sendManualMenu(boolean update);
    void sendCompassMenu(boolean update);
    void processCompassMenu(String pfodCmd);
    void processManualMenu(String pfodCmd);
    void processSettingsMenu(String pfodCmd);  
    void processArduMagResult(String pfodCmd);
};



#endif


