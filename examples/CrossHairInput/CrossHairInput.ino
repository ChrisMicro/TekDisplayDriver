// A simple TEK4010/4014 Vector terminal DEMO
// You need TeraTerm or Xterm switched to TEK4010/14 Emulation
//
// Use fast Serial over USB for best experience
//
//  Shows MOUSE activity and returned X and Y coordinates
//  You must click to get new X and Y
//
// Provided as-is, no warranties of any kind are provided :)
// by Pito 7/2017

#include "Arduino.h"
#include "Tek.h"

TEK tek;

void setup()
{
  delay(3000);
  Serial.begin(115200);
}

void loop()
{
  uint32_t i = 0;
  char b0, b1, b2, b3, b4;
  uint16_t x = 0, y = 0, xo = 0, yo = 0;

  tek.Tekcls();
  tek.Tekcolor(cyan);

  while (1) {
    tek.Tekgin();
    if (Serial.available() > 0) b0 = Serial.read();
    if (Serial.available() > 0) b1 = Serial.read();
    if (Serial.available() > 0) b2 = Serial.read();
    if (Serial.available() > 0) b3 = Serial.read();
    if (Serial.available() > 0) b4 = Serial.read();
    x = 32 * (b1 - 32) + (b2 - 32);
    y = 32 * (b3 - 32) + (b4 - 32);
    tek.Tekalpha();
    tek.Tekfont(small);
    tek.Tekcolor(cyan);
    if ((x != xo) | (y != yo)) {
      Serial.print(b0, HEX);  // KeyCode
      Serial.print("   X=");
      Serial.print(x);
      Serial.print(" Y=");
      Serial.print(y);
      Serial.println();
      xo = x;
      yo = y;
      i++;
      delay(2000);
    }
    delay(100);
    if (i == 80) {
      tek.Tekcls();
      i = 0;
    }
  }
}
