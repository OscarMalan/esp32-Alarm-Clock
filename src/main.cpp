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
    delay(100);
    }
    else if(digitalRead(BUTTON_C) == LOW){
      if (New_Day <= 1){New_Day = 31;}
      else{New_Day--;}
    delay(100);
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
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
  delay(100);
    }
    else if(digitalRead(BUTTON_C) == LOW){
      if (New_Month <= 1){New_Month = 12;}
      else{New_Month--;}
    delay(100);
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
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
      if (New_Year >= 2039){New_Year = 2023;}
      else{New_Year++;}
  delay(100);
    }
    else if(digitalRead(BUTTON_C) == LOW){
      if (New_Year <= 2023){New_Year = 2039;}
      else{New_Year--;}
    delay(100);
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
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
    else if(digitalRead(BUTTON_C) == LOW){
      if (New_Hour <= 0){New_Hour = 23;}
      else{New_Hour--;}
    delay(100);
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
    else if(digitalRead(BUTTON_C) == LOW){
      if (New_Minute <= 0){New_Minute = 59;}
      else{New_Minute--;}
    delay(100);
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

void Set_Alarm(){
  Alarm = 1;
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Set Alarm");
  display.display();
  delay(1000);
  while(Done == false){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Alarm?");
    display.setCursor(0, 24);
    display.print(Alarm);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (Alarm >= 4){Alarm = 1;}
      else{Alarm++;}
    delay(100);
    }
    else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm <= 1){Alarm = 4;}
      else{Alarm--;}
    delay(100);
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
  }
  Done = false;
  display.clearDisplay();
  delay(1000);
  switch (Alarm)
  {
  case 1:
    while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al1 Hour");
      display.setCursor(0, 24);
      display.print(Alarm1[0]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm1[0] >= 23){Alarm1[0] = 0;}
        else{Alarm1[0]++;}
      delay(100);
      }
      else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm1[0] <= 0){Alarm1[0] = 23;}
      else{Alarm1[0]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al1 Minute");
      display.setCursor(0, 24);
      display.print(Alarm1[1]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm1[1] >= 59){Alarm1[1] = 0;}
        else{Alarm1[1]++;}
      delay(100);
      }
        else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm1[1] <= 0){Alarm1[1] = 59;}
      else{Alarm1[1]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
    }
    Done = false;
    delay(1000);
    break;
  
  case 2:
    while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al2 Hour");
      display.setCursor(0, 24);
      display.print(Alarm2[0]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm2[0] >= 23){Alarm2[0] = 0;}
        else{Alarm2[0]++;}
      delay(100);
      }
        else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm2[0] <= 0){Alarm2[0] = 23;}
      else{Alarm2[0]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al2 Minute");
      display.setCursor(0, 24);
      display.print(Alarm2[1]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm2[1] >= 59){Alarm2[1] = 0;}
        else{Alarm2[1]++;}
      delay(100);
      }
        else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm2[1] <= 0){Alarm2[1] = 59;}
      else{Alarm2[1]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
    }
    Done = false;
    delay(1000);
    break;
  case 3:
   while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al3 Hour");
      display.setCursor(0, 24);
      display.print(Alarm3[0]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm3[0] >= 23){Alarm3[0] = 0;}
        else{Alarm3[0]++;}
      delay(100);
      }
        else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm3[0] <= 0){Alarm3[0] = 23;}
      else{Alarm3[0]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al3 Minute");
      display.setCursor(0, 24);
      display.print(Alarm3[1]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm3[1] >= 59){Alarm3[1] = 0;}
        else{Alarm3[1]++;}
      delay(100);
      }
        else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm3[1] <= 0){Alarm3[1] = 59;}
      else{Alarm3[1]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
    }
    Done = false;
    delay(1000);
    break;
  case 4:
   while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al4 Hour");
      display.setCursor(0, 24);
      display.print(Alarm4[0]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm4[0] >= 23){Alarm4[0] = 0;}
        else{Alarm4[0]++;}
      delay(100);
      }
        else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm4[0] <= 0){Alarm4[0] = 23;}
      else{Alarm4[0]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
    }
    Done = false;
    delay(1000);
    while (Done == false)
    {
      display.clearDisplay();
      display.setCursor(0, 0);
      display.setTextSize(2);
      display.print("Al4 Minute");
      display.setCursor(0, 24);
      display.print(Alarm4[1]);
      display.display();
      if(digitalRead(BUTTON_B) == LOW){
        if (Alarm4[1] >= 59){Alarm4[1] = 0;}
        else{Alarm4[1]++;}
      delay(100);
      }
        else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm4[1] <= 0){Alarm4[1] = 59;}
      else{Alarm4[1]--;}
      delay(100);
    }
      else if (digitalRead(BUTTON_A) == LOW)
      {
        Done = true;
      }
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
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("Alarm?");
    display.setCursor(0, 24);
    display.print(Alarm);
    display.display();
    if(digitalRead(BUTTON_B) == LOW){
      if (Alarm >= 4){Alarm = 1;}
      else{Alarm++;}
    delay(100);
    }
    else if(digitalRead(BUTTON_C) == LOW){
      if (Alarm <= 1){Alarm = 4;}
      else{Alarm--;}
    delay(100);
    }
    else if (digitalRead(BUTTON_A) == LOW)
    {
      Done = true;
    }
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