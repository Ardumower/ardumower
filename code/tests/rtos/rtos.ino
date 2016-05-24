
/* RTOS test  (requires FreeRTOS, imu.cpp)
 */

#include <Arduino.h>
#include <Wire.h>
#ifdef __AVR__
  // Arduino Mega
  #include <EEPROM.h>
  //#include <FreeRTOS_AVR.h>
#else
  // Arduino Due
  #include <FreeRTOS_ARM.h>
  #include "due.h"
#endif

#include "imu.h"

class Test2 {
  public:
    Test2(){}
    int  run(){ return 42; }
};

class Test {
  public:
    Test2 test2;
    Test(){}
    int run(){ return test2.run(); }    
};


// handle for blink task
xTaskHandle imuTask;
unsigned long nextInfoTime = 0;
volatile long counter = 0;
volatile float ypr[3];
const uint8_t LED_PIN = 13;
//Test test;
//AHRS ahrs;
IMU imu;
  

// http://www.freertos.org/FreeRTOS_Support_Forum_Archive/July_2010/freertos_Is_it_possible_create_freertos_task_in_c_3778071.html

static void vIMUTask(void *pvParameters) {
  pinMode(LED_PIN, OUTPUT);  
  //imu.init();  
  portTickType xLastWakeTime;
  const portTickType xTimeInc = 10;
  xLastWakeTime = xTaskGetTickCount();
  for (;;) {
    //digitalWrite(LED_PIN, HIGH);
    vTaskDelayUntil( &xLastWakeTime, xTimeInc );
    //AHRS *ahrs = (AHRS*)pvParameters;
    //ahrs->update(0.2, 0.1, 0.2, 0.1, 0.2, 0.1, 0.2, 0.1, 0.2, 5000, true);
    //Test *test = (Test*)pvParameters;    
    //counter = test->run();
    IMU *imu = (IMU*)pvParameters;
    imu->getEulerRad((float*)ypr);
    //Serial.println("TASK");
    //digitalWrite(LED_PIN, LOW);
    //vTaskDelay((10L * configTICK_RATE_HZ) / 1000L);
    counter++;
  }
}


void setup()  {
  //robot.setup();
  Wire.begin();
  Serial.begin(19200);
  Serial.println("START");
  //ahrs.update(0.2, 0.1, 0.2, 0.1, 0.2, 0.1, 0.2, 0.1, 0.2, 5000, true);
  imu.init();  
  delay(2000);

  xTaskCreate(vIMUTask,
              (signed portCHAR *)"IMU",
              configMINIMAL_STACK_SIZE + 300,
              &imu,
              tskIDLE_PRIORITY + 2,
              &imuTask);

  vTaskStartScheduler();
  // should never return
  Serial.println(F("Die"));
  while (1);
}

void loop()  {
  //  robot.loop();
  while (1) {
    if (millis() >= nextInfoTime) {
      nextInfoTime = millis() + 300;
      Serial.print("LOOP ");
      //Serial.println(imu.getCallCounter());
      Serial.print(counter);
      Serial.print('\t');
      Serial.print(ypr[0]/PI*180);
      Serial.print('\t');
      Serial.print(ypr[1]/PI*180);
      Serial.print('\t');
      Serial.println(ypr[2]/PI*180);
      //vTaskDelay((1000L * configTICK_RATE_HZ) / 1000L);
    }
  }
}




