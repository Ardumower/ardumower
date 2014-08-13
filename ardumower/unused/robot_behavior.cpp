
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


