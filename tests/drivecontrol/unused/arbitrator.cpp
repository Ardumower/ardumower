#include "arbitrator.h"
#include "drivers.h"

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
    Console.println(F("ERROR: Arbitrator::add"));
    return;
  }
  Console.print(F("Arbitrator::addBehavior "));  
  Console.print(behaviorCount);
  Console.print(": ");  
  Console.println(behavior->name);
  behaviors[behaviorCount] = behavior;
  behaviorCount++;
}  
   
void Arbitrator::run(){
  Console.println(F("Arbitrator::run"));
  if (activeBehavior){
    activeBehavior->action();  
    Console.print(F("COMPLETED: "));
    Console.println(activeBehavior->name);    
  }
  activeBehavior = NULL;
  activeBehaviorIdx = -1;
  while (nextBehavior == NULL) {
    // no next behavior (no supression) => find out next behavior    
    Console.println(F("NO SUPPRESSION"));
    monitor();
  }
  activeBehaviorIdx=nextBehaviorIdx;    
  activeBehavior = nextBehavior;
  nextBehavior = NULL;    
  nextBehaviorIdx = -1;
  Console.print(F("-----CHANGED activeBehavior Idx: "));
  Console.print(activeBehaviorIdx);
  Console.print("  ");
  Console.print(activeBehavior->name);
  Console.println(F("-----"));
}
   
void Arbitrator::monitor() {
  //Console.println("Arbitrator::monitor");
  for (int idx=behaviorCount-1; idx >= 0; idx--) {   
    Behavior *behavior = behaviors[idx];
    
    /*Console.print("takeControl ");
    Console.print(idx);    
    Console.print("  ");    
    Console.println(behavior->name);    */
    
    if ( (behavior->enabled) && (idx > activeBehaviorIdx) && (behavior->takeControl()) ){
      setNextBehavior(behavior);
      //if (activeBehavior != NULL){    
      //  Console.println(F("Arbitrator::monitor suppressing"));
      //  activeBehavior->suppress(); 
      //}
      //nextBehavior = behavior;
      //nextBehaviorIdx = idx;             
      break;
    }
  }    
}

void Arbitrator::setNextBehavior(Behavior *behavior){
  //Console.print(F("Arbitrator::setNextBehavior "));
  //Console.println(behavior->name);
  if (activeBehavior != NULL){    
    Console.println(F("Arbitrator::monitor suppressing"));
    activeBehavior->suppress(); 
  }
  for (int idx=0; idx < behaviorCount; idx++){
    if (behaviors[idx] == behavior){
      nextBehavior = behavior;
      nextBehaviorIdx = idx;            
      break;
    }
  }  
}

