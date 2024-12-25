#include <Arduino.h>

int CDSPin = 0;
int CDSVal = 0;
int LEDPin = 5;


void setup()
{
  Serial.begin(9600);

  pinMode(LEDPin, OUTPUT);
}

void loop()
{
  CDSVal = analogRead(CDSPin);
  Serial.println(CDSVal);
  analogWrite(LEDPin, (CDSVal - 400 - 10) / 4);
}
