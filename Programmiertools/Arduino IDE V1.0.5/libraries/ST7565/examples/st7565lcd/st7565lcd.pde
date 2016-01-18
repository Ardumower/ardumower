#include "ST7565.h"

int ledPin =  13;    // LED connected to digital pin 13

// the LCD backlight is connected up to a pin so you can turn it on & off
#define BACKLIGHT_LED 10

// pin 9 - Serial data out (SID)
// pin 8 - Serial clock out (SCLK)
// pin 7 - Data/Command select (RS or A0)
// pin 6 - LCD reset (RST)
// pin 5 - LCD chip select (CS)
ST7565 glcd(9, 8, 7, 6, 5);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

// a bitmap of a 16x16 fruit icon
const static unsigned char __attribute__ ((progmem)) logo16_glcd_bmp[]={
0x30, 0xf0, 0xf0, 0xf0, 0xf0, 0x30, 0xf8, 0xbe, 0x9f, 0xff, 0xf8, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 
0x20, 0x3c, 0x3f, 0x3f, 0x1f, 0x19, 0x1f, 0x7b, 0xfb, 0xfe, 0xfe, 0x07, 0x07, 0x07, 0x03, 0x00, };

// The setup() method runs once, when the sketch starts
void setup()   {                
  Serial.begin(9600);

  Serial.print(freeRam());
  
  // turn on backlight
  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, HIGH);

  // initialize and set the contrast to 0x18
  glcd.begin(0x18);

  glcd.display(); // show splashscreen
  delay(2000);
  glcd.clear();

  // draw a single pixel
  glcd.setpixel(10, 10, BLACK);
  glcd.display();        // show the changes to the buffer
  delay(2000);
  glcd.clear();

  // draw many lines
  testdrawline();
  glcd.display();       // show the lines
  delay(2000);
  glcd.clear();

  // draw rectangles
  testdrawrect();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw multiple rectangles
  testfillrect();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw mulitple circles
  testdrawcircle();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a black circle, 10 pixel radius, at location (32,32)
  glcd.fillcircle(32, 32, 10, BLACK);
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw the first ~120 characters in the font
  testdrawchar();
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a string at location (0,0)
  glcd.drawstring(0, 0, "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation");
  glcd.display();
  delay(2000);
  glcd.clear();

  // draw a bitmap icon and 'animate' movement
  testdrawbitmap(logo16_glcd_bmp, LOGO16_GLCD_HEIGHT, LOGO16_GLCD_WIDTH);
}


void loop()                     
{}

// this handy function will return the number of bytes currently free in RAM, great for debugging!   
int freeRam(void)
{
  extern int  __bss_end; 
  extern int  *__brkval; 
  int free_memory; 
  if((int)__brkval == 0) {
    free_memory = ((int)&free_memory) - ((int)&__bss_end); 
  }
  else {
    free_memory = ((int)&free_memory) - ((int)__brkval); 
  }
  return free_memory; 
} 


#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

void testdrawbitmap(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  uint8_t icons[NUMFLAKES][3];
  srandom(666);     // whatever seed
 
  // initialize
  for (uint8_t f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random() % 128;
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random() % 5 + 1;
  }

  while (1) {
    // draw each icon
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS], logo16_glcd_bmp, w, h, BLACK);
    }
    glcd.display();
    delay(200);
    
    // then erase it + move it
    for (uint8_t f=0; f< NUMFLAKES; f++) {
      glcd.drawbitmap(icons[f][XPOS], icons[f][YPOS],  logo16_glcd_bmp, w, h, 0);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > 64) {
	icons[f][XPOS] = random() % 128;
	icons[f][YPOS] = 0;
	icons[f][DELTAY] = random() % 5 + 1;
      }
    }
  }
}


void testdrawchar(void) {
  for (uint8_t i=0; i < 168; i++) {
    glcd.drawchar((i % 21) * 6, i/21, i);
  }    
}

void testdrawcircle(void) {
  for (uint8_t i=0; i<64; i+=2) {
    glcd.drawcircle(63, 31, i, BLACK);
  }
}


void testdrawrect(void) {
  for (uint8_t i=0; i<64; i+=2) {
    glcd.drawrect(i, i, 128-i, 64-i, BLACK);
  }
}

void testfillrect(void) {
  for (uint8_t i=0; i<64; i++) {
      // alternate colors for moire effect
    glcd.fillrect(i, i, 128-i, 64-i, i%2);
  }
}

void testdrawline() {
  for (uint8_t i=0; i<128; i+=4) {
    glcd.drawline(0, 0, i, 63, BLACK);
  }
  for (uint8_t i=0; i<64; i+=4) {
    glcd.drawline(0, 0, 127, i, BLACK);
  }

  glcd.display();
  delay(1000);

  for (uint8_t i=0; i<128; i+=4) {
    glcd.drawline(i, 63, 0, 0, WHITE);
  }
  for (uint8_t i=0; i<64; i+=4) {
    glcd.drawline(127, i, 0, 0, WHITE);
  }
}
