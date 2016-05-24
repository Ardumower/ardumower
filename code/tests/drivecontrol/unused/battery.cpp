#include "battery.h"
#include "config.h"
#include "ADCMan.h"
#include "timer.h"
#include "drivers.h"

BatteryControl Battery;



BatteryControl::BatteryControl(){  
  nextBatteryTime = batteryReadCounter = 0;
  chargingStartTimeMinutes = 0;
  batVoltage = 24;
  chgVoltage = 0;
  idleTimeSec = 0;
  enableMonitor = false;
  chargeRelayEnabled = false;  
  batFactor       = 0.495;      // battery conversion factor  / 10 due to arduremote bug, can be removed after fixing (look in robot.cpp)
  batChgFactor    = 0.495;      // battery conversion factor  / 10 due to arduremote bug, can be removed after fixing (look in robot.cpp)
  batFull          =29.4;      // battery reference Voltage (fully charged) PLEASE ADJUST IF USING A DIFFERENT BATTERY VOLTAGE! FOR a 12V SYSTEM TO 14.4V
  batChargingCurrentMax =1.6;  // maximum current your charger can devliver
  batFullCurrent  = 0.3;      // current flowing when battery is fully charged
  batGoHomeIfBelow = 23.7;     // drive home voltage (Volt)
  startChargingIfBelow = 27.0; // start charging if battery Voltage is below
  chargingTimeoutMinutes = 210; // safety timer for charging (minutes)    
  // Sensorausgabe Konsole      (chgSelection =0)
  // Einstellungen ACS712 5A    (chgSelection =1   /   chgSenseZero ~ 511    /    chgFactor = 39    /    chgSense =185.0    /    chgChange = 0 oder 1    (je nach  Stromrichtung)   /   chgNull  = 2)
  // Einstellungen INA169 board (chgSelection =2)
  chgSelection    = 2;
  chgSenseZero    = 511;        // charge current sense zero point
  chgFactor       = 39;         // charge current conversion factor   - Empfindlichkeit nimmt mit ca. 39/V Vcc ab
  chgSense        = 185.0;      // mV/A empfindlichkeit des Ladestromsensors in mV/A (Für ACS712 5A = 185)
  chgChange       = 0;          // Messwertumkehr von - nach +         1 oder 0
  chgNull         = 2;          // Nullduchgang abziehen (1 oder 2)    
}

void BatteryControl::setup(){
  Console.println(F("BatteryControl::setup"));
  pinMode(pinBatterySwitch, OUTPUT);
  pinMode(pinBatteryVoltage, INPUT);        
  pinMode(pinChargeCurrent, INPUT);          
  pinMode(pinChargeVoltage, INPUT); 
  pinMode(pinVoltageMeasurement, INPUT);    
  pinMode(pinChargeRelay, OUTPUT);  
  
  ADCMan.setCapture(pinChargeCurrent, 1, true);//Aktivierung des LaddeStrom Pins beim ADC-Managers  
  ADCMan.setCapture(pinBatteryVoltage, 1, false);
  ADCMan.setCapture(pinChargeVoltage, 1, false);  
  ADCMan.setCapture(pinVoltageMeasurement, 1, false);      
  setBatterySwitch(HIGH);
}

void BatteryControl::setBatterySwitch(bool state){
  Console.print(F("BatteryControl::setBatterySwitch "));
  Console.println(state);
  digitalWrite(pinBatterySwitch, state);
}

// call this in main loop
void BatteryControl::run(){
  if (millis() < nextBatteryTime) return;
  nextBatteryTime = millis() + 1000;  
  read();  
  if (batteryReadCounter == 10) {    
    batteryReadCounter = 0;
    print();
  }      
  if ( (chargerConnected()) && (robotShouldCharge()) ) {
    Battery.enableChargingRelay(true);
  } else {
    Battery.enableChargingRelay(false);    
  }
  idleTimeSec++;
}

bool BatteryControl::isCharging(){
  return chargeRelayEnabled;
}

bool BatteryControl::robotShouldGoHome(){
  return ((enableMonitor) &&  (batVoltage < batGoHomeIfBelow));
}

bool BatteryControl::robotShouldSwitchOff(){
  return (     (enableMonitor) 
           &&  (  (idleTimeSec > batSwitchOffIfIdle * 60) || (batVoltage < batSwitchOffIfBelow) )
         );
}

bool BatteryControl::robotShouldCharge(){
  return (     (enableMonitor) &&  (batVoltage < startChargingIfBelow)
               && (getChargingTimeMinutes() < chargingTimeoutMinutes) 
         );
}

