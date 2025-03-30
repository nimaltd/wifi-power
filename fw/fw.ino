
#include <Arduino.h>
#include "Adafruit_NeoPixel.h"
#include "config.h"
#include "mp4245.h"

Adafruit_NeoPixel led(CONFIG_LED_MAX, CONFIG_LED_PIN, NEO_GRB + NEO_KHZ800);
mp4245 dcdc(CONFIG_MP_SDA_PIN, CONFIG_MP_SCL_PIN, CONFIG_MP_EN_PIN);

/*************************************************************************************************/
void setup()
{
  Serial.begin(115200);
  led.begin();
  led.clear();
  delay(1000);
  dcdc.begin();
  dcdc.enable(true); 
}

/*************************************************************************************************/
void loop()
{
  delay(500);
  dcdc.cfg_set_vout(1000);
  delay(500);
  dcdc.cfg_set_vout(2000);
  delay(500);
  dcdc.cfg_set_vout(3000);
  delay(500);
  dcdc.cfg_set_vout(4000);
  delay(500);
  dcdc.cfg_set_vout(5000);

 
}