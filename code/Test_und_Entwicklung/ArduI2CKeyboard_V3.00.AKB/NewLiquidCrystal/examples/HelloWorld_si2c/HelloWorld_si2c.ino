#include <Wire.h>
#include <LiquidCrystal_SI2C.h>

LiquidCrystal_SI2C	lcd(0x4e,2,1,0,4,5,6,7);

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

  lcd.begin (16,2);
  lcd.setBacklightPin(3, POSITIVE);
  lcd.setBacklight(HIGH);

   for ( int i = 0; i < charBitmapSize; i++ )
   {
      lcd.createChar ( i, (uint8_t *)charBitmap[i] );
   }

  lcd.home ();                   // go home
  lcd.print("Hello, Arduino ");  
  lcd.setCursor ( 0, 1 );        // go to the next line
  for ( int i = 0; i < 8; i++ )
    lcd.print (char(i));
  delay ( 1000 );
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
   delay (500);
}

