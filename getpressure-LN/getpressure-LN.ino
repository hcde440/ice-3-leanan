#include <Wire.h>
#include <Adafruit_MPL115A2.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "config.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Adafruit_MPL115A2 mpl115a2;

// set up the 'pressure'feed
AdafruitIO_Feed *pressure = io.feed("pressure");

void setup() {
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initailize with the i2c addre 0x3C
  display.clearDisplay();                    //Clears any existing images or text
  display.setTextSize(1);                    //Set text size
  display.setTextColor(WHITE);               //Set text color to white
  display.setCursor(0,0);                    //Puts cursor on top left corner
  display.println("Starting up...");         //Test and write up
  display.display();                         //Displaying the display
  
  Serial.println("Getting barometric pressure ...");
  mpl115a2.begin();

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  io.run();  
  
  float pressureKPA = 0, temperatureC = 0;    

  pressureKPA = mpl115a2.getPressure();  
  Serial.print("Pressure (kPa): "); Serial.print(pressureKPA, 4); Serial.println(" kPa");
  
  
  // save pressure to Adafruit IO
  pressure->save(pressureKPA);
  
  temperatureC = mpl115a2.getTemperature();  
  Serial.print("Temp (*C): "); Serial.print(temperatureC, 1); Serial.println(" *C");
  
  delay(1000);

  display.clearDisplay(); //Clears any existing images or text
  display.setCursor(0,0); //Puts cursor on top left corner
    // prints pressure message on display
  display.print("Pressure: "); 
  display.print(pressureKPA, 3); 
  display.println(F(" kPa"));
  display.display(); //Displaying the display
  
}
