#ifndef SONAR_H
#define SONAR_H

// Ardumower ultrasonic sensor
// requires: HCSR04  

#include <Arduino.h>


class SonarControl
{
  public:
    bool enableLeft;
    bool enableRight;
    bool enableCenter;
    int sonarTriggerBelow ;    // ultrasonic sensor trigger distance
    unsigned int sonarDistCenter ;
    unsigned int sonarDistRight ;
    unsigned int sonarDistLeft ; 
    unsigned int sonarDistCounter ;
    unsigned long sonarObstacleTimeout ;      
    bool triggeredCenter();
    bool triggeredLeft();    
    bool triggeredRight();        
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

