/*
 * Mr. Tank Bot
 * 
 * By: Inderpreet Singh
 * 
 * Notes:
 * ESP8266 GPIO used:
 * 2 and 0 For SCL and SDA respectively. Wire.begin(0,2);
 * 
 * For ESP8266MOD : Select the NodeMCU 0.9
 * For ESP-12N    : Select NodeMCU 1.0
 */

/* 
 *  Definitions and Constants Sections
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN  //4

// Direction and speed Pin. One Direction Pin for Forward and Backward and One Common Speed Pin for the lack of available Pins
#define M1 4
#define M2 5
#define SPEED 15

/* 
 *  Global Variables and types
 */
Adafruit_SSD1306 display(OLED_RESET);
// 128x64
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
enum action{
  HLT=0,
  FWD=1,
  BCK=2,
  RIT=3,
  LFT=4
  };

/* 
 *  Motor Speed Control Function
 *  Takes arguments:
 *    dir: Direction which can be HLT, FWD, BCK, RIT, LFT only
 *    secs: duration of travel in milliseconds
 *    vroom: PWM speed control with value ranging from 0 to 1023
 */
void control(enum action dir, int secs, int vroom){
  switch(dir){
    case FWD:
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
//      digitalWrite(SPEED, HIGH);
      analogWrite(SPEED, vroom);
      break;
    case BCK:
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
//      digitalWrite(SPEED, HIGH);
      analogWrite(SPEED, vroom);
      break;
    case RIT:
      digitalWrite(M1, LOW);
      digitalWrite(M2, HIGH);
//      digitalWrite(SPEED, HIGH);
      analogWrite(SPEED, vroom);
      break;
    case LFT:
      digitalWrite(M1, HIGH);
      digitalWrite(M2, LOW);
//      digitalWrite(SPEED, HIGH);
      analogWrite(SPEED, vroom);
      break;
    case HLT:
    default:
//      digitalWrite(SPEED, LOW);
      analogWrite(SPEED, 0);
      break;
  }
  delay(secs);
//  digitalWrite(SPEED, LOW);
  analogWrite(SPEED, 0);  
}

/* 
 *  *******************************************
 *  Setup Function
 *  *******************************************
 */
void setup() {
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(SPEED, OUTPUT);
  control(HLT, 10, 0); // Initially Halted
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Mr. Tank Initialized");
  display.setCursor(0,9);
  display.println("Motors OFF");
  display.display();
}

/* 
 *  **********************************************
 *  Main Loop Function
 *  **********************************************
 */
void loop() {
  // ************* Forward ******************
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Mr. Tank");
  display.setCursor(0,9);
  display.println("Motors FWD  ");
  display.display();
  control(FWD, 3000, 512);

  
  // ************* Right Turn ******************
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Mr. Tank");
  display.setCursor(0,9);
  display.println("Motors RIT  ");
  display.display();
  control(RIT, 2000, 512);

  // ************* Left Turn  ******************
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Mr. Tank");
  display.setCursor(0,9);
  display.println("Motors LFT");
  display.display();
  control(LFT, 2000, 512);

  // ************* Forward ******************
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Mr. Tank");
  display.setCursor(0,9);
  display.println("Going Backwards  ");
  display.display();
  control(BCK, 3000, 512);

  // ************* Forward ******************
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Mr. Tank");
  display.setCursor(0,9);
  display.println("Going Nowhere  ");
  display.display();
  control(HLT, 3000, 512);
}
