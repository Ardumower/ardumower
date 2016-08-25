// ************************** DUE Testcode components ***************************************
// ******************************************************************************************
// TESTVERSION: 1
// SD-Card, RTC1307, BT HC05 ZS-040, WTV020
// ******************************************************************************************
// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#include <Wire.h> // Comes with Arduino IDE
#include <Arduino.h>

// default I2C address is 0x68
// default I2C address is:  B1101000
byte DS1307_ADDRESS = B1101000;

byte hour = 1;
byte minute = 1;
byte dayOfWeek = 1;
byte day = 1;
byte month = 1;
short year = 2016;
#define LED_PIN 13
bool blinkState = false;
long lastSecond;

// Get the LCD I2C Library here:
// https://bitbucket.org/fmalpartida/new-liquidcryst...
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.

#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/

//none

/*-----( Declare objects )-----*/
//                    addr, en,rw,rs,d4,d5,d6,d7
// LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);  // Set the LCD I2C address

// The address pins A0-A2 are pulled high with the three 10k resistors at the bottom of the picture.
// If the three pads A0-A2 are jumpered, the address is changed to 0x20.
// https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/schematics#!i2c-connection
// Set the pins on the I2C chip used for LCD connections:

// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7); // Set the LCD I2C address

byte AdrKeyPad = 0x20;

/*-----( Declare Variables )-----*/
long nextDisplayRefresh = 0;
//none

// Creat a set of new characters
const uint8_t charBitmap[][8] = {
  { 0xc, 0x12, 0x12, 0xc, 0, 0, 0, 0 },
  { 0x6, 0x9, 0x9, 0x6, 0, 0, 0, 0 },
  { 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0, 0x0 },
  { 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0, 0x0 },
  { 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0, 0x0 },
  { 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0, 0x0 },
  { 0x0, 0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0 },
  { 0x0, 0x0, 0x0, 0xc, 0x12, 0x12, 0xc, 0x0 }
};

const byte keyMap[2][20] = {
  { 23, 27, 29, 30, 55, 59, 61, 62, 87, 91, 93, 94, 119, 123, 125, 126, 151, 155, 157, 158},
  { 13, 82, 48, 76, 27, 57, 56, 55, 68, 54, 53, 52, 85, 51, 50, 49, 42, 35, 66, 65 }
};
/*
  SD card read/write

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

File myFile;

#include <Wtv020sd16p.h>

int resetPin = 40;  // The pin number of the reset pin.
int clockPin = 41;  // The pin number of the clock pin.
int dataPin = 42;  // The pin number of the data pin.
int busyPin = 43;  // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);  // start serial for output
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //Initializes the module.
  wtv020sd16p.reset();
  
  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  Wire.begin();
  //-------------------------------------------------------------------------------------------------------------------
  // initialize device
  Serial.println("Initializing I2C devices...");
  Serial.println("Testing device connections...");
  Serial.print("RTC default address=");
  Serial.println(DS1307_ADDRESS); // verify connection
  if (findDS1307()) {
    testRead();
    Serial.println("DS1307 connection successful");
  } else {
    Serial.println("DS1307 connection failed");
  }
  //testWriteStatic();
   // testWrite();
  // configure LED pin for output
  pinMode(LED_PIN, OUTPUT);

  // set sample time
  lastSecond = millis() + 1000;
  //-------------------------------------------------------------------------------------------------------------------
  int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));

  // Switch on the backlight
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.begin(20, 4);              // initialize the lcd

  for ( int i = 0; i < charBitmapSize; i++ )
  {
    lcd.createChar ( i, (uint8_t *)charBitmap[i] );
  }

  lcd.home ();                   // go home
  lcd.print("Hello, ARDUINO ");
  lcd.setCursor ( 0, 3 );        // go to the next line
  lcd.print ("Hello ArduMower");
  
  pfodSetup();
  
  //Plays asynchronously an audio file.
  wtv020sd16p.asyncPlayVoice(1);

}

void loop() {
  if (millis() >= nextDisplayRefresh) {
    nextDisplayRefresh = millis() + 500;
    lcd.setCursor (1, 2 );        // go to line
    if(hour < 10)lcd.print("0");
    lcd.print(hour);
    lcd.print(":");
    if(minute < 10)lcd.print("0");
    lcd.print(minute);
    lcd.print("  ");
    if(day < 10)lcd.print("0");
    lcd.print(day);
    lcd.print(".");
    if(month < 10)lcd.print("0");
    lcd.print(month);
    lcd.print(".");
    lcd.print(year);
    lcd.home ();
    // Do a little animation by writing to the same location
    for ( int i = 0; i < 2; i++ )
    {
      for ( int j = 0; j < 16; j++ )
      {
        lcd.print (char(random(7)));
      }
      lcd.setCursor ( 0, 1 );
    }
  }

  byte key;
  char charKey;
  static byte rowKeyCounter = 0;
  byte rowKey = (rowKeyCounter << 5) | 0x1F; // calculate the row value
  Wire.beginTransmission(AdrKeyPad); // transmit to device 0x20 Keypad
  Wire.write(rowKey);              // sends one byte
  Wire.endTransmission();    // stop transmitting
  delay(10);

  Wire.requestFrom(AdrKeyPad, 1);    // request 1 byte from slave device 0x20 Keypad
  while (Wire.available()) { // slave may send less than requested
    key = Wire.read(); // receive a byte
    if (key != rowKey) { // if key pressd
      for (byte x = 0; x < 21; x++) { // search for Key-Nr
        if (key == keyMap[0][x]) { // find key in table
          charKey = char(keyMap[1][x]); // mapping char to Key-Nr
          key = keyMap[1][x]; // mapping char to Key-Nr
          break; // mapping is done
        }
      }
      Serial.println(key);         // print the key
      lcd.setCursor ( 17, 2 );        // go to the next line
      lcd.print (key);
      lcd.setCursor ( 18, 3 );        // go to the next line
      lcd.print (charKey);
    }
  }

  do { // wait until key was released
    delay(10);
    Wire.requestFrom(AdrKeyPad, 1);    // request 1 byte from slave device 0x20 Keypad
    while (Wire.available()) { // slave may send less than requested
      key = Wire.read(); // receive a byte

    }
  } while (key != rowKey);

  rowKeyCounter += 1;
  if ( rowKeyCounter > 7) rowKeyCounter = 0;

  //-----------------------------------------------------------------------------------------------------------------------------
  // read all clock info from device
  if (millis() >= lastSecond) { // wait one second so the next reading will be different
    lastSecond = millis() + 1000;
    if (readDS1307()) {
      Serial.print("reading RTC time=");
      Serial.print(hour);
      Serial.print(":");
      Serial.print(minute);
      Serial.print("  dateOfWeek=");
      Serial.print(dayOfWeek);
      Serial.print("  date=");
      Serial.print(day);
      Serial.print(".");
      Serial.print(month);
      Serial.print(".");
      Serial.println(year);
    } else {
      Serial.println("DS1307 connection failed");
    }
    Serial.println();

    // blink LED to indicate activity
    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
  }
  pfodLoop();

  
}


