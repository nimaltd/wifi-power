
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include "config.h"
#include "mp4245.h"

Adafruit_NeoPixel led(CONFIG_LED_MAX, CONFIG_LED_PIN, NEO_GRB + NEO_KHZ800);

/*************************************************************************************************/
void setup()
{
  Serial.begin(115200);
  led.begin();
  led.clear();
}

/*************************************************************************************************/
void loop()
{
 
}