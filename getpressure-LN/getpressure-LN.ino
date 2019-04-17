#include <Wire.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "config.h"

Adafruit_MPL115A2 mpl115a2;

// set up the 'pressure'feed
AdafruitIO_Feed *pressure = io.feed("pressure");

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Hello!");
  
  Serial.println("Getting barometric pressure ...");
  mpl115a2.begin();
}

void loop(void) 
{
  float pressureKPA = 0, temperatureC = 0;    

  pressureKPA = mpl115a2.getPressure();  
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.println(" kPa");
  
  
  // save pressure to Adafruit IO
  pressure->save(mpl115a2.getPressure());
  
  temperatureC = mpl115a2.getTemperature();  
  Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C");
  
  delay(1000);
}
