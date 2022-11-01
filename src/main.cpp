#include <Arduino.h>



#include <SPI.h>
#include <Adafruit_Sensor.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#include "DHT.h"

#define DHTPIN 5     // Digital pin connected to the DHT sensor

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);  


#define i2c_Address 0x3c 


#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1 

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin ();
  delay(250);
  display.begin(i2c_Address, true);
  dht.begin();

}  

void loop() {
  delay(100);
  float h = dht.readHumidity();
  
  float t = dht.readTemperature();


  
  
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE); 
  display.setCursor(0,0);
  display.print("humedad:");
  display.print(h);
  display.setCursor(0,40);
  display.setTextSize(1);
  display.print("temperatura:");
  display.print(t);
  display.display();
}  
