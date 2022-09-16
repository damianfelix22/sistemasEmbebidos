#include "DHT.h"
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#define DHTTYPE DHT11   

const int DHTPin = 4;     // what digital pin we're connected to
DHT dht(DHTPin, DHTTYPE);
void setup() {
   Serial.begin(115200);
  // Serial.println("DHTxx test!");
  
   dht.begin();
}
void loop() {
   // Wait a few seconds between measurements.
   delay(2000);
   // Reading temperature or humidity takes about 250 milliseconds!
   float h = dht.readHumidity();
   float t = dht.readTemperature();
   
   Serial.print("Humidity: ");
   Serial.print(h);
   Serial.print(" %\t");
   Serial.print("Temperature: ");
   Serial.print(t);
   Serial.println(" *C ");
}