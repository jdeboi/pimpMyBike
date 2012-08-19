// include the library code:
#include <avr/pgmspace.h>
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

////////////////////////////////////////////////////////////////////////////
/////////////////////////CHAR ARRAYS////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

prog_uchar rightBytes[48] PROGMEM  = {
  64, 64, 64, 
  32, 32, 32, 
  16, 16, 16, 
  8, 8, 8, 
  4, 4, 4, 
  2, 2, 2, 
  1, 1, 1, 
  1, 1, 1, 
  2, 2, 2, 
  4, 4, 4, 
  8, 8, 8, 
  16, 16, 16, 
  32, 32, 32, 
  64, 64, 64, 
  128, 128, 128
};

prog_uchar leftBytes [48] PROGMEM = {
  1, 1, 1, 
  2, 2, 2, 
  4, 4, 4, 
  8, 8, 8, 
  16, 16, 16, 
  32, 32, 32, 
  64, 64, 64, 
  128, 128, 128, 
  128, 128, 128, 
  64, 64, 64, 
  32, 32, 32, 
  16, 16, 16, 
  8, 8, 8, 
  4, 4, 4, 
  2, 2, 2, 
  1, 1, 1
};
  
prog_uchar brakeBytes [48] PROGMEM = {
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
  0, 24, 0
};
  
 
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
  0, 0, 0
};

////////////////////////////////////////////////////////////////////////////
/////////////////////////VARIABLES////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
///////Brake Switch/////////////
int brakeV; 
int brakeOld;
int brakeVPin; 
boolean brakeOn = false;
boolean strobeOn = false;
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
boolean stateChange = false;
boolean turningOn = false;
boolean turningLOn = false;
boolean turningROn = false;
int right;
int left;
int rightOld;
int leftOld;
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
char pixel;
  
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);


///////LCD//////////////////////
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, A0, 8, 7, 4);
int LCDButton;
int brightness = 100;

////////////////////////////////////////////////////////////////////////////
//////////////////////////SETUP/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void setup() {
  // set up the LCD's number of rows and columns:
  Serial.begin(9600);
  lcd.begin(16, 2);
  setBacklight(130, 222, 219);
  lcd.print("Speed Test");
  lcd.setCursor(0,1);
  lcd.print(" Distance Test");
  
  matrix.begin(HT1632_COMMON_16NMOS); 
  delay(500);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
 
  pinMode(turnRPin, INPUT); 
  pinMode(turnRLED, OUTPUT);   
  pinMode(turnLPin, INPUT);
  pinMode(turnLLED, OUTPUT);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////LOOP////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop() {
  //checkBraking();
  checkTurning();
  setTurning();
  //setStrobe();
  //checkReed();
  //printLCD();
}

////////////////////////////////////////////////////////////////////////////
///////////////////////////CHECK////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void checkBraking(){
  brakeV = digitalRead(brakeVPin);
  if(brakeV == HIGH && brakeOld == LOW){
    brakeOn = true;
    drawBrake();
  }
  else if (brakeV == LOW && brakeOld == HIGH){
    brakeOn = false;
    stateChange = true;
    setTurning();
  }
  brakeOld = brakeV;
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

void checkReed(){
  int r = digitalRead(reedPin);
  if(r == 1 && reedOn == false){
    reedOn = true;
    reedTimeDelta = millis() - reedTime;
    reedTime = millis();
    circleNum++;
  }
  else if (r == 0 && reedOn){
    reedOn = false;
  }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////SET/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/*
void setStrobe(){
  if(stateChange && turningOn == false && brakeOn == false){
    if (strobeOn){
      drawStrobe();
    }
    else{
      matrix.clearScreen();
    }
  }
}
*/ 
void setBrake(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 3; j++) {
      tmpByteLEDs[i*3 + j] = pgm_read_byte_near(brakeBytes + i*3 + j);
    }
  }    
}


void setRight(){
 for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 3; j++) {
      tmpByteLEDs[i*3 + j] = pgm_read_byte_near(rightBytes + i*3 + j);
    }
  }    
}

void setLeft(){
   for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 3; j++) {
      tmpByteLEDs[i*3 + j] = pgm_read_byte_near(leftBytes + i*3 + j);
    }
  }    
}
     
