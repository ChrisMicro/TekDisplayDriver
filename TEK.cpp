// A simple TEK4010/4014 Graphics Vector terminal - DEMO
// You need ie. TeraTerm or Xterm switched into TEK4010/14 Emulation
// The current vector's addressing is 1024x1024 (10bit)
//
// Loosely inspired by
// http://www.ne.jp/asahi/shared/o-family/ElecRoom/AVRMCOM/TEK4010/TEK4010gdisp.html
// and other related information found on the web
//
// Provided as-is, no warranties of any kind are provided :)
// by Pito 7/2017

#include "Arduino.h"
#include "TEK.h"

// Clear Tek screen
void TEK::Tekcls() {
  Serial.write(0x1B);
  Serial.write(0x0c);
//Serial.write(0x0d);Serial.write(0x0a);
}

// Select a color (0-7)
// [0 = White, 1 = Red, 2 = Green, 3 = Yellow, 4 = Blue, 5 = Magenta, 6 = Cyan, 7 = Böack]
void TEK::Tekcolor(uint8_t color) {
  Serial.write(0x1B);
  Serial.write(0x5b);
  Serial.write(0x33);
  Serial.write(0x30 + color);
  Serial.write(0x6d);
}

// Switch to graphical mode with a line style (0-4)
void TEK::Tekgraph(uint8_t style) {
  Serial.write(0x1D);
  Serial.write(0x1B);
  Serial.write(style | 0x60);
}

// Select a font size (0-3) for printing alphanumeric strings
// The actual font type has to be set in the Emulator
void TEK::Tekfont(uint8_t fontsize) {
  Serial.write(0x1B);
  Serial.write(0x38 + fontsize);
}

// Normal style lines (0-4)
void TEK::Tekstyle(uint8_t style) {
  Serial.write(0x1B);
  Serial.write(0x60 + style);
}

// Bold style lines (??)
void TEK::Tekstyleb(uint8_t style) {
  Serial.write(0x1B);
  Serial.write(0x68 + style);
}

// Switch to alphanumeric mode
void TEK::Tekalpha() {
  Serial.write(0x1f);
}

// Draw a point as a small cross (??)
void TEK::Tekpoint(uint16_t x, uint16_t y) {
  Serial.write(0x1C);  // FS
  Serial.write(0x20 + ((y >> 5) & 0x1F));
  Serial.write(0x60 + ((y) & 0x1F));
  Serial.write(0x20 + ((x >> 5) & 0x1F));
  Serial.write(0x40 + ((x) & 0x1F));
}

// Draw a single dot
void TEK::Tekdot(uint16_t x, uint16_t y) {
  Serial.write(0x1D);  // GS
  Serial.write(0x20 + ((y >> 5) & 0x1F));
  Serial.write(0x60 + ((y) & 0x1F));
  Serial.write(0x20 + ((x >> 5) & 0x1F));
  Serial.write(0x40 + ((x) & 0x1F));
  Serial.write(0x40 + ((x) & 0x1F));
}

// Draw a line from (x1, y1) to (x2, y2)
void TEK::Tekline(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  Serial.write(0x1D);  // GS
  Serial.write(0x20 + ((y1 >> 5) & 0x1F));
  Serial.write(0x60 + ((y1) & 0x1F));
  Serial.write(0x20 + ((x1 >> 5) & 0x1F));
  Serial.write(0x40 + ((x1) & 0x1F));
  Serial.write(0x20 + ((y2 >> 5) & 0x1F));
  Serial.write(0x60 + ((y2) & 0x1F));
  Serial.write(0x20 + ((x2 >> 5) & 0x1F));
  Serial.write(0x40 + ((x2) & 0x1F));
}

// Continue with drawing a line to (x1, y1)
void TEK::Tekplot(uint16_t x1, uint16_t y1) {
  Serial.write(0x20 + ((y1 >> 5) & 0x1F));
  Serial.write(0x60 + ((y1) & 0x1F));
  Serial.write(0x20 + ((x1 >> 5) & 0x1F));
  Serial.write(0x40 + ((x1) & 0x1F));
}

// Locate a point where to print a string
void TEK::Teklocate(uint16_t x1, uint16_t y1) {
  Serial.write(0x1D);  // GS
  Serial.write(0x20 + ((y1 >> 5) & 0x1F));
  Serial.write(0x60 + ((y1) & 0x1F));
  Serial.write(0x20 + ((x1 >> 5) & 0x1F));
  Serial.write(0x40 + ((x1) & 0x1F));
  Tekalpha();
}

// Draw a box with left bottom corner at (bx, by) and top right corner at (tx, ty)
void TEK::Tekbox(uint16_t bx, uint16_t by, uint16_t tx, uint16_t ty) {
  Tekline(bx, by, tx, by);
  Tekplot(tx, ty);
  Tekplot(bx, ty);
  Tekplot(bx, by);
}

// Draw small sprites
void TEK::Teksprite(char* sprite) {
  Serial.write(0x1E);
  Serial.print(sprite); 
}

// Go to the Graphics-IN mode
void TEK::Tekgin() {
  Serial.write(0x1B);
  Serial.write(0x1A);
}
