#ifndef LED_H
#define LED_H

// Ardumower LEDs  (play LED 'sequences')

#include <Arduino.h>


// playable LED sequences
enum {
  LED_OFF,
  LED_GREEN_ON,
  LED_ORANGE_ON,
  LED_ORANGE_BLINK,
  LED_RED_BLINK,
  LED_RED_ON,
};

/*
LED Anzeigen - Hardware:
Led 3V grün - Betriebsanzeige Versorgungsspannung
LED 24V grün - Betriebsanzeige Versorgungsspannung R2 für 12 V anpassen
LED 5V grün - Betriebsanzeige Versorgungsspannung
LED Station - gelb - Statusanzeige ob Mover in Ladestation

LED Anzeigen - Software:
Dual LED z.B:
Dual LED grün. Dauerlicht - Mover innerhalb Perimeter
Dual LED grün+rot = Orange - Dauerlicht Mover außerhalb Perimeter
Dual LED grün+rot = Orange - Blinkt Mover findet Perimeter nicht oder sucht danach
Dual LED rot = Blinkt Fehler kurzseitig Überlast Antriebmotor Treibe oder Mähmotor.
Dual LED rot - Dauerlicht - Fehler muß für weiterfahren durch drücken 
*/



class LEDControl
{
  public:
    LEDControl();
    void playSequence(int sequenceIdx);
    void run();
    void setup();
  private:
    unsigned long nextLEDTime;
    int ledSequenceIdx;
    bool onState;
};

extern LEDControl LED;

#endif


