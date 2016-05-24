#ifndef SIMMOWER_H
#define SIMMOWER_H

#include "../config.h"

// Ardumower simulator classes

class SimLED : public LEDControl
{
  private:
    virtual void setDriverLED(int LEDidx, bool state){};
};

class SimMotor : public MotorControl
{
  private:
    virtual void setDriverPWM(int leftMotorPWM, int rightMotorPWM){};
};

extern SimLED LED;
extern SimMotor MotorCtrl;

#endif


