/*
 * TEK template
 */

#include "Arduino.h"
#include "Tek.h"

TEK tek;

void setup()
{
  delay(3000);  // Wait for USB
  Serial.begin(115200);
}

void loop() 
{
  tek.Tekcls();
  tek.Tekcolor(2);

  tek.Tekline(100, 100, 200, 400);

  tek.Teklocate(250, 400);
  Serial.println("Hello World !!");

  delay(5000);
}




