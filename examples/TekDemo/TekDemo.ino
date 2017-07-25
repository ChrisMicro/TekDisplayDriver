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


TEK tek;

void setup() {
    delay(3000);  // Wait for USB
    Serial.begin(115200);
    }

void loop() {

  // Draw some primitives on the screen for fun
  // Origin (0,0) is the left bottom corner, y| __x

  uint32_t elapsed = micros();
  
  tek.Tekcls();
  tek.Tekcolor(2);
  tek.Tekgraph(4);
  tek.Tekpoint(100, 100);
  tek.Tekpoint(200, 100);
  tek.Tekpoint(200, 200);
  tek.Tekpoint(100, 200);

  tek.Tekcolor(3);
  for (uint32_t i = 300; i < 500; i = i + 10) {
    tek.Tekline(i, 400, i, 600);
  }

  tek.Tekstyle(0);

  tek.Tekline(300, 300, 500, 500);
  tek.Tekstyle(1);
  tek.Tekline(600, 400, 200, 300);
  tek.Tekstyleb(2);
  tek.Tekcolor(7);
  tek.Tekplot(10, 700);
  tek.Tekplot(500, 30);
  tek.Tekstyle(3);
  tek.Tekline(400, 600, 100, 800);
  tek.Tekcolor(4);
  tek.Tekstyleb(4);
  tek.Tekplot(300, 330);

  tek.Tekalpha();

  tek.Tekfont(1);
  tek.Teklocate(700, 400);
  tek.Tekcolor(6);
  Serial.println("Hello World !!");

  tek.Tekfont(2);
  tek.Tekcolor(1);
  tek.Teklocate(700, 300);
  Serial.println("STM32duino !!");

  tek.Tekfont(0);
  tek.Tekcolor(2);
  tek.Teklocate(500, 200);
  Serial.println("THIS IS A TEST OF TEK4014 !!");

  tek.Tekcolor(1);
  tek.Tekstyle(0);
  tek.Tekbox(300, 200, 600, 600);

  tek.Tekcolor(2);
  tek.Tekstyle(0);
  tek.Tekdot(150, 150);

  uint32_t i;

  for (i = 0; i < 360; i++) {
    float q = i;
    q = 3.141592f * q / 180.0f;
    float r = cosf(q);
    q = sinf(q);
    q = q * 120.0f;
    q = q + 195.0f;
    r = r * 120.0f;
    r = r + 580.0f;
    tek.Tekdot((uint16_t) r, (uint16_t) q);
  }

  tek.Tekcolor(5);

  for (i = 0; i < 360; i++) {
    float q = i;
    q = 3.141592f * q / 180.0f;
    q = sinf(q);
    q = q * 150.0f;
    q = q + 195.0f;
    float r = i + 30.0f;
    tek.Tekdot((uint16_t) r, (uint16_t) q);
  }

  uint32_t a = 450;
  for (i = 1; i < 34; i++) {
    tek.Tekline(0, 450, 1000, a);
    a = a + 10;
  }
  
  tek.Tekalpha();
  tek.Teklocate(400, 100);

  elapsed = micros() - elapsed;
  Serial.print("Elapsed: ");
  Serial.print(elapsed);
  Serial.println(" micros");

  delay(5000);
}

void testSprite()
{
    uint32_t elapsed;
    tek.Tekcls();
  tek.Tekcolor(2);
//  Tekcolor(green);
  char* sprite;
  // Type 26 frigate
  sprite = "PAAAAAAAAAAAAAADDBBBDDBBBHHBBBDDBBBHHBBHH";
  elapsed = micros();
  for(int i=100; i<600; i=i+20){
    for(int a=100; a<600; a=a+20){
      tek.Teklocate(i, a);
      tek.Teksprite(sprite);
    }
  }
  elapsed = micros() - elapsed;
  tek.Tekalpha();
    tek.Tekfont(0);//  Tekfont(normal);
  tek.Teklocate(100, 50);
  Serial.print("Elapsed: ");
  Serial.print(elapsed);
  Serial.println(" micros");
}


