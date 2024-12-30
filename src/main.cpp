#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int CDSPin = 0;
int CDSVal = 0;
int LEDPin = 5;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(LEDPin, OUTPUT);
}

void loop()
{
  CDSVal = analogRead(CDSPin);
  Serial.println(CDSVal);
  analogWrite(LEDPin, (CDSVal - 400 - 10) / 4);
  lcd.setCursor(0, 0);
  lcd.print("Time Now:");
  lcd.setCursor(1, 0);
  lcd.print("");
}
