#include <Arduino.h>
#include <PubSubClient.h> 
#include <WiFi.h>
#include <Wire.h> 

WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);

const char* ssid     = "FAST";
const char* password = "Genaro1972";

char *server = "192.168.0.187";
int port = 1883;

int ledpin= 4;

int var = 0;
int ledval = 0;
String resultS = "";

int valorLDR = 0;
int pinLDR = 4;

int Rojo = 23;
int Verde = 22;
int Azul = 21;
int pinLeDsensor = 5; 

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

      mqttClient.subscribe("color");
      
    } else {
      Serial.print("Fallo, rc=");
      Serial.println(mqttClient.state());
      delay(5000);
    }
  }
}

void setup()
{
  pinMode(Rojo,OUTPUT);
  pinMode(Verde,OUTPUT);
  pinMode(Azul,OUTPUT);

  pinMode(pinLeDsensor,OUTPUT);
  
  Serial.begin(9600);
  wifiInit();
  mqttClient.setServer(server, port);
  mqttClient.setCallback(callback);
}

void loop()
{
    valorLDR = analogRead(pinLDR);
    Serial.println(valorLDR);

    if(valorLDR >= 400)
    {
        digitalWrite(pinLeDsensor, LOW);
    }
    else
    {

        digitalWrite(pinLeDsensor, HIGH);
    }

    if (!mqttClient.connected()) {
      reconnect();
    }
    mqttClient.loop();

    int longitud = resultS.length();
    String colores = resultS.substring(4, longitud-1);
    Serial.println(colores); 

    int coma1 = colores.indexOf(",");
    int coma2 = colores.substring(coma1+1, colores.length()).indexOf(",") + coma1 + 1;
     
    
  

    
    String rojo_codigo = colores.substring(0, coma1);
    Serial.println(rojo_codigo);
    delay(500);

    String verde_codigo = colores.substring(coma1+1, coma2);
    Serial.println(verde_codigo);
    delay(500);

    String azul_codigo = colores.substring(coma2+1, coma2+5);
    Serial.println(azul_codigo);
    delay(500);

    int rojo = 0;
    int verde = 0;
    int azul = 0;

    rojo = rojo_codigo.toInt();
    verde = verde_codigo.toInt();
    azul = azul_codigo.toInt();
    






    analogWrite(Rojo, rojo);
    analogWrite(Verde, verde);
    analogWrite(Azul, azul);

    delay(200);
}