// read battery
void BatteryControl::read(){
  batteryReadCounter++;
  
  #ifndef SIMULATE
    if ((abs(chgCurrent) > 0.04) && (chgVoltage > 5)){
      // charging
      batCapacity += (chgCurrent / 36.0);
    }
    // convert to double  
    batADC = ADCMan.read(pinBatteryVoltage);
    double batvolt = (double)batADC * batFactor / 10;  // / 10 due to arduremote bug, can be removed after fixing
    //double chgvolt = ((double)((int)(readSensor(SEN_CHG_VOLTAGE) / 10))) / 10.0;  
    int chgADC = ADCMan.read(pinChargeVoltage);
    //Console.println(chgADC);
    double chgvolt = (double)chgADC * batChgFactor / 10;  // / 10 due to arduremote bug, can be removed after fixing
    double current = ((double)((int)(ADCMan.read(pinChargeCurrent))));  
    // low-pass filter
    double accel = 0.01;
    if (abs(batVoltage-batvolt)>5)   batVoltage = batvolt; else batVoltage = (1.0-accel) * batVoltage + accel * batvolt;
    if (abs(chgVoltage-chgvolt)>5)   chgVoltage = chgvolt; else chgVoltage = (1.0-accel) * chgVoltage + accel * chgvolt;
    // if (abs(chgCurrent-current)>0.4) chgCurrent = current; else chgCurrent = (1.0-accel) * chgCurrent + accel * current;  //Deaktiviert fÃ¼r Ladestromsensor berechnung 

    // Anfang Ladestromsensor zur GlÃ¤ttung und Mittelwertbildung
    // ********************************************************************
    //  Variabeln
    double currentmitte = current;    
    // ********************************************************************
    // Ende Ladestromsensor zur GlÃ¤ttung und Mittelwertbildung


   //  Anfang Ladestromsensor berechnen
   // ********************************************************************
   //  Variabeln 
    float vcc, asensor, amp;     
    float chgAMP;                                               //Sensorwert des Ladestrompin

    //Sensor Wert Ausgabe auf Seriellen Monitor oder HandyApp   wenn chgSelection =0
    if (chgSelection==0) chgCurrent = current;

    // Berechnung fÃ¼r Ladestromsensor ACS712 5A                 wenn chgSelection =1
    if (chgSelection==1) {  
      chgAMP = currentmitte;                                     //Sensorwert Ã¼bergabe vom Ladestrompin
      vcc = (float) 3.30 / chgSenseZero * 1023.0;                // Versorgungsspannung ermitteln!  chgSenseZero=511  ->Die Genauigkeit kann erhÃ¶t werden wenn der 3.3V Pin an ein Analogen Pin eingelesen wird. Dann ist vcc = (float) 3.30 / analogRead(X) * 1023.0;
      asensor = (float) chgAMP * vcc / 1023.0;                   // Messwert auslesen
      asensor = (float) asensor - (vcc/chgNull);                 // Nulldurchgang (vcc/2) abziehen
      chgSense = (float) chgSense - ((5.00-vcc)*chgFactor);      // Korrekturfactor fÃ¼r Vcc!  chgFactor=39
      amp = (float) asensor /chgSense *1000 ;                    // Ampere berechnen
      if (chgChange ==1) amp = amp / -1;                         //Lade Strom Messwertumkehr von - nach +
      if (amp<0.0) chgCurrent = 0; else chgCurrent = amp;        // MesswertrÃ¼ckgabe in chgCurrent   (Wenn Messwert kleiner als 0 dann Messwert =0 anssonsten messwertau8sgabe in Ampere)
    }
    
    // Berechnung fÃ¼r Ladestromsensor INA169 board              wenn chgSelection =2
    if (chgSelection==2) {
      chgAMP = currentmitte;
      asensor = (chgAMP * 5) / 1023;                          // umrechnen von messwert in Spannung (5V Reference)
      amp = asensor / (10 * 0.1);                               // Ampere berechnen RL = 10k    Is = (Vout x 1k) / (RS x RL)
      if (amp<0.0) chgCurrent = 0; else chgCurrent = amp;       // MesswertrÃ¼ckgabe in chgCurrent   (Wenn Messwert kleiner als 0 dann Messwert =0 ansonsten MesswertauÃŸsgabe in Ampere)
    }      
    
    //  Ladestromsensor berechnen ********** Ende
    // ********************************************************************

    //batVoltage = batVolt
    //chgVoltage = chgvolt;
    //chgCurrent = current;          
  #endif        
}

bool BatteryControl::chargerConnected(){
  return ((chgVoltage > 5.0)  && (batVoltage > 8));
}

int BatteryControl::getChargingTimeMinutes(){
  if (!chargeRelayEnabled) return 0;
  return (Timer.powerTimeMinutes - chargingStartTimeMinutes);
}

void BatteryControl::enableChargingRelay(bool state){
  if (state == chargeRelayEnabled) return;
  Console.print(F("BatteryControll::enableChargingRelay "));
  Console.println(state);
  chargeRelayEnabled = state;
  digitalWrite(pinChargeRelay, state);
  if (state) chargingStartTimeMinutes = Timer.powerTimeMinutes;    
}


void BatteryControl::print(){
  Console.print(F("batVoltage="));
  Console.print(batVoltage);
  Console.print(F("  chgVoltage="));
  Console.print(chgVoltage);
  Console.print(F("  chgCurrent="));
  Console.print(chgCurrent);  
  Console.print(F("  chargerConnected="));
  Console.print(chargerConnected());
  Console.print(F("  chargeRelayEnabled="));
  Console.print(chargeRelayEnabled);    
  Console.print(F("  chargingTimeMinutes="));
  Console.print(getChargingTimeMinutes());
  Console.println();
}



