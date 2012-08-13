// include the library code:
#include<stdlib.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "Timer.h"
#include "HT1632.h"

#define DATA 11
#define WR   12
#define CS   10

#define REDLITE 5
#define GREENLITE 6
#define BLUELITE 9

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4
#define FLASH 3
#define BRAKING 3

///////Brake Switch/////////////
int brakeV; 
int brakeOld;
int brakeVPin; 
boolean brakeOn = false;
boolean strobeOn = false;
boolean blinkOn = false;
///////Reed Switch//////////////
int reedPin = A1;  
int circleNum = 0;
float wheelDiameter = 25.2;
float wheelC = 3.14 * wheelDiameter;
float odometer = 0;
float miles = 0;
float kilometers = 0;
float speedometer = 0;
float MPH = 0;
float KPH = 0;
int reedTime = 0;
int reedTimeDelta = 0;
boolean reedOn = false;
boolean metric = true;
///////Turning Indicator Buttons////////
boolean rOn = false;
boolean lOn = false;
boolean rightIndicator = false;
boolean leftIndicator = false;
boolean stepUp = false;
int right;
int left;
int rightOld;
int leftOld;
int type;
const int turnRPin = A3;
const int turnLPin = A2;
const int turnRLED = A5;
const int turnLLED = A4;
///////Turning Indicator Matrix///////////
// use this line for single matrix
int numMatrices = 1;
int height = 16;
int width = numMatrices * 32;
int stepSize = 2;
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);

int state = 0;
int blinkTime = 1000;
Timer scrollTimer;
int scrollTime = 130;
Timer strobeTimer;
int strobeTime = 500;

///////LCD//////////////////////
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, A0, 8, 7, 4);
int LCDButton;



////////////////////////////////////////////////////////
////////////////////////////SETUP////////////////////////////
////////////////////////////////////////////////////////
void setup() {
  // set up the LCD's number of rows and columns:
  lcd.begin(16, 2);
  lcd.print("Speed Test");
  lcd.setCursor(0,1);
  lcd.print(" Distance Test");
  
  
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  blankScreen();
  
  scrollTimer.every(scrollTime, scroll);
  strobeTimer.every(strobeTime, strobe);
  
  reedTime = millis();
  
  pinMode(turnRPin, INPUT); 
  pinMode(turnRLED, OUTPUT);   
  pinMode(turnLPin, INPUT);
  pinMode(turnLLED, OUTPUT); 
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////LOOP////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop() {
  checkRightTurning();
  checkLeftTurning();
  checkBraking();
  checkReed();
  printLCD();
  scrollTimer.update();
  strobeTimer.update();
}


void printLCD(){
  //column, line
  lcd.setCursor(1, 0);      
  lcd.print(getSpeedString());
  lcd.setCursor(1, 1); 
  lcd.print(getDistanceString());
}

void setLEDShape(){
  if(brakeOn){
    return;
  }
  //right turning indicator is on, left off
  else if (rOn && lOn == false && stepUp){
    drawRight();
    rightIndicator = true;
    digitalWrite(turnRLED, HIGH);
  }
  //left turning indicator is on, right off
  else if (lOn && rOn == false && stepUp){
    drawLeft();
    leftIndicator = true;
    digitalWrite(turnLLED, HIGH);
  }
  //right is on
  else if (lOn && rOn == false && stepUp == false){
    //never going to happen
  }
  else if(rOn && lOn && strobeOn == false){
    rightIndicator = false;
    leftIndicator = false;
    strobeOn = true;
    rOn = false;
    lOn = false;
    digitalWrite(turnRLED, LOW);
    digitalWrite(turnLLED, LOW);
    drawStrobe();
  }
  else if(rOn && lOn && strobeOn){
    rightIndicator = false;
    leftIndicator = false;
    strobeOn = false;
    rOn = false;
    lOn = false;
    digitalWrite(turnRLED, LOW);
    digitalWrite(turnLLED, LOW);
    blankScreen();
  }
  
  //left and right turning indicators are off
  //turn screen off
  else if(rOn == false && lOn == false && strobeOn == false){
    //everything off/ flushed
    blankScreen();
  }
}

void blankScreen(){
  matrix.clearScreen();
  matrix.clearLEDs();
}


////////////////////////////////
////////TIMER FUNCTIONS///////////
////////////////////////////////
void scroll(){
  if(brakeOn){
    return;
  }
  else if(rightIndicator){
    matrix.translate(stepSize, 0);
    matrix.writeScreen();
  }
  else if(leftIndicator){
    matrix.translate(-1*stepSize, 0);
    matrix.writeScreen();
  }
}

void strobe(){
  if(strobeOn == false || rOn || lOn || brakeOn){
    return;
  }
  else{
    blinkOn = ! blinkOn;
    if(blinkOn){
      drawStrobe();
    }
    else{
      matrix.clearScreen();
    }
  }
}


     

