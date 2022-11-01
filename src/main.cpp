#include <Arduino.h>
#include <PubSubClient.h>

#include <WiFi.h>
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

WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);





const char* ssid     = "SisEmbebidos22";
const char* password = "sisembebidos2022";

char *server = "192.168.0.100";
int port = 1883;

int var = 0;
int ledval = 0;
int fotoval = 0;
char temp[80];
char hum[80];
String resultS = "";

void wifiInit() {
    Serial.print("Conectándose a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
        delay(500);  
    }
    Serial.println("");
    Serial.println("Conectado a WiFi");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
  }

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("] ");

  char payload_string[length + 1];
  
  int resultI;

  memcpy(payload_string, payload, length);
  payload_string[length] = '\0';
  resultI = atoi(payload_string);
  
  var = resultI;

  resultS = "";
  
  for (int i=0;i<length;i++) {
    resultS= resultS + (char)payload[i];
  }
  Serial.println();
}






void reconnect() {
  while (!mqttClient.connected()) {
    Serial.println("Intentando conectarse MQTT...");

    if (mqttClient.connect("esp32")) {
      Serial.println("Conectado");
      
    } else {
      Serial.print("Fallo, rc=");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}




void setup() {
  Serial.begin(9600);
  Wire.begin ();
  delay(250);
  display.begin(i2c_Address, true);
  dht.begin();
  wifiInit();
  mqttClient.setServer(server, port);
  mqttClient.setCallback(callback);

}  

void loop() {


  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();

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

  sprintf(temp, "Temp: %f", t);
  sprintf(hum, "Hum: %f", h);

  mqttClient.publish("temperatura",temp);
  mqttClient.publish("humedad",hum);
  delay(1000);
}  
