
// ------ choose ONLY ONE robot configuration ---------------------------------------------
#define USE_MOWER
//#define USE_MINI


// ----------------------------------------------------------------------------------------

#ifdef USE_MOWER
  #include "mower.h"  // Ardumower Chassis Kit 1.0  (see mower.cpp for actual code)
#endif

#ifdef USE_BLANK_MEGA
  #include "mega.h"
#endif

#ifdef USE_MINI
  #include "mini.h"  // Mini robot
#endif

#ifdef USE_SIM
  #include "sim.h"  // simbad simulator - maybe future :)
#endif


