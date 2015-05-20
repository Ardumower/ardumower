#include "arbitrator.h"

#define MAX_BEHAVIORS 30

// stored in increasing priority order
Behavior *behaviors[MAX_BEHAVIORS];    

    
Arbitrator::Arbitrator(){
  behaviorCount = 0;
  activeBehavior = nextBehavior = NULL;
  activeBehaviorIdx = nextBehaviorIdx = -1;
}  
 
void Arbitrator::addBehavior(Behavior *behavior){
  if (behaviorCount >= MAX_BEHAVIORS) {
    Serial.println("ERROR: Arbitrator::add");
    return;
  }
  Serial.print("Arbitrator::addBehavior ");  
  Serial.print(behaviorCount);
  Serial.print(": ");  
  Serial.println(behavior->name);
  behaviors[behaviorCount] = behavior;
  behaviorCount++;
}  
   
void Arbitrator::run(){
  Serial.println("Arbitrator::run");
  if (activeBehavior){
    activeBehavior->action();  
    Serial.print("COMPLETED: ");
    Serial.println(activeBehavior->name);    
  }
  activeBehavior = NULL;
  activeBehaviorIdx = -1;
  while (nextBehavior == NULL) {
    // no next behavior (no supression) => find out next behavior    
    Serial.println("NO SUPPRESSION");
    monitor();
  }
  activeBehaviorIdx=nextBehaviorIdx;    
  activeBehavior = nextBehavior;
  nextBehavior = NULL;    
  nextBehaviorIdx = -1;
  Serial.print("CHANGED activeBehavior Idx: ");
  Serial.print(activeBehaviorIdx);
  Serial.print("  ");
  Serial.println(activeBehavior->name);
}
   
void Arbitrator::monitor() {
  //Serial.println("Arbitrator::monitor");
  for (int idx=behaviorCount-1; idx >= 0; idx--) {   
    Behavior *behavior = behaviors[idx];
    
    /*Serial.print("takeControl ");
    Serial.print(idx);    
    Serial.print("  ");    
    Serial.println(behavior->name);    */
    
    if ( (idx > activeBehaviorIdx) && (behavior->takeControl()) ){
      if (activeBehavior != NULL){    
        Serial.println("Arbitrator::monitor suppressing");
        activeBehavior->suppress(); 
      }
      nextBehavior = behavior;
      nextBehaviorIdx = idx;            
      break;
    }
  }    
}


