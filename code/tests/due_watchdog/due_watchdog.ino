// watch dog test for Arduino Due

// uses NVR RAM: a variable will be retained (not filled with zero) in start code

/* NOTE: for NVR RAM this needs to be added to C:\Users\...\AppData\Local\Arduino15\packages\arduino\hardware\sam\1.6.11\variants\arduino_due_x\linker_scripts\gcc\flash.ld
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
 

#define pinBuzzer 53               // Buzzer


//non-initialized value
union configUnion{
  uint8_t    byte[6]; // match the below struct...
  struct {
    uint16_t magic;
    uint8_t state;    
  } val ;
} nvr  __attribute__ ((section (".noinit"))); 



int counter = 0;


void watchdogSetup(void) {
  // do what you want here
}

void setup() 
{
  pinMode(pinBuzzer, OUTPUT);
  delay(3000);
  watchdogEnable(10000);
  Serial.begin(115200); 
  
  
  if (nvr.val.magic != 0x1234){    
    Serial.println("this was a normal reset");  
    nvr.val.state = 0;
    nvr.val.magic = 0x1234;
  } else {
    Serial.println("this was reset by watchdog");  
  }  
  Serial.print("state is ");  
  Serial.println(nvr.val.state);   
  nvr.val.state = 1;  
}



void loop() 
{
  delay(500);
  Serial.print("normal loop ");
  Serial.println(counter);
  if(counter >= 10)
  { 
    while(true)
    {
      Serial.println("hanging loop");
      delay(100);
    }
  }
  counter++;
}




