#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"

RTC_DS3231 rtc;

#define BUTTON_A 4
#define BUTTON_B 15
#define BUTTON_C 12
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
char Text_Display[14][11] = {"Day", "Month", "Year", "Hour", "Minute", "Alarm", "Al1 Hour", "Al1 Minute", "Al2 Hour", "Al2 Minute", "Al3 Hour", "Al3 Minute", "Al4 Hour", "Al4 Minute"};
char Week_Day[7][4] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
int Alarm = 1;

// By putting RTC_DATA_ATTR before defining a variable, it stores it in the RTC ram area on the ESP32, meaning if its modified it wont be forgotten when sleep mode is used
RTC_DATA_ATTR int Alarm1[2] = {6, 0};
RTC_DATA_ATTR int Alarm2[2] = {6, 0};
RTC_DATA_ATTR int Alarm3[2] = {6, 0};
RTC_DATA_ATTR int Alarm4[2] = {6, 0};
RTC_DATA_ATTR bool Alarm1ON = false;
RTC_DATA_ATTR bool Alarm2ON = false;
RTC_DATA_ATTR bool Alarm3ON = false;
RTC_DATA_ATTR bool Alarm4ON = false;


void Variable_Value_Control(int &Changed_Varible, int Max_Value, int Min_Value, /* Handles text output on display, can't just parse the string as a paramenter due to how C++ handles strings */ int Text){
  while (Done == false) {  
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    // Originally used switch case, but array is better
    display.print(Text_Display[Text]);
    display.setCursor(0, 24);
    display.print(Changed_Varible);
    display.display();
    if(digitalRead(BUTTON_B) == HIGH){
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
    else if(digitalRead(BUTTON_C) == HIGH){
      if (Changed_Varible <= Min_Value){Changed_Varible = Max_Value;}
      else{if (Count >= 5) {Changed_Varible -= 2;}
      else if (Count >= 10) {Changed_Varible -= 5;}
      else if (Count >= 15) {Changed_Varible -= 8;}
      else {Changed_Varible--;}
      }
      Count++;
    delay(100);
    }
    else if (digitalRead(BUTTON_A) == HIGH)
    {
      Done = true;
    }
    else {Count = 0;}
  }
  Done = false;
  delay(2000);
}


void Set_Time() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.print("Set Time");
  display.display();
  delay(2000);
  Variable_Value_Control(New_Day, 31, 1, 0);
  Variable_Value_Control(New_Month, 12, 1, 1);
  Variable_Value_Control(New_Year, 2039, 2023, 2);
  Variable_Value_Control(New_Hour, 23, 0, 3);
  Variable_Value_Control(New_Minute, 59, 0, 4);
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
  delay(2000);
  Variable_Value_Control(Alarm, 4, 1, 5);
  display.clearDisplay();
  switch (Alarm)
  {
  case 1:
    Variable_Value_Control(Alarm1[0], 23, 0, 6);
    Variable_Value_Control(Alarm1[1], 59, 0, 7);
    break;
  case 2:
    Variable_Value_Control(Alarm2[0], 23, 0, 8);
    Variable_Value_Control(Alarm2[1], 59, 0, 9);
    break;
  case 3:
    Variable_Value_Control(Alarm3[0], 23, 0, 10);
    Variable_Value_Control(Alarm3[1], 59, 0, 11);
    break;
  case 4:
    Variable_Value_Control(Alarm4[0], 23, 0, 12);
    Variable_Value_Control(Alarm4[1], 59, 0, 13);
    break;
  default:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("ERROR");
    display.display();
    delay(10000);
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
  delay(2000);
  Variable_Value_Control(Alarm, 4, 1, 5);
  switch (Alarm)
  {
  case 1:
    // ! infront of a bool variable makes it the opposite value, so then just assign using =
    Alarm1ON = !Alarm1ON;
    break;
  case 2:
    Alarm2ON = !Alarm2ON;
    break;
  case 3:
    Alarm3ON = !Alarm3ON;
    break;
  case 4:
    Alarm4ON = !Alarm4ON;
    break;
  default:
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("ERROR");
    display.display();
    break;
  }
  delay(1000);
}

void setup() {

  // Turns on display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);

  // Tests RTC is working, tells user if it is failing
  if (! rtc.begin()) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.print("RTC FAILED");
    display.display();
  }


  //====================================================================================================================================
  // Comment this out when final, otherwise will change time everytime power is lost and sleep mode won't work
  // rtc.adjust(DateTime(__DATE__, __TIME__));
  //====================================================================================================================================

  // Changed from 
  pinMode(BUTTON_A, INPUT_PULLDOWN);
  pinMode(BUTTON_B, INPUT_PULLDOWN);
  pinMode(BUTTON_C, INPUT_PULLDOWN);
  pinMode(Buzzer, OUTPUT);
  // Tells esp32 to wake up from deep sleep after 59.999999 seconds
  esp_sleep_enable_timer_wakeup(59999999);
  // Will wake up esp32 from sleep when any of the buttons are pressed
  esp_sleep_enable_ext1_wakeup(0x000000010,ESP_EXT1_WAKEUP_ANY_HIGH);
  // esp_sleep_enable_ext1_wakeup(0x000008000,ESP_EXT1_WAKEUP_ANY_HIGH);
  // esp_sleep_enable_ext1_wakeup(0x000001000,ESP_EXT1_WAKEUP_ANY_HIGH);
}

void loop() {
  DateTime now = rtc.now();
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);

  // Main Display
  display.print(Week_Day[now.dayOfTheWeek()]); display.setCursor(42, 0);
  display.print(now.day()); display.setTextSize(1); display.print("/"); display.setTextSize(2); display.print(now.month()); display.setTextSize(1); display.print("/"); display.setTextSize(2); display.println(now.year()-2000);
  display.setCursor(0, 24);
  display.print(now.hour()); display.print(":"); display.print(now.minute()); display.print("   ");display.print(int(rtc.getTemperature())); display.setTextSize(1); display.print("C");
  
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

  if(digitalRead(BUTTON_A) == HIGH){
    Set_Time();
  }
  if(digitalRead(BUTTON_B) == HIGH){
    Set_Alarm();
  }
  if(digitalRead(BUTTON_C) == HIGH){
    Control_Alarm();
  }
  else{
  // Send ESP32 into deep sleep
  esp_deep_sleep_start();
  }

}