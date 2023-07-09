#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define BUTTON_A 16
#define BUTTON_B 15
#define BUTTON_C 14
#define Buzzer 17

#define WIRE Wire

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

int New_Day = 1;
int New_Month = 1;
int New_Year = 2023;
int New_Hour = 0;
int New_Minute = 1;
int Count = 0;
bool Done = false;
char Week_Day[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
int Alarm = 1;
int Alarm1[2] = {6, 0};
int Alarm2[2] = {6, 0};
int Alarm3[2] = {6, 0};
int Alarm4[2] = {6, 0};
bool Alarm1ON = false;
bool Alarm2ON = false;
bool Alarm3ON = false;
bool Alarm4ON = false;


void Variable_Value_Control(int &Changed_Varible, int Max_Value, int Min_Value, /* Handles text output on display, can't just parse the string as a paramenter due to how C++ handles strings */ int Text){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    // The best way I could figure out on how to handle this text, still more effiecent by 10 lines
    switch (Text)
    {
    case 0:
      display.print("Day");
      break;
    case 1:
      display.print("Month");
      break;
    case 2:
      display.print("Year");
      break;
    case 3:
      display.print("Hour");
      break;
    case 4:
      display.print("Minute");
      break;
    case 5:
      display.print("Alarm");
      break;
    case 6:
      display.print("Al1 Hour");
      break;
    case 7:
      display.print("Al1 Minute");
      break;
    case 8:
      display.print("Al2 Hour");
      break;
    case 9:
      display.print("Al2 Minute");
      break;
    case 10:
      display.print("Al3 Hour");
      break;
    case 11:
      display.print("Al3 Minute");
      break;
    case 12:
      display.print("Al4 Hour");
      break;
    case 13:
      display.print("Al4 Minute");
      break;
    }
    display.setCursor(0, 24);
    display.print(Changed_Varible);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (Changed_Varible >= Max_Value){Changed_Varible = Min_Value; }
      // Count is used as a scaling, so that the longer the button is held down for, the larger the counting incremints
      else{if (Count >= 5) {Changed_Varible += 2;}
      else if (Count >= 10) {Changed_Varible += 5;}
      else if (Count >= 15) {Changed_Varible += 8;}
      else {Changed_Varible++;}
      }
      Count++;
    delay(100);
    }
    else if(digitalRead(BUTTON_C) == LOW){
      if (Changed_Varible <= Min_Value){Changed_Varible = Max_Value;}
      else{if (Count >= 5) {Changed_Varible -= 2;}
      else if (Count >= 10) {Changed_Varible -= 5;}
      else if (Count >= 15) {Changed_Varible -= 8;}
      else {Changed_Varible--;}
      }
      Count++;
    delay(100);
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
    else {Count = 0;}
}

void setup() {

  // Turns on display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Tests RTC is working, tells user if it is failing
  if (! rtc.begin()) {
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("RTC FAILED");
    display.display();
  }

  //====================================================================================================================================
  // Comment this out when final, otherwise will change time everytime power is lost
  rtc.adjust(DateTime(__DATE__, __TIME__));
  //====================================================================================================================================
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
}

void Set_Time() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Set Time");
  display.display();
  delay(1000);
  while(Done == false){
    Variable_Value_Control(New_Day, 31, 1, 0);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    Variable_Value_Control(New_Month, 12, 1, 1);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    Variable_Value_Control(New_Year, 2039, 2023, 2);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    Variable_Value_Control(New_Hour, 23, 0, 3);
  }
  delay(1000);
  Done = false;
  while(Done == false){
    Variable_Value_Control(New_Minute, 59, 0, 4);
  }
  Done = false;
  // Adjust the RTC time
  rtc.adjust(DateTime(New_Year, New_Month, New_Day, New_Hour, New_Minute, 0));
}

void Set_Alarm(){
  Alarm = 1;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Set Alarm");
  display.display();
  delay(1000);
  while(Done == false){
    Variable_Value_Control(Alarm, 4, 1, 5);
  }
  Done = false;
  display.clearDisplay();
  delay(1000);
  switch (Alarm)
  {
  case 1:
    while (Done == false)
    {
      Variable_Value_Control(Alarm1[0], 23, 0, 6);
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      Variable_Value_Control(Alarm1[1], 59, 0, 7);
    }
    Done = false;
    delay(1000);
    break;
  case 2:
    while (Done == false)
    {
      Variable_Value_Control(Alarm2[0], 23, 0, 8);
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      Variable_Value_Control(Alarm2[1], 59, 0, 9);
    }
    Done = false;
    delay(1000);
    break;
  case 3:
   while (Done == false)
    {
      Variable_Value_Control(Alarm3[0], 23, 0, 10);
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      Variable_Value_Control(Alarm3[1], 59, 0, 11);
    }
    Done = false;
    delay(1000);
    break;
  case 4:
   while (Done == false)
    {
      Variable_Value_Control(Alarm4[0], 23, 0, 12);
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      Variable_Value_Control(Alarm4[1], 59, 0, 13);
    }
    Done = false;
    delay(1000);
    break;

  default:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("ERROR");
    display.display();
    break;
  }
}

void Control_Alarm(){
  Alarm = 1;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("ON/OFF Al");
  display.display();
  delay(1000);
  while(Done == false){
    Variable_Value_Control(Alarm, 4, 1, 5);
  }
  Done = false;
  switch (Alarm)
  {
  case 1:
    if (Alarm1ON == false){Alarm1ON = true;}
    else if (Alarm1ON == true){Alarm1ON = false;}
    else {Alarm1ON = false;}
    break;
  case 2:
    if (Alarm2ON == false){Alarm2ON = true;}
    else if (Alarm2ON == true){Alarm2ON = false;}
    else {Alarm2ON = false;}
    break;
  case 3:
    if (Alarm3ON == false){Alarm3ON = true;}
    else if (Alarm3ON == true){Alarm3ON = false;}
    else {Alarm3ON = false;}
    break;
  case 4:
    if (Alarm4ON == false){Alarm4ON = true;}
    else if (Alarm4ON == true){Alarm4ON = false;}
    else {Alarm4ON = false;}
    break;
  
  default:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("ERROR");
    display.display();
    break;
  }
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
    Set_Alarm();
  }
  if(digitalRead(BUTTON_C) == LOW){
    Control_Alarm();
  }

  if(now.second() == 0){
    if(now.hour() == Alarm1[0]){
      if(now.minute() == Alarm1[1]){
        digitalWrite(Buzzer, HIGH);
        delay(10000);
        digitalWrite(Buzzer, LOW);
      }
    }
    if(now.hour() == Alarm2[0]){
      if(now.minute() == Alarm2[1]){
        digitalWrite(Buzzer, HIGH);
        delay(10000);
        digitalWrite(Buzzer, LOW);
      }
    }
    if(now.hour() == Alarm3[0]){
      if(now.minute() == Alarm3[1]){
        digitalWrite(Buzzer, HIGH);
        delay(10000);
        digitalWrite(Buzzer, LOW);
      }
    }
    if(now.hour() == Alarm4[0]){
      if(now.minute() == Alarm4[1]){
        digitalWrite(Buzzer, HIGH);
        delay(10000);
        digitalWrite(Buzzer, LOW);
      }
    }
  }

  display.display();
}