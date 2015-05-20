#include "arbitrator.h"


// stored in increasing priority order
Behavior *behaviors[MAX_BEHAVIORS];    

    
Arbitrator::Arbitrator(){
  behaviorCount = 0;
  activeBehavior = nextBehavior = NULL;
  activeBehaviorIdx = 0;
  nextBehaviorIdx = -1;
}  
 
void Arbitrator::addBehavior(Behavior *behavior){
  if (behaviorCount >= MAX_BEHAVIORS) {
    Serial.println("ERROR: Arbitrator::add");
    return;
  }
  Serial.print("Arbitrator::addBehavior ");  
  Serial.println(behavior->name);
  behaviors[behaviorCount] = behavior;
  behaviorCount++;
}  
   
void Arbitrator::run(){
  if (activeBehavior){
    activeBehavior->action();  
    Serial.print("COMPLETED: ");
    Serial.println(activeBehavior->name);    
  }
  activeBehavior = NULL;
  activeBehaviorIdx = -1;
  if (nextBehavior == NULL) {
    // no next behavior (no supression) => find out next behavior    
    Serial.println("NO SUPPRESSION");
    monitor();
  }
  activeBehaviorIdx=nextBehaviorIdx;    
  activeBehavior = nextBehavior;
  nextBehavior = NULL;    
  Serial.print("CHANGED activeBehavior Idx: ");
  Serial.print(activeBehaviorIdx);
  Serial.print("  ");
  Serial.println(activeBehavior->name);
}
   
void Arbitrator::monitor() {
  for (int idx=behaviorCount-1; idx >= 0; idx--) {   
    Behavior *behavior = behaviors[idx];
    if ((behavior->takeControl()) && (idx >= activeBehaviorIdx)){
      if (activeBehavior){
        activeBehavior->suppress(); 
      }
      nextBehavior = behavior;
      nextBehaviorIdx = idx;      
      break;
    }
  }    
}


