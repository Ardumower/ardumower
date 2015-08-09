/*
  Ardumower (www.ardumower.de)
  Copyright (c) 2013-2014 by Alexander Grau
  Copyright (c) 2013-2014 by Sven Gennat
  
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

// example usage:
//   RemoteControl remote;
//   remote.initSerial(19200);
//   while (true){
//     remote.readSerial();
//     remote.run();
//  }


#ifndef PFOD_H
#define PFOD_H

#include <Arduino.h>
#include "drivers.h"
#include "pid.h"
#include "perimeter.h"

// pfodApp state
enum { PFOD_OFF, PFOD_MENU, PFOD_LOG_SENSORS, 
       PFOD_PLOT_BAT, PFOD_PLOT_ODO2D, PFOD_PLOT_IMU, PFOD_PLOT_SENSOR_COUNTERS, 
       PFOD_PLOT_SENSORS, PFOD_PLOT_PERIMETER, PFOD_PLOT_GPS, PFOD_PLOT_GPS2D,
       PFOD_PLOT_MOTOR };

class Robot;

class RemoteControl
{
  public:
    RemoteControl();
    void setRobot(Robot *aRobot);
    void initSerial(HardwareSerial* serialPort, uint32_t baudrate);
    bool readSerial();
    void run();    
  private:
    HardwareSerial* serialPort;
    Robot *robot;    
    boolean pfodCmdComplete;
    String pfodCmd;
    byte pfodState;
    int testmode;
    unsigned long nextPlotTime;
    int8_t perimeterCapture[RAW_SIGNAL_SAMPLE_SIZE];
    int perimeterCaptureIdx;        
    float stringToFloat(String &s);   

    // generic
    void sendYesNo(int value);
    void sendOnOff(int value);

    // PID slider
    void sendPIDSlider(String cmd, String title, PID &pid, double scale, float maxvalue);
    void processPIDSlider(String result, String cmd, PID &pid, double scale, float maxvalue);
    
    // generic slider
    void sendSlider(String cmd, String title, float value, String unit, double scale, float maxvalue, float minvalue = 0);    
    void processSlider(String result, float &value, double scale);
    void processSlider(String result, long &value, double scale);
    void processSlider(String result, int &value, double scale);
    void processSlider(String result, byte &value, double scale);
    void processSlider(String result, short &value, double scale);


    // send timer menu details
    void sendTimer(ttimer_t timer);

    // main menu
    void sendMainMenu(boolean update);
    void sendErrorMenu(boolean update);
    void sendInfoMenu(boolean update);
    void sendCommandMenu(boolean update);
    void processCommandMenu(String pfodCmd);
    void sendManualMenu(boolean update);
    void sendCompassMenu(boolean update);
    void processCompassMenu(String pfodCmd);
    void processManualMenu(String pfodCmd);
    void processSettingsMenu(String pfodCmd);      
    
    // plotting
    void sendPlotMenu(boolean update);
    
    // settings
    void sendSettingsMenu(boolean update);
    void sendMotorMenu(boolean update);    
    void sendMowMenu(boolean update);
    void sendBumperMenu(boolean update);
    void sendDropMenu(boolean update);
    void sendSonarMenu(boolean update);    
    void sendPerimeterMenu(boolean update);
    void sendLawnSensorMenu(boolean update);    
    void sendImuMenu(boolean update);
    void sendRemoteMenu(boolean update);
    void sendBatteryMenu(boolean update);    
    void sendStationMenu(boolean update);
    void sendOdometryMenu(boolean update);
    void sendRainMenu(boolean update);    
    void sendGPSMenu(boolean update);        
    void sendDateTimeMenu(boolean update);
    void sendFactorySettingsMenu(boolean update);    
    void sendADCMenu(boolean update);
    
    void processMotorMenu(String pfodCmd);    
    void processErrorMenu(String pfodCmd);        
    void processMowMenu(String pfodCmd);
    void processBumperMenu(String pfodCmd);
    void processSonarMenu(String pfodCmd);    
    void processPerimeterMenu(String pfodCmd); 
    void processLawnSensorMenu(String pfodCmd);   
    void processRainMenu(String pfodCmd);       
    void processDropMenu(String pfodCmd);    
    void processGPSMenu(String pfodCmd);           
    void processImuMenu(String pfodCmd);         
    void processRemoteMenu(String pfodCmd);      
    void processBatteryMenu(String pfodCmd);
    void processStationMenu(String pfodCmd);
    void processOdometryMenu(String pfodCmd);      
    void processDateTimeMenu(String pfodCmd);
    void processFactorySettingsMenu(String pfodCmd); 
    void processInfoMenu(String pfodCmd);

    // timer
    void sendTimerDetailMenu(int timerIdx, boolean update);
    void processTimerDetailMenu(String pfodCmd);    
    void sendTimerMenu(boolean update);
    void processTimerMenu(String pfodCmd);
              
};



#endif


