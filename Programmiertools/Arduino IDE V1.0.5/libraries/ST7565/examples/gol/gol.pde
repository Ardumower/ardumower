// (c) Tom Soulanille - public domain!
// Modified from:
// (c) adafruit industries - public domain!

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

// the buffer for the image display
extern uint8_t st7565_buffer[1024];

// The setup() method runs once, when the sketch starts
void setup()   {                
  Serial.begin(9600);

  Serial.println(freeRam());
  
  pinMode(BACKLIGHT_LED, OUTPUT);
  digitalWrite(BACKLIGHT_LED, HIGH);

  glcd.st7565_init();
  glcd.st7565_command(CMD_DISPLAY_ON);
  glcd.st7565_command(CMD_SET_ALLPTS_NORMAL);
  glcd.st7565_set_brightness(0x18);

  glcd.display(); // show splashscreen

  glcd.clear();

  Serial.println(freeRam());
  
  // A little of Conway's game of Life
  drawGabrielsp138();
}


void loop()                     
{
  lifeNextGen(&glcd);
  glcd.display();
}

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

// http://www.conwaylife.com/wiki/index.php?title=Gabriel%27s_p138
void drawGabrielsp138() {
  uint8_t *p;
  // buffer[x+ (y/8)*128] |= _BV(7-(y%8));
  p = st7565_buffer + 53 + 7 + 2*128;
  *p++=0x1c; *p++=0x24; *p++=0x20; *p=0x38;
  p = st7565_buffer + 53 + 0 + 3*128;
  *p++=0xe; *p++=9; *p++=9; *p=3;
  p = st7565_buffer + 53 + 17 + 3*128;
  *p++=0x60; *p++=0x48; *p++=0x48; *p=0x38;
  p = st7565_buffer + 53 + 10 + 4*128;
  *p++=0xe; *p++=2; *p++=0x12; *p=0x1c;
}

void drawGlider() {
  uint8_t *p;
  p = st7565_buffer + 62 + 4*128;
  *p++=1; *p++=5; *p=3;  
}

uint8_t fifoBuf[LCDHEIGHT/8];
int fifoIndex = 0;
boolean bitFIFO(boolean in) {
  if (fifoIndex >= LCDHEIGHT) fifoIndex = 0;
  uint8_t bitMask = 1 << (fifoIndex&7);
  uint8_t fbi = fifoIndex>>3;
  boolean rv = fifoBuf[fbi] & bitMask;
  if (in) {
    fifoBuf[fbi] |= bitMask;
  } else {
    fifoBuf[fbi] &= ~bitMask;
  }
  fifoIndex++;
  return rv;
}

int lifeLivingAround(ST7565 *g, int x, int y) {
  int dx, dy, n = 0;
  for (dy=-1; dy<2; dy++)
    for (dx=-1; dx<2; dx++)
      if (dx || dy) {
        n += g->getpixel(x+dx, y+dy);
      }
  return n;
}

void lifeNextGen() {
  lifeNextGen(&glcd);
}

void lifeNextGen(ST7565 *g) {
  int x, y, n;
  boolean newState, pix, zpix;
  for (x=0; x<=LCDWIDTH; x++) {
    for (y=0; y<LCDHEIGHT; y++) {
      n = lifeLivingAround(g, x, y);
      newState = n==3 || n==2 && g->getpixel(x, y);
      zpix = pix;
      pix = bitFIFO(newState);
      if (x && y) g->setpixel(x-1, y-1, zpix);
    }
    g->setpixel(x-1, y-1, pix);
  }
}
