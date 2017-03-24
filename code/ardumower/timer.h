// timer-based mowing

void Robot::setDefaultTime(){
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


// check timer
void Robot::checkTimer(){
  if (millis() < nextTimeTimer) return;
  nextTimeTimer = millis() + 60000;
  srand(time2minutes(datetime.time)); // initializes the pseudo-random number generator for c++ rand()
  randomSeed(time2minutes(datetime.time)); // initializes the pseudo-random number generator for arduino random()
  receiveGPSTime(); 
  boolean stopTimerTriggered = true;
  if (timerUse){    
    for (int i=0; i < MAX_TIMERS; i++){
      if (timer[i].active){
        if  ( (timer[i].daysOfWeek & (1 << datetime.date.dayOfWeek)) != 0) {
          int startmin = time2minutes(timer[i].startTime);
          int stopmin =  time2minutes(timer[i].stopTime);
          int currmin =  time2minutes(datetime.time);
          if ((currmin >= startmin) && (currmin < stopmin)){
            // start timer triggered
            stopTimerTriggered = false;
            if ((stateCurr == STATE_STATION) || (stateCurr == STATE_OFF)){
              Console.println(F("timer start triggered"));
              motorMowEnable = true;
              setNextState(STATE_FORWARD, 0);
            } 
          }           
        }
      if ((stopTimerTriggered) && (timer[i].active)){
      if (stateCurr == STATE_FORWARD){
        Console.println(F("timer stop triggered"));
        if (perimeterUse){
        setNextState(STATE_PERI_FIND, 0);
      }
        else setNextState(STATE_OFF,0);
      } 
    }
      }
    }
  }
}
