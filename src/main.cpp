#include <Arduino.h>

int valorLDR = 0;
int pinLDR = 4;

int Rojo = 23;
int Verde = 22;
int Azul = 21;
int pinLeDsensor = 5; 

void setup()
{
  pinMode(Rojo,OUTPUT);
  pinMode(Verde,OUTPUT);
  pinMode(Azul,OUTPUT);

  pinMode(pinLeDsensor,OUTPUT);
  
  Serial.begin(9600);
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
        
    analogWrite(Rojo, 0);
    analogWrite(Verde, 50);
    analogWrite(Azul, 250);

    delay(200);
}