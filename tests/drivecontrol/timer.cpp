#include "timer.h"
#include "drivers.h"

TimerControl Timer;

#define DS1307_ADDRESS B1101000


char *dayOfWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};



TimerControl::TimerControl(){    
  enable = false;    
  powerTimeMinutes = 0;
  nextTimerTime = 60000;    
  stopTimerTriggered = true;
  startTimerTriggered = false;
}

void TimerControl::setup(){
  Console.println(F("TimerControl::setup"));
  setDefaultTime();      
  rtcError = false;
}

// call this in main loop
void TimerControl::run(){
  if (!enable) return;
  if (millis() < nextTimerTime) return;
  nextTimerTime = millis() + 60000;  
  powerTimeMinutes++;
  readDS1307(datetime);
  print();
  checkTimer();
}

// Returns the day of week (0=Sunday, 6=Saturday) for a given date
int TimerControl::getDayOfWeek(int month, int day, int year, int CalendarSystem)
{
     // CalendarSystem = 1 for Gregorian Calendar, 0 for Julian Calendar
     if (month < 3)
     {
           month = month + 12;
           year = year - 1;
     }
     return (
             day
             + (2 * month)
             + int(6 * (month + 1) / 10)
             + year
             + int(year / 4)
             - int(year / 100)
             + int(year / 400)
             + CalendarSystem
            ) % 7;
}


int TimerControl::time2minutes(timehm_t time){
  return (time.hour * 60 + time.minute);
}

void TimerControl::minutes2time(int minutes, timehm_t &time){
  time.hour   = minutes / 60;
  time.minute = minutes % 60;
}

String TimerControl::time2str(timehm_t time){
  String s = String(time.hour/10);
  s += (time.hour%10);
  s += ":";
  s += (time.minute/10);
  s += (time.minute%10);
  return s;
}
   
String TimerControl::date2str(date_t date){
  String s = dayOfWeek[date.dayOfWeek];
  s += " ";
  s += date.day / 10;
  s += date.day % 10;
  s += ".";
  s += date.month / 10;
  s += date.month % 10;
  s += ".";  
  s += date.year; 
  return s;
}   


// DS1307 real time driver
boolean TimerControl::readDS1307(datetime_t &dt){
  byte buf[8];  
  if (I2CreadFrom(DS1307_ADDRESS, 0x00, 8, buf, 3) != 8) {
    Console.println(F("ERROR: DS1307 comm"));    
    rtcError = true;
    return false;
  }      
  if (   ((buf[0] >> 7) != 0) || ((buf[1] >> 7) != 0) || ((buf[2] >> 7) != 0) || ((buf[3] >> 3) != 0) 
      || ((buf[4] >> 6) != 0) || ((buf[5] >> 5) != 0) || ((buf[7] & B01101100) != 0) ) {    
    Console.println(F("ERROR: DS1307 data1"));    
    rtcError = true;
    return false;
  }
  datetime_t r;
  r.time.minute    = 10*((buf[1] >>4) & B00000111) + (buf[1] & B00001111);
  r.time.hour      = 10*((buf[2] >>4) & B00000111) + (buf[2] & B00001111);
  r.date.dayOfWeek = (buf[3] & B00000111);
  r.date.day       = 10*((buf[4] >>4) & B00000011) + (buf[4] & B00001111);
  r.date.month     = 10*((buf[5] >>4) & B00000001) + (buf[5] & B00001111);
  r.date.year      = 10*((buf[6] >>4) & B00001111) + (buf[6] & B00001111);
  if (    (r.time.minute > 59) || (r.time.hour > 23) || (r.date.dayOfWeek > 6)  
       || (r.date.month > 12)  || (r.date.day > 31)  || (r.date.day < 1)         
       || (r.date.month < 1)   || (r.date.year > 99) ){
    Console.println(F("ERROR: DS1307 data2"));    
    rtcError = true;
    return false;
  }  
  r.date.year      += 2000;
  dt = r;
  return true;
}

boolean TimerControl::setDS1307(datetime_t &dt){
  byte buf[7];
  if (I2CreadFrom(DS1307_ADDRESS, 0x00, 7, buf, 3) != 7){
    Console.println(F("ERROR: DS1307 comm"));    
    rtcError = true;
    return false;
  }
  buf[0] = buf[0] & B01111111; // enable clock
  buf[1] = ((dt.time.minute / 10) << 4) | (dt.time.minute % 10);
  buf[2] = ((dt.time.hour   / 10) << 4) | (dt.time.hour   % 10);
  buf[3] = dt.date.dayOfWeek;
  buf[4] = ((dt.date.day    / 10) << 4) | (dt.date.day    % 10);
  buf[5] = ((dt.date.month  / 10) << 4) | (dt.date.month  % 10);
  buf[6] = ((dt.date.year % 100  / 10) << 4) | (dt.date.year % 10);
  I2CwriteTo(DS1307_ADDRESS, 0x00, 7, buf);
  return true;
}

void TimerControl::setDefaultTime(){
  datetime.time.hour = 12;
  datetime.time.minute = 0;
  datetime.date.dayOfWeek = 0;
  datetime.date.day = 1;
  datetime.date.month = 1;
  datetime.date.year = 2013;
  timer[0].active = false;
  timer[0].daysOfWeek= B01111110;
  timer[0].startTime.hour = 9;
  timer[0].stopTime.hour = 11;
}

void TimerControl::print(){
  Console.print(F("powerTimeMinutes: "));
  Console.print(powerTimeMinutes);
  Console.print(F("  RTC date: "));
  Console.println(date2str(datetime.date));
}

void TimerControl::writeRTCDateTime(){
  Console.print(F("RTC date set: "));
  Console.println(date2str(datetime.date));  
  setDS1307(datetime);
}


// check timer
void TimerControl::checkTimer(){
  stopTimerTriggered = true;
  startTimerTriggered = false;
  
  for (int i=0; i < MAX_TIMERS; i++){
      if (timer[i].active){
        if  ( (timer[i].daysOfWeek & (1 << datetime.date.dayOfWeek)) != 0) {
          int startmin = time2minutes(timer[i].startTime);
          int stopmin =  time2minutes(timer[i].stopTime);
          int currmin =  time2minutes(datetime.time);
          if ((currmin >= startmin) && (currmin < stopmin)){
            // start timer triggered
            stopTimerTriggered = false;            
            Console.println(F("timer start triggered"));
            startTimerTriggered = true;                          
          }           
        }
      }
  }
}


