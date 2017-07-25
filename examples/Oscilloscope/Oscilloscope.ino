/************************************************************************

  Tek4010 simple oscilloscope example

  The oscilloscope has a auto trigger function to achieve a stable
  visual impression when a repeating signal like a sine wave is applied.

  July 2017, ChrisMicro

************************************************************************/

#include "Arduino.h"
#include "Tek.h"

TEK tek;

#define HORIZONTAL_RESOLUTION 1024
#define VERTICAL_RESOLUTION    760
#define SIGNAL_LENGTH          300

#define SCALEFACTOR_X (HORIZONTAL_RESOLUTION/SIGNAL_LENGTH)

#define POSITION_OFFSET_Y      20


uint16_t oldSignal[SIGNAL_LENGTH];
uint16_t adcBuffer[SIGNAL_LENGTH];

#define SAMPLING_TIME_US     5
#define ANALOG_SIGNAL_INPUT A0

void setup()
{
  delay(3000);  // Wait for USB
  Serial.begin(115200);

  tek.Tekcls();
  tek.Tekcolor(2);

  tek.Teklocate(400, VERTICAL_RESOLUTION);
  Serial.println("Tek Oscilloscope");
}

void waitForAutoTrigger()
{

  uint32_t triggerLevel = 512;
  uint32_t hysteresis   =  10;
  uint32_t timeOut_ms   = 100;

  uint32_t timeOutLimit = millis() + timeOut_ms;
  uint32_t timeOutFlag = false;

  uint32_t adcValue = 0;

  adcValue = analogRead( ANALOG_SIGNAL_INPUT );

  // wait for low level
  while ( ( adcValue > triggerLevel - hysteresis ) && !timeOutFlag )
  {
    adcValue = analogRead( ANALOG_SIGNAL_INPUT );

    if ( millis() > timeOutLimit ) timeOutFlag = 1 ;
  }

  if ( !timeOutFlag )
  {
    // wait for high level
    while ( ( adcValue < triggerLevel + hysteresis ) && ( millis() < timeOutLimit ) )
    {
      adcValue = analogRead(ANALOG_SIGNAL_INPUT);
    }
  }

}

void showSignal()
{
  int n;

  int oldx;
  int oldy;
  int y;

  for (n = 1; n < SIGNAL_LENGTH; n++)
  {
    //y = ( (int32_t)adcBuffer[n] * VERTICAL_RESOLUTION / 1024 ) + POSITION_OFFSET_Y;
    y = ( adcBuffer[n] * 3 ) + POSITION_OFFSET_Y;
    if (n == 1)
    {
      oldx = n;
      oldy = y;
    }

    if (n < SIGNAL_LENGTH - 1)
    {
      // delete old line element
      // [0 = White, 1 = Red, 2 = Green, 3 = Yellow, 4 = Blue, 5 = Magenta, 6 = Cyan, 7 = Böack]
      tek.Tekcolor(0); // back ground color
      tek.Tekline((n - 1)*SCALEFACTOR_X , oldSignal[n - 1], n*SCALEFACTOR_X, oldSignal[n]);

      // draw new line element
      tek.Tekcolor(4); // foreground color
      tek.Tekline(oldx*SCALEFACTOR_X,               oldy, n*SCALEFACTOR_X,            y);
    }

    oldSignal[n - 1] = oldy;
    oldx = n;
    oldy = y;
  }
}

void loop(void)
{
  int n;
  uint32_t nextTime = 0;

  waitForAutoTrigger();

  // record signal
  for (n = 1; n < SIGNAL_LENGTH; n++)
  {
    adcBuffer[n] = analogRead( ANALOG_SIGNAL_INPUT );

    // wait for next sample
    while (micros() < nextTime);
    nextTime = micros() + SAMPLING_TIME_US;
  }

  showSignal();
}