void setTurning(){
  if(stateChange && brakeOn == false){  
    if(rOn && lOn){
      strobeOn =! strobeOn;
      if(strobeOn){
        drawBrake();
      }
      else{
        matrix.clearScreen();
      }
      delay(50);
      rOn = false;
      lOn = false;
      digitalWrite(turnRLED, LOW);
      digitalWrite(turnLLED, LOW);
      turningOn = false;
      turningROn = false;
      turningLOn = false;
    }
    else if(rOn && lOn == false){
      drawRight();
      digitalWrite(turnRLED, HIGH);
      turningOn = true;
      turningROn = true;
    }
    else if(rOn == false && lOn){
      drawLeft();
      digitalWrite(turnLLED, HIGH);
      turningOn = true;
      turningLOn = true;
    }
    else if(rOn == false && lOn == false){
      matrix.clearScreen();
      digitalWrite(turnRLED, LOW);
      digitalWrite(turnLLED, LOW);
      turningOn = false;
      turningROn = false;
      turningLOn = false;
    }
  }
}

void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
  // normalize the red LED - its brighter than the rest!
  r = map(r, 0, 255, 0, 100);
  g = map(g, 0, 255, 0, 150);
 
  r = map(r, 0, 255, 0, brightness);
  g = map(g, 0, 255, 0, brightness);
  b = map(b, 0, 255, 0, brightness);
 
  // common anode so invert!
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);
  //Serial.print("R = "); Serial.print(r, DEC);
  //Serial.print(" G = "); Serial.print(g, DEC);
  //Serial.print(" B = "); Serial.println(b, DEC);
  analogWrite(REDLITE, r);
  analogWrite(GREENLITE, g);
  analogWrite(BLUELITE, b);
}


////////////////////////////////////////////////////////////////////////////
////////////////////////////GET/////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
String getSpeedString(){
  speedometer = wheelC/reedTimeDelta; 
  if(metric){
    KPH = speedometer * 36;
    char tmp[25] = "KPH: ";
    dtostrf(KPH,1,2, &tmp[12]);
    return tmp;
  }
  else{
    MPH = speedometer * 22.369;
    char tmp[25] = "KPH: ";
    dtostrf(MPH,1,2, &tmp[12]);
    return tmp;
  } 
}

String getDistanceString(){
  odometer = wheelC*circleNum;
  if(metric){
    kilometers = odometer / 100000;
    char tmp[25] = "Distance: ";
    dtostrf(kilometers,1,2, &tmp[12]);
    return tmp; 
  }
  else{
    miles = odometer / 160934.4;
    char tmp[25] = "Distance: ";
    dtostrf(miles,1,2, &tmp[12]);
    return tmp; 
  }
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////DRAW////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

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

void drawRight(){
  setRight();
  drawLEDs();
}

void drawLeft(){
  setLeft();
  drawLEDs();
}

void drawBrake(){
  setBrake();
  drawLEDs();
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////TRANSLATE////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void translate(int x, int y) {
    //x and y are # of steps in each dimension
    if (x > 0) {
        for (int i = 0; i < x; i++) {
            stepRight();
        }
    }
    else if (x < 0){  
        for (int i = 0; i > x; i--) {
            stepLeft();
        }
    }
    /*
    if (y > 0){
        for (int i = 0; i < y; i++) {
            stepUp();
        }
    }
    else if (y < 0){
        for (int i = 0; i > y; i--) {
            stepDown();
        }
    }
    */
    drawLEDs();
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

void stepRight(){
  //move pixels to the right one bit at a time
  //by setting each bit equal to the bit on the left
  for(int i = 0; i < 16; i++) {
      byte b1t = tmpByteLEDs[i*3] >> 1;
      byte b2t = tmpByteLEDs[i*3 + 1] >> 1;
      byte b3t = tmpByteLEDs[i*3 + 2] >> 1;
      bitWrite(b1t, 7, bitRead(tmpByteLEDs[i*3 + 1], 0));
      bitWrite(b2t, 7, bitRead(tmpByteLEDs[i*3 + 2], 0));
      bitWrite(b3t, 7, bitRead(tmpByteLEDs[i*3], 0));
      tmpByteLEDs[i*3] = b1t;
      tmpByteLEDs[i*3 + 1] = b2t;
      tmpByteLEDs[i*3 + 2] = b3t;
  }
}

