#ifndef TIMER_H
#define TIMER_H

// Ardumower RTC/timer
// requires: DS1307 RTC 

#include <Arduino.h>

#define MAX_TIMERS 5

// ---------- date time --------------------------------------

struct timehm_t {
  byte hour;
  byte minute;  
};

typedef struct timehm_t timehm_t;

struct date_t {
  byte dayOfWeek;
  byte day;
  byte month;
  short year;  
};

typedef struct date_t date_t;

struct datetime_t {
  timehm_t time;
  date_t date;
};

typedef struct datetime_t datetime_t;

// ---------- timers --------------------------------------
struct ttimer_t {
  boolean active;
  timehm_t startTime;
  timehm_t stopTime;
  byte daysOfWeek;
};

typedef struct ttimer_t ttimer_t;



class TimerControl
{
  public:
    bool enable;
    unsigned long powerTimeMinutes;  // power-ON time (minutes)
    ttimer_t timer[MAX_TIMERS];  // timers
    datetime_t datetime;         // current date & time                                         
    bool stopTimerTriggered;     // has stop timer triggered?
    bool startTimerTriggered;    // has start timer triggered?
    TimerControl();
    void setup();
    bool rtcError;              // RTC communication error?
    void run();    
    void print();
    void writeRTCDateTime();  // write datetime to RTC
    int getDayOfWeek(int month, int day, int year, int CalendarSystem);
    String date2str(date_t date);
    int time2minutes(timehm_t time);
    String time2str(timehm_t time);
    void minutes2time(int minutes, timehm_t &time);            
  private:
    void checkTimer();
    void setDefaultTime();
    unsigned long nextTimerTime;
    boolean readDS1307(datetime_t &dt);
    boolean setDS1307(datetime_t &dt);        
};


extern TimerControl Timer;  

  
#endif

