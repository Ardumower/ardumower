#include <Wire.h> // Comes with Arduino IDE

// Get the LCD I2C Library here:

// https://bitbucket.org/fmalpartida/new-liquidcryst...

// Move any other LCD libraries to another folder or delete them

// See Library "Docs" folder for possible commands etc.

#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/

//none

/*-----( Declare objects )-----*/
//////////////////////////////////////////////////////////////////////////////////////////////////////
//Initialize the LCD library
//LiquidCrystal_I2C lcd(0x27,16,2);
//                    addr, en,rw,rs,d4,d5,d6,d7
// LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7);  // Set the LCD I2C address

// The address pins A0-A2 are pulled high with the three 10k resistors at the bottom of the picture.
// If the three pads A0-A2 are jumpered, the address is changed to 0x20.
// https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/schematics#!i2c-connection
// Set the pins on the I2C chip used for LCD connections:

// Set the correct Address !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
//LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7); // Set the LCD I2C address at PCF8574AT
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); // Set the LCD I2C address  at PCF8574T
//////////////////////////////////////////////////////////////////////////////////////////////////////


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

void setup()
{
  Wire.begin();
  Serial.begin(9600);  // start serial for output
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
  delay ( 3000 );
}

void loop()
{
  if (millis() >= nextDisplayRefresh) {
    nextDisplayRefresh = millis() + 500;
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
}
