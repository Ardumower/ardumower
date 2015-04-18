#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;

void stopIfFault()
{
  if (md.getFault())
  {
    Serial.println("fault");
    while(1);
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Dual MC33926 Motor Shield");
  md.init();
}

void loop()
{
  for (int i = 0; i <= 400; i++)
  {
    md.setM1Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(2);
  }
  
  for (int i = 400; i >= -400; i--)
  {
    md.setM1Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(2);
  }
  
  for (int i = -400; i <= 0; i++)
  {
    md.setM1Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("M1 current: ");
      Serial.println(md.getM1CurrentMilliamps());
    }
    delay(2);
  }

  for (int i = 0; i <= 400; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
    delay(2);
  }
  
  for (int i = 400; i >= -400; i--)
  {
    md.setM2Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
    delay(2);
  }
  
  for (int i = -400; i <= 0; i++)
  {
    md.setM2Speed(i);
    stopIfFault();
    if (abs(i)%200 == 100)
    {
      Serial.print("M2 current: ");
      Serial.println(md.getM2CurrentMilliamps());
    }
    delay(2);
  }
}
