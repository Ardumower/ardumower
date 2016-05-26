#include <Wire.h> // Comes with Arduino IDE

// Get the LCD I2C Library here:

// https://bitbucket.org/fmalpartida/new-liquidcryst...

// Move any other LCD libraries to another folder or delete them

// See Library "Docs" folder for possible commands etc.

#include <LiquidCrystal_I2C.h>

/*-----( Declare Constants )-----*/

//none

/*-----( Declare objects )-----*/

// Set the pins on the I2C chip used for LCD connections:

// addr, en,rw,rs,d4,d5,d6,d7,bl,blpol

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7); // Set the LCD I2C address

/*-----( Declare Variables )-----*/

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

void setup()
{
   int charBitmapSize = (sizeof(charBitmap ) / sizeof (charBitmap[0]));

  // Switch on the backlight
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);
  
  lcd.begin(20,4);               // initialize the lcd 

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
   delay (200);
}
