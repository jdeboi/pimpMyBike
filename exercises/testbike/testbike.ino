// include the library code:
#include <stdlib.h>
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

char rightArrow [] = 
  "100000001000000010000000"
  "010000000100000001000000"
  "001000000010000000100000"
  "000100000001000000010000"
  "000010000000100000001000"
  "000001000000010000000100"
  "000000100000001000000010"
  "000000010000000100000001"
  "000000010000000100000001"
  "000000100000001000000010"
  "000001000000010000000100"
  "000010000000100000001000"
  "000100000001000000010000"
  "001000000010000000100000"
  "010000000100000001000000"
  "100000001000000010000000";

char leftArrow [] = 
  "000000010000000100000001"
  "000000100000001000000010"
  "000001000000010000000100"
  "000010000000100000001000"
  "000100000001000000010000"
  "001000000010000000100000"
  "010000000100000001000000"
  "100000001000000010000000"
  "100000001000000010000000"
  "010000000100000001000000"
  "001000000010000000100000"
  "000100000001000000010000"
  "000010000000100000001000"
  "000001000000010000000100"
  "000000100000001000000010"
  "000000010000000100000001";


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
boolean rightIndicator = true;
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
int numLEDs = height*width;
int stepSize = 2;
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);

//////////Timer Variables/////////////////
int blinkTime = 1000;
Timer scrollTimer;
int scrollTime = 130;
Timer strobeTimer;
int strobeTime = 500;

boolean stateChange = false;

////////////////////////////////////////////////////////
////////////////////////////SETUP////////////////////////////
////////////////////////////////////////////////////////
void setup() {
  //Serial.begin(9600);
  scrollTimer.every(scrollTime, scroll);
  matrix.begin(HT1632_COMMON_16NMOS); 
  delay(500);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  drawRight();
  delay(50);
  pinMode(turnRPin, INPUT); 
  pinMode(turnRLED, OUTPUT);   
  pinMode(turnLPin, INPUT);
  pinMode(turnLLED, OUTPUT); 
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////LOOP////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop() {
  //checkTurning();
  //setTurning();
  //drawLeft();
  //delay(1000);
  //matrix.translate(1, 0);
  //matrix.writeScreen();
  //delay(1000);
  scrollTimer.update();
  //strobeTimer.update();
}

void blankScreen(){
  matrix.clearScreen();
  matrix.clearLEDs();
}

void checkTurning(){
  stateChange = false;
  right = digitalRead(turnRPin);
  left = digitalRead(turnLPin);
  if(right == HIGH && rightOld == LOW){
      rOn =! rOn;
      stateChange = true;
  }
  else if(left == HIGH && leftOld == LOW){
     lOn =! lOn;
     stateChange = true;
  }
  rightOld = right;
  leftOld = left;
}
     
void setTurning(){
  if(stateChange && brakeOn == false){  
    if(rOn && lOn){
      strobeOn =! strobeOn;
      rOn = false;
      lOn = false;
      digitalWrite(turnRLED, LOW);
      digitalWrite(turnLLED, LOW);
    }
    else if(rOn && lOn == false){
      drawRight();
      digitalWrite(turnRLED, HIGH);
    }
    else if(rOn == false && lOn){
      drawLeft();
      digitalWrite(turnLLED, HIGH);
    }
    else if(rOn == false && lOn == false){
      matrix.clearScreen();
      digitalWrite(turnRLED, LOW);
      digitalWrite(turnLLED, LOW);
    }
  }
}

void drawRight(){
 for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, (rightArrow[j+i*24]-'0'));
    }    
 }
 matrix.writeScreen();
}

void drawLeft(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, (leftArrow[j+i*24]-'0'));
    }    
 }
 matrix.writeScreen();
}

void scroll(){
  if(rightIndicator){
    matrix.translate(stepSize, 0);
    matrix.writeScreen();
  }
  else if(leftIndicator){
    matrix.translate(-1*stepSize, 0);
    matrix.writeScreen();
  }
}

