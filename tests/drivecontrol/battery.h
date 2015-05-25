#ifndef BATTERY_H
#define BATTERY_H

// Ardumower battery/charger management

#include <Arduino.h>


class BatteryControl
{
  public:
    float batFactor       ;     // battery conversion factor
    float batChgFactor       ;     // battery conversion factor    
    float batFull         ;      // battery reference Voltage (fully charged)
    float batChargingCurrentMax ; // maximum current your charger can devliver
    float batFullCurrent   ; // current flowing when battery is fully charged
    float startChargingIfBelow; // start charging if battery Voltage is below
    unsigned long chargingTimeout; // safety timer for charging
    int batADC;
    float chgSenseZero    ;       // charge current sense zero point
    float chgFactor       ;     // charge current conversion factor
    float chgSense        ;       // mV/A empfindlichkeit des Ladestromsensors in mV/A (Für ACS712 5A = 185)
    char chgChange        ;       // messwertumkehr von - nach +         1oder 0
    float batVoltage ;  // battery voltage (Volt)
    byte chgSelection     ;       // Senor Auswahl
    float batRefFactor ;
    float batCapacity ; // battery capacity (mAh)
    float chgVoltage ;  // charge voltage (Volt)
    float chgCurrent ;  // charge current  (Ampere)
    int chgNull;        // Nulldurchgang Ladestromsensor         
    int batteryReadCounter;
    bool chargeRelayEnabled;
    BatteryControl();            
    void setup();    
    void run();        
    void read();       
    void print();    
    void setBatterySwitch(bool state);
    bool chargerConnected();
    void enableChargingRelay(bool state);
  private:
    unsigned long nextBatteryTime;
};


extern BatteryControl Battery;  

  
#endif

