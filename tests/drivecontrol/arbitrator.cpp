#include "arbitrator.h"


// stored in increasing priority order
Behavior *behaviors[MAX_BEHAVIORS];    

    
Arbitrator::Arbitrator(){
  behaviorCount = 0;
  activeBehavior = 0;
  activeBehaviorIdx = 0;
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
   
   
void Arbitrator::run() {
  for (int idx=behaviorCount-1; idx >= 0; idx--) {   
    Behavior *behavior = behaviors[idx];
    if ((behavior->takeControl()) && (idx >= activeBehaviorIdx)){
      if (activeBehavior){
       activeBehavior->suppress(); 
      }
      activeBehavior = behavior;
      activeBehaviorIdx = idx;      
      Serial.print("CHANGED activeBehavior Idx: ");
      Serial.print(activeBehaviorIdx);
      Serial.print("  ");
      Serial.println(activeBehavior->name);
      break;
    }
  }  
  bool actionCompleted = activeBehavior->actionCompleted();  
  if (actionCompleted){
    Serial.print("COMPLETED: ");
    Serial.println(activeBehavior->name);    
    activeBehaviorIdx=-1;
  }
}


