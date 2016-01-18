#include <DistanceGP2Y0A21YK.h>

DistanceGP2Y0A21YK Dist;
int distance;

void setup()
{
  Serial.begin(9600);
  Dist.begin(A0);
}

void loop()
{
  distance = Dist.getDistanceVolt();
  Serial.print("\nADC input mV: ");
  Serial.print(distance);  
  delay(500); //make it readable
}