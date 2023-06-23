#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define BUTTON_A 16
#define BUTTON_B 15
#define BUTTON_C 14
#define WIRE Wire

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

int New_Day = 1;
int New_Month = 1;
int New_Year = 2023;
int New_Hour = 0;
int New_Minute = 1;
bool Done = false;
char Week_Day[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
int Alarm1[2] = {6, 0};
int Alarm2[2] = {6, 0};
int Alarm3[2] = {6, 0};
int Alarm4[2] = {6, 0};
bool Alarm1ON = true;
bool Alarm2ON = true;
bool Alarm3ON = true;
bool Alarm4ON = true;

void Set_Time() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Day?");
  display.display();
  delay(1000);
  while(Done == false){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Day?");
    display.setCursor(0, 24);
    display.print(New_Day);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (New_Day >= 31){New_Day = 1;}
      else{New_Day++;}
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
  delay(100);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Month?");
    display.setCursor(0, 24);
    display.print(New_Month);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (New_Month >= 12){New_Month = 1;}
      else{New_Month++;}
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
  delay(100);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Year?");
    display.setCursor(0, 24);
    display.print(New_Year);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (New_Year >= 2199){New_Year = 2023;}
      else{New_Year++;}
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
  delay(100);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Year?");
    display.setCursor(0, 24);
    display.print(New_Year);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (New_Year >= 2199){New_Year = 2023;}
      else{New_Year++;}
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
  delay(100);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Hour?");
    display.setCursor(0, 24);
    display.print(New_Hour);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (New_Hour >= 23){New_Hour = 0;}
      else{New_Hour++;}
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
  delay(100);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Minute?");
    display.setCursor(0, 24);
    display.print(New_Minute);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (New_Minute >= 59){New_Minute = 0;}
      else{New_Minute++;}
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
  delay(100);
  }
  Done = false;
  rtc.adjust(DateTime(New_Year, New_Month, New_Day, New_Hour, New_Minute, 0));
}

void Set_Alarm(int x){
  display.println(x);
}

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  if (! rtc.begin()) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("RTC FAILED");
    display.display();
  }

  rtc.adjust(DateTime(__DATE__, __TIME__));
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
}

void loop() {
  DateTime now = rtc.now();
  
  display.clearDisplay();
  delay(1000);
  display.setCursor(0, 0);
  display.setTextSize(2);

  // Main Display
  display.print(Week_Day[now.dayOfTheWeek()]); display.setCursor(42, 0);
  display.print(now.day()); display.setTextSize(1); display.print("/"); display.setTextSize(2); display.print(now.month()); display.setTextSize(1); display.print("/"); display.setTextSize(2); display.println(now.year()-2000);
  display.setCursor(0, 24);
  display.print(now.hour()); display.print(":"); display.print(now.minute()); display.print(":"); display.print(now.second()); display.setTextSize(1); display.print(" "); display.print(int(rtc.getTemperature())); display.print(" C");
  
  // Alarm ON/OFF display
  display.setTextSize(1);
  if (Alarm1ON == true) {
    display.fillRect(12, 44, 12, 8, WHITE);
  }
  if (Alarm2ON == true) {
    display.fillRect(42, 44, 12, 8, WHITE);
  }
  if (Alarm3ON == true) {
    display.fillRect(72, 44, 12, 8, WHITE);
  }
  if (Alarm4ON == true) {
    display.fillRect(102, 44, 12, 8, WHITE);
  }
  // Alarm Number display
  display.setCursor(10, 54);
  display.print("AL1");
  display.setCursor(40, 54);
  display.print("AL2");
  display.setCursor(70, 54);
  display.print("AL3");
  display.setCursor(100, 54);
  display.print("AL4");

  if(digitalRead(BUTTON_A) == LOW){
    Set_Time();
  }
  if(digitalRead(BUTTON_B) == LOW){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("BUTTON B");
  }

  display.display();
}