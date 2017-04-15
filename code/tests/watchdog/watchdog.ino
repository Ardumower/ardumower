// watch dog test for Arduino Mega/Due

// uses NVR RAM: a variable will be retained (not filled with zero) in start code

/* NOTE: for Due NVR RAM this needs to be added to C:\Users\...\AppData\Local\Arduino15\packages\arduino\hardware\sam\1.6.11\variants\arduino_due_x\linker_scripts\gcc\flash.ld
    // .noinit section which is used for uninitialized data that won't be zeroed at startup 
    .noinit ALIGN(4) (NOLOAD) :
    {
        . = ALIGN(4);
        _snoinit = . ;
        *(.noinit .noinit.*)
        *(COMMON)
        . = ALIGN(4);
        _enoinit = . ;
    } > ram    
*/  

#ifdef __AVR__
  #include <avr/wdt.h>  
   void(* resetFunc) (void) = 0; //declare reset function @ address 0
#endif 

#define pinBuzzer 53               // Buzzer


//non-initialized value
union configUnion{
  uint8_t    byte[6]; // match the below struct...
  struct {
    uint16_t wdflag;
    uint8_t state;    
  } val ;
} nvr  __attribute__ ((section (".noinit"))); 



int counter = 0;


void setup() 
{   
  #ifdef __AVR__
    WatchDog_Setup();
  #else
    watchdogEnable(8000);
  #endif  
  pinMode(pinBuzzer, OUTPUT);  
  delay(3000);  
  Serial.begin(115200);   
  
  if (nvr.val.wdflag != 0x1234){    
    Serial.println("this was a normal reset");  
    nvr.val.state = 0;    
  } else {
    Serial.println("this was reset by watchdog");  
    #ifdef __AVR__
      nvr.val.wdflag = 0; 
    #endif
  }   
  Serial.print("state is ");  
  Serial.println(nvr.val.state);   
  nvr.val.state = 1;  
}



void loop() 
{
  //Reset watchdog to prevent reset
  #ifdef __AVR__         // Mega  
    wdt_reset();                                                         
  #else
    watchdogReset();     // Due
  #endif
  delay(1000);
  Serial.print("normal loop ");
  Serial.println(counter);
  if(counter >= 10)
  { 
    while(true)
    {
      Serial.println("hanging loop");
      delay(1000);
    }
  }
  counter++;
}



#ifdef __AVR__         // Mega  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
  // WDTCSR configuration:
  // WDIE = 1: Interrupt Enable
  // WDE = 1 :Reset Enable
  // For 8000ms Time-out
  // WDP3 = 1
  // WDP2 = 1
  // WDP1 = 1
  // WDP0 = 1
*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void WatchDog_Setup(void)
{
  cli();                       // disable all interrupts
  wdt_reset();                 // reset the WDT timer

  MCUSR   =   0;
  // Enter Watchdog Configuration mode:
  WDTCSR |= (1 << WDCE) | (1 << WDE);
  // Set Watchdog settings:
  WDTCSR = (1 << WDIE) | (1 << WDE) | (1 << WDP3) | (1 << WDP2) | (1 << WDP1) | (1 << WDP0);
  sei();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
   WDIE - Enables Interrupts. This will give you the
   chance to include one last dying wish (or a few
   lines of code...) before the board is reset. This is a
   great way of performing interrupts on a regular
   interval should the watchdog be configured to not
   reset on time-out.

*/


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ISR(WDT_vect) // Watchdog timer interrupt.
{
  // Chance to express a last dying wish for the program
  // Include your code here - be careful not to use functions they may cause the interrupt to hang and
  // prevent a reset.
  wdt_disable();
  wdt_reset();  
  nvr.val.wdflag = 0x1234;
  resetFunc();  //call reset  
}


#else

// function required for watchdog to work for Arduino Due
void watchdogSetup(void) {
  // do what you want here     
}
#endif

 
