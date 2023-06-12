#include <Wire.h>
#include <SPI.h>
#include <string>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14
#define WIRE Wire

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &WIRE);

int Time_Year = 23;
int Time_Month = 1;
int Time_Day = 1;
int Time_Hour = 0;
int Time_Minute = 0;
int Time_Second = 0;
String Week_Day[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
int Alarm1[2] = {6, 0};
int Alarm2[2] = {6, 0};
int Alarm3[2] = {6, 0};
int Alarm4[2] = {6, 0};
bool Alarm1ON = true;
bool Alarm2ON = true;
bool Alarm3ON = true;
bool Alarm4ON = true;

void Set_Time() {

}

void Set_Alarm(int x){
  display.println(x);
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  display.clearDisplay();

  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.setTextSize(2);

}

void loop() {
  display.clearDisplay();
  delay(1000);
  display.setCursor(0, 0);
  display.setTextSize(2);

  // Loading Display
  display.print(Week_Day[1]); display.print(" ");
  display.print(Time_Day); display.print("-"); display.print(Time_Month); display.print("-"); display.println(Time_Year);
  display.setCursor(0, 24);
  display.print(Time_Hour); display.print(":"); display.print(Time_Minute); display.print(":"); display.println(Time_Second);
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

  Time_Second++;
  if (Time_Second == 60){
  Time_Second = 0;
  Time_Minute++;
  }
  if (Time_Minute == 60){
    Time_Minute = 0;
    Time_Hour++;
  }
  if (Time_Hour == 24){
    Time_Hour = 0;
    Time_Day++;
  }
  // Handles Leap Year Feb
  if (Time_Year % 4 == 0 && Time_Month == 2){
    if (Time_Day == 30){
      Time_Day = 1;
      Time_Month++;
    }
  }
  else {
    switch (Time_Month)
    {
    case 1:
      if (Time_Day == 32){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 2:
      if (Time_Day == 29){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 3:
      if (Time_Day == 32){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 4:
      if (Time_Day == 31){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 5:
      if (Time_Day == 32){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 6:
      if (Time_Day == 31){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 7:
      if (Time_Day == 32){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 8:
      if (Time_Day == 32){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 9:
      if (Time_Day == 31){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 10:
      if (Time_Day == 32){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 11:
      if (Time_Day == 31){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    case 12:
      if (Time_Day == 32){
        Time_Day = 1;
        Time_Month++;
      }
      break;
    }
  }
  if (Time_Month == 13){
    Time_Month = 1;
    Time_Year++;
  }

  display.display();
}
