// UTFT_ViewFont 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the included fonts.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t SevenSegNumFont[];

// Remember to change the model parameter to suit your display module!
UTFT myGLCD(ITDB32S,15,18,11,32);

void setup()
{
  myGLCD.InitLCD();

  myGLCD.clrScr();
}

void loop()
{
  myGLCD.setBackColor(0, 0, 0);

  myGLCD.setColor(0, 0, 255);
  myGLCD.setFont(BigFont);
  myGLCD.print(" !\"#$%&'()*+,-./", CENTER, 0);
  myGLCD.print("0123456789:;<=>?", CENTER, 16);
  myGLCD.print("@ABCDEFGHIJKLMNO", CENTER, 32);
  myGLCD.print("PQRSTUVWXYZ[\\]^_", CENTER, 48);
  myGLCD.print("`abcdefghijklmno", CENTER, 64);
  myGLCD.print("pqrstuvwxyz{|}~ ", CENTER, 80);

  myGLCD.setColor(255, 0, 0);
  myGLCD.setFont(SmallFont);
  myGLCD.print(" !\"#$%&'()*+,-./0123456789:;<=>?", CENTER, 120);
  myGLCD.print("@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_", CENTER, 132);
  myGLCD.print("`abcdefghijklmnopqrstuvwxyz{|}~ ", CENTER, 144);

  myGLCD.setColor(0, 255, 0);
  myGLCD.setFont(SevenSegNumFont);
  myGLCD.print("0123456789", CENTER, 190);

  while(1) {};
}

