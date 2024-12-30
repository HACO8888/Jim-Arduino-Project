#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTCLib.h>
#include <Adafruit_I2CDevice.h>
#include <SPI.h>

int CDSPin = 0;
int CDSVal = 0;
int LEDPin = 5;
int SETBtn = 8;
int DOWNBtn = 9;
int UPBtn = 10;
int Buz = 2;

int time = 0;
int timeSet = 0;

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  lcd.backlight();

  pinMode(Buz, OUTPUT);
  pinMode(LEDPin, OUTPUT);
  pinMode(SETBtn, INPUT);
  pinMode(DOWNBtn, INPUT);
  pinMode(UPBtn, INPUT);

  if (!rtc.begin())
  {
    Serial.println("无法找到 DS3231 RTC 模块");
    while (1)
      ;
  }

  // 如果 RTC 电源丢失，则设置时间
  if (rtc.lostPower())
  {
    Serial.println("RTC 电源故障，正在设置时间！");
    // 设置时间为编译时的时间
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop()
{

  if (digitalRead(UPBtn) == LOW)
  {
    time += 1;
    delay(200);
  }

  if (digitalRead(DOWNBtn) == LOW)
  {
    if (time > 0)
    {
      time -= 1;
      delay(200);
    }
  }

  DateTime now = rtc.now();
  CDSVal = analogRead(CDSPin);
  // Serial.println(CDSVal);
  analogWrite(LEDPin, (CDSVal - 400 - 10) / 4);
  lcd.setCursor(0, 0);
  lcd.print(now.month());
  lcd.print("/");
  lcd.print(now.day());
  lcd.print(" ");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());
  lcd.print(":");
  lcd.print(now.second());
  lcd.print("   ");

  if (timeSet == 0)
  {
    lcd.setCursor(0, 1);
    lcd.print("Time:");
    lcd.print(time);
    lcd.print("m");
    lcd.print("   ");
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Time:");
    lcd.print(timeSet);
    lcd.print("s");
    lcd.print("   ");
  }

  if (digitalRead(SETBtn) == LOW)
  {
    if (timeSet == 0)
    {
      digitalWrite(Buz, HIGH);
      delay(500);
      digitalWrite(Buz, LOW);
      timeSet = time * 60;
    }
  }

  if (timeSet > 0)
  {
    timeSet -= 1;
    delay(1000);
    if (timeSet < 0)
    {
      digitalWrite(Buz, HIGH);
      delay(1000);
      digitalWrite(Buz, LOW);
      timeSet = 0;
    }
  }
}
