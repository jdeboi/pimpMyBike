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

byte byteLEDs [48] = {
  0, 24, 0, 
  0, 60, 0, 
  0, 126, 0, 
  0, 231, 0, 
  1, 195, 128, 
  3, 153, 192, 
  7, 60, 224, 
  14, 126, 112, 
  14, 126, 112, 
  7, 60, 224, 
  3, 153, 192, 
  1, 195, 128, 
  0, 231, 0, 
  0, 126, 0, 
  0, 60, 0, 
  0, 24, 0};
  
/*  
byte tmpByteLEDs [48] = {
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0, 
  0, 0, 0};
*/
byte tmpByteLEDs [48] = {
  0, 24, 0, 
  0, 60, 0, 
  0, 126, 0, 
  0, 231, 0, 
  1, 195, 128, 
  3, 153, 192, 
  7, 60, 224, 
  14, 126, 112, 
  14, 126, 112, 
  7, 60, 224, 
  3, 153, 192, 
  1, 195, 128, 
  0, 231, 0, 
  0, 126, 0, 
  0, 60, 0, 
  0, 24, 0};

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
  drawLEDs();
  delay(500);
  translateLeft();
  delay(500);
  //strobeTimer.update();
}


void drawLEDs(){
 for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 3; j++) {
      for(int k = 0; k < 8; k++) {
        int pixel = bitRead(tmpByteLEDs[i*3+j], 7 - k);
        matrix.drawPixel(j*8+k, i, pixel);
      }
    }    
 }
 matrix.writeScreen();
}

void stepLeft(){
  for(int i = 0; i < 16; i++) {
      byte b1t = tmpByteLEDs[i*3] << 1;
      byte b2t = tmpByteLEDs[i*3 + 1] << 1;
      byte b3t = tmpByteLEDs[i*3 + 2] << 1;
      bitWrite(b1t, 0, bitRead(tmpByteLEDs[i*3 + 1], 7));
      bitWrite(b2t, 0, bitRead(tmpByteLEDs[i*3 + 2], 7));
      bitWrite(b3t, 0, bitRead(tmpByteLEDs[i*3], 7));
      tmpByteLEDs[i*3] = b1t;
      tmpByteLEDs[i*3 + 1] = b2t;
      tmpByteLEDs[i*3 + 2] = b3t;
  }
}

/*
void drawLeft(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, (leftArrow[j+i*24]-'0'));
    }    
 }
 matrix.writeScreen();
}
*/

void scroll(){
  if(rightIndicator){
    //matrix.translate(stepSize, 0);
    matrix.writeScreen();
  }
  else if(leftIndicator){
    //matrix.translate(-1*stepSize, 0);
    matrix.writeScreen();
  }
}

