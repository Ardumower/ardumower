#ifndef SONAR_H
#define SONAR_H

// Ardumower ultrasonic sensor 

#include <Arduino.h>


class SonarControl
{
  public:
    char sonarLeftUse;
    char sonarRightUse;
    char sonarCenterUse;
    int sonarTriggerBelow ;    // ultrasonic sensor trigger distance
    unsigned int sonarDistCenter ;
    unsigned int sonarDistRight ;
    unsigned int sonarDistLeft ; 
    unsigned int sonarDistCounter ;
    unsigned long sonarObstacleTimeout ;      
    SonarControl();
    void setup();
    void run();
    void print();
  private:
    unsigned long nextSonarTime;
    unsigned int readHCSR04(int triggerPin, int echoPin);
};


extern SonarControl Sonar;  

  
#endif

