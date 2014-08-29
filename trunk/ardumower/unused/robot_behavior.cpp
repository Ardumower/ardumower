
#define BEHAVIOR_COUNT 5

    // --------- behavior -------------------------------
    /*Behavior *behaviorCurr; // current behavior
    int behaviorCurrIdx;    // current behavior index
    Behavior *behaviors[BEHAVIOR_COUNT];  // all behaviors    
    boolean suppresses[BEHAVIOR_COUNT][BEHAVIOR_COUNT]; // suppress matrix*/



void Robot::initSuppresses(boolean matrix[BEHAVIOR_COUNT][BEHAVIOR_COUNT]){
  for (int i=0; i < BEHAVIOR_COUNT; i++){
    for (int j=0; j < BEHAVIOR_COUNT; j++){
       suppresses[i][j] = matrix[i][j];
    }
  }
  behaviorCurrIdx = 0;
}


void Robot::performBehavior(void) {
   boolean isActive[BEHAVIOR_COUNT];
   for (int i = 0; i < BEHAVIOR_COUNT; i++) {
     isActive[i] = ( (behaviors[i] != NULL) && (behaviors[i]->isActive()) );
   }
   boolean ranABehavior = false;
   while (!ranABehavior) {
      boolean runCurrentBehavior =  isActive[behaviorCurrIdx];
      if (runCurrentBehavior) {
         for (int i = 0; i < BEHAVIOR_COUNT; i++) {
            if ((isActive[i]) && (suppresses[i][behaviorCurrIdx])) {
               runCurrentBehavior = false; // behavior is suppressed
               break;
            }
         }
      }

      if (runCurrentBehavior) {
         if (behaviorCurrIdx < BEHAVIOR_COUNT) {
            behaviors[behaviorCurrIdx]->act();            
         }
         ranABehavior = true;
      }

      if (BEHAVIOR_COUNT > 0) {
         behaviorCurrIdx = (behaviorCurrIdx + 1)
                  % BEHAVIOR_COUNT;
      }
   }
}




void Mower::initBehaviors(void){
   
  /*memset(behaviors, 0, sizeof behaviors);
  behaviors[0] = new ManualBehavior(this);
  behaviors[1] = new ObstacleBehavior(this);
  behaviors[2] = new MowBehavior(this);
  behaviors[3] = new TrackBehavior(this);
  
  // manual behavior 
  // false, ...           not suppressed by manual behavior
  // false, ...           not suppressed by obstacle behavior
  // false, ...           not suppressed by mow behavior 
  // false, ...           not suppressed by track behavior
  
  boolean suppresses[BEHAVIOR_COUNT][BEHAVIOR_COUNT] = {
    { false, true,  true,  true  }, 
    { false, false, true,  true  }, 
    { false, false, false, true  }, 
    { false, false, false, false }  
  };
  
  initSuppresses(suppresses);    */
}




