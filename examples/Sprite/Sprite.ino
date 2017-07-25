/*
  Tek sprite example

  Provided as-is, no warranties of any kind are provided :)
  by ChrisMicro 2017
  
*/

#include "Arduino.h"
#include "Tek.h"

TEK tek;

void setup() 
{
  delay(3000);
  Serial.begin(115200);

}

int Position_x = 0;

void loop() {

  uint32_t i;

  tek.Tekcls();

  char* sprite;
  sprite = "PAAAAAAAAAAAAAADDBBBDDBBBHHBBBDDBBBHHBBHH"; // sprite from Pito
  tek.Tekgraph(solid);

  int y=500;

  int offset=200*sin(2*PI*Position_x/1000*3);

  // ship1
  tek.Tekcolor(blue);
  tek.Teklocate(Position_x, y+offset);
  tek.Teksprite(sprite);

  // ship2
  tek.Tekcolor(blue);
  tek.Teklocate(1023-Position_x, y-offset);
  tek.Teksprite(sprite);
  
  Position_x +=2;
  if(Position_x>900)Position_x=0;

  delay(100);

}

