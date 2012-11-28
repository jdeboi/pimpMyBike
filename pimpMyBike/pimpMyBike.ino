////////////////////////////////////////////////////////////////////////
// pimpMyBike ///////////////////////////////////
// jdeboi
// September 15, 2012
// For more information: www.jdeboi.com
// Feel free to copy, distribute, improve, deconstruct...
////////////////////////////////////////////////////////////////////////

////////////////////////////////////
///////Headers/libraries//////////////////////
///////////////////////////////

#include <avr/pgmspace.h>
#include <stdlib.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "Timer.h"            //https://github.com/JChristensen/Timer
#include "HT1632.h"           //https://github.com/adafruit/HT1632

///////////////////////////////////////////////////////////////
////////////////////////VARIABLES////////////////////
///////////////////////////////////////////

////////////////////////////////////
/////Variables to set/////////////////////////
///////////////////////////////

//set metric = false to use miles
boolean metric = true;
//in centimeters 
float wheelC = 212.5;


////////////////////////////////////
///////Pins to set////////////////////////////
///////////////////////////////

/*
Note: Change the pin numbers according
to your individual circuit. For most pins, 
it doesn't matter whether you use analog 
or digital I/O.
*/

const int brakeVPin = A0;   //analog input
const int reedPin = A1;     //any input
const int turnRPin = A3;    //any input; pin used to sense turning button
const int turnRLED = A5;    //any output; pin used to turn on button LED
const int turnLPin = A2;    //any input; pin used to sense turning button
const int turnLLED = A4;    //any output; pin used to turn on button LED
const int data = 11;        //any output; LED panel, orange wire
const int wr = 12;          //any output; LED panel, yellow wire
const int cs = 10;          //any output; LED panel, white wire
const int LCD4 = 2;         //any output; LCD pin #4
const int LCD6 = 3;         //any output; LCD pin #6    
const int LCD11 = 13;       //any output; LCD pin #11
const int LCD12 = 8;        //any output; LCD pin #12
const int LCD13 = 7;        //any output; LCD pin #13 
const int LCD14 = 4;        //any output; LCD pin #14
const int redLCD = 5;       //analog out (~PWM pin); LCD pin #16  
const int greenLCD = 6;     //analog out (~PWM pin); LCD pin #17
const int blueLCD = 9;      //analog out (~PWM pin); LCD pin #18 

/*
for LCD pin wiring: http://learn.adafruit.com/character-lcds/rgb-backlit-lcds

LCD# - Arduino#
-------------------
1 - GND
2 - 5V
3 - LCD potentiometer (not connected to Arduino)
4 - LCD1 (I used pin D2)
5 - GND
6 - LCD2 (I used pin D3)
7 through 10 aren't connected to the Arduino
11 - LCD3 
12 - LCD4 
13 - LCD5 
14 - LCD6 
15 - 5V
16 - redLCD, ~PWM pin (I used pin D5)
17 - greenLCD, ~PWM pin (I used pin D6)
18 - blueLCD, ~PWM pin (I used pin D9)

16 through 18 control the color of the LCD backlight
*/


////////////////////////////////////
///////Bike Variables/////////////////////////
///////////////////////////////

///////Brake Switch/////////////
int brakeV; 
int brakeOld; 
int brakeThresh = 250;
int brakeTime;
boolean brakeOn = false;
boolean strobeOn = false;

///////Reed Switch//////////////
int circleNum = 0;
float odometer = 0;
float miles = 0;
float kilometers = 0;
float speedometer = 0;
float MPH = 0;
float KPH = 0;
int reedTime = 0;
int reedTimeDelta = 0;
boolean reedOn = false;

////Turning Indicator Buttons///
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
unsigned long millisRight;
unsigned long millisLeft;

//////LED Panel/////////////////
//single matrix
int numMatrices = 1;
int height = 16;
int width = numMatrices * 32;
int numLEDs = height*width;
int stepSize = 2;
char pixel;
HT1632LEDMatrix matrix = HT1632LEDMatrix(data, wr, cs);

///////LCD//////////////////////
LiquidCrystal lcd(LCD4, LCD6, LCD11, LCD12, LCD13, LCD14);
int LCDButton;
int brightness = 50;
int red = 130;
int green = 222;
int blue = 219;
int counter;
boolean brightUp;
boolean backlightOn; 

//////////Timer Variables///////
int blinkTime = 1000;
Timer scrollTimer;
int scrollTime = 130;
Timer strobeTimer;
int strobeTime = 100;
boolean blinkOn;

////////////////////////////////////
/////////LED Designs//////////////////////////
///////////////////////////////

/*
Note: bitmap of LED pixels (ints in 
binary store value of each LED- either
1 or 0- on/off respectively.
printed  the ints using LED matrix visulaizer
http://jdeboi.com/portfolio/electronics/bike/visualizer.html

save SRAM by saving in flash memory:
http://arduino.cc/en/Reference/PROGMEM
not enough SRAM to store LED patterns as
ints or chars
*/

//right turning indicator LED pattern
prog_uchar rightBytes[48] PROGMEM  = {
  28, 0, 56, 
  14, 0, 112, 
  7, 0, 224, 
  3, 129, 192, 
  1, 195, 128, 
  0, 231, 0, 
  0, 126, 0, 
  0, 60, 0, 
  28, 0, 56, 
  14, 0, 112, 
  7, 0, 224, 
  3, 129, 192, 
  1, 195, 128, 
  0, 231, 0, 
  0, 126, 0, 
  0, 60, 0
};

//left turning indicator LED pattern
prog_uchar leftBytes [48] PROGMEM = {
  0, 24, 0, 
  0, 60, 0, 
  0, 126, 0, 
  0, 231, 0, 
  1, 195, 128, 
  3, 129, 192, 
  7, 0, 224, 
  14, 0, 112, 
  0, 28, 0, 
  0, 62, 0, 
  0, 119, 0, 
  0, 227, 128, 
  1, 193, 192, 
  3, 128, 224, 
  7, 0, 112, 
  14, 0, 56
};

//brake and night-taillight LED pattern
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

//byte array to store LED pattern;
//needed for translate()
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



///////////////////////////////////////////////////////////////
//////////////////////////SETUP//////////////////////
///////////////////////////////////////////

void setup() {
  delay(500);
  // set up the LCD's number of rows and columns:
  scrollTimer.every(scrollTime, scroll);
  strobeTimer.every(strobeTime, strobe);
  lcd.begin(16, 2);
  backlightOff();

  matrix.begin(HT1632_COMMON_16NMOS); 
  delay(500);
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();

  pinMode(turnRPin, INPUT); 
  pinMode(turnRLED, OUTPUT);   
  pinMode(turnLPin, INPUT);
  pinMode(turnLLED, OUTPUT);
  
  /*
  measure the brake threshold when the Arduino turns on- 
  the tab may have moved around since the last time
  you used the bike circuit
  */
  brakeThresh = analogRead(brakeV) - 25;
  delay(800);

  /*
  optional to do: Map the brake LED brightness
  to force applied on the brakes,
  more accurately, to the voltage divider of two
  resistors in series- 
  map(0, 1023, 0, brakeThresh);
  */
}

///////////////////////////////////////////////////////////////
////////////////////////////LOOP/////////////////////
///////////////////////////////////////////

void loop() {
  checkBraking();
  checkTurning();
  setTurning();
  scrollTimer.update();
  strobeTimer.update();
  checkReed();
  printSpeed();
  printDistance();
  //debugBrake();
}

///////////////////////////////////////////////////////////////
///////////////////////////CHECK/////////////////////
///////////////////////////////////////////

void checkBraking(){
  brakeV = analogRead(brakeVPin);
  if(brakeV < brakeThresh){
    brakeOn = true;
    drawBrake();
  }
  else if (brakeV > brakeThresh){
    if(brakeOn == true){
      brakeOn = false;
      stateChange = true;
      setTurning();
    }
  }
}

void checkTurning(){
  stateChange = false;
  right = digitalRead(turnRPin);
  left = digitalRead(turnLPin);
  if(right == HIGH && rightOld == LOW){
    millisRight = millis();
    rOn =! rOn;
    stateChange = true;
  }
  else if(left == HIGH && leftOld == LOW){
    millisLeft = millis();
    lOn =! lOn;
    stateChange = true;
  }
  else if(right == HIGH && rightOld == HIGH){
    int deltaTime = millis() - millisRight;
    if(deltaTime > 1000 && !backlightOn){
      setLCDColor();  
    }
    else if (deltaTime > 1000) {
       backlightOff();
    }
  }
   else if(right == LOW && rightOld == HIGH){
    int deltaTime = millis() - millisRight;
    if(deltaTime > 1000){
      backlightOn =! backlightOn;
      delay(30);
    }  
  }
  else if(left == HIGH && leftOld == HIGH){
    if(millis() - millisLeft > 1000){
      resetLCD();
    }
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

///////////////////////////////////////////////////////////////
////////////////////////////SET//////////////////////
///////////////////////////////////////////

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

void setBacklight() {
  /*
  courtesy of Adafruit
  http://learn.adafruit.com/character-lcds/rgb-backlit-lcds
  */
  
  // normalize the red LED - its brighter than the rest!
  int r = red;
  int g = green;
  int b = blue;

  r = map(r, 0, 255, 0, 100);
  g = map(g, 0, 255, 0, 150);
 
  r = map(r, 0, 255, 0, brightness);
  g = map(g, 0, 255, 0, brightness);
  b = map(b, 0, 255, 0, brightness);


  // common anode so invert!
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);

  analogWrite(redLCD, r);
  analogWrite(greenLCD, g);
  analogWrite(blueLCD, b);
}

void backlightOff(){
  //common annode, so invert (?) 255 and 0
  analogWrite(redLCD, 255);
  analogWrite(greenLCD, 255);
  analogWrite(blueLCD, 255);
}

void setLCDColor(){
  counter++;
  if(counter == 765){
    counter = 0;
  }
  if(counter < 255){
    red = counter;
    green = 0;
    blue = 255 - counter;
  }
  else if(counter >= 255 && counter < 510) {
    red = 255 - (counter % 255);
    green = (counter % 255);
    blue = 0;
  }
  else {
    red = 0;
    green = 255 - (counter % 510);
    blue = counter % 510;
  }
  setBacklight();
  delay(5);
}

void resetLCD(){
  circleNum = 0;
  backlightOff();
}

///////////////////////////////////////////////////////////////
///////////////////////////PRINT/////////////////////
///////////////////////////////////////////

void printSpeed(){
  speedometer = wheelC/reedTimeDelta; 
  if(metric){
    KPH = speedometer * 36;
    lcd.setCursor(1, 0); 
    lcd.print("KPH: ");
    lcd.setCursor(6, 0);
    lcd.print(KPH, 2);
  }
  else{
    MPH = speedometer * 22.369;
    lcd.setCursor(1, 0); 
    lcd.print("MPH: ");
    lcd.setCursor(6, 0);
    lcd.print(MPH, 2);
  } 
}

void printDistance(){
  odometer = wheelC*circleNum;
  if(metric){
    kilometers = odometer / 100000;
    lcd.setCursor(1, 1); 
    lcd.print("KM: ");
    lcd.setCursor(5, 1);
    lcd.print(kilometers, 2); 
  }
  else{
    miles = odometer / 160934.4;
    lcd.setCursor(1, 1); 
    lcd.print("Miles: ");
    lcd.setCursor(5, 1);
    lcd.print(miles, 2); 
  }
}

///////////////////////////////////////////////////////////////
///////////////////////////DRAW//////////////////////
///////////////////////////////////////////

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

///////////////////////////////////////////////////////////////
/////////////////////////TRANSLATE///////////////////
///////////////////////////////////////////

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
  drawLEDs();
}

void stepLeft(){
  //move pixels to the left one bit at a time
  //by setting each bit equal to the bit on the right
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

void stepUp(){
  //move pixels up by setting each byte equal to the byte 
  //below it
  byte b1t =  tmpByteLEDs[0];
  byte b2t = tmpByteLEDs[1];
  byte b3t = tmpByteLEDs[2];
  for(int i = 0; i < 15; i++) {
    for (int j = 0; j < 3; j++){
      tmpByteLEDs[i*3 + j] = tmpByteLEDs[(i+1)*3 + j];
    }
  }
  tmpByteLEDs[45] = b1t;
  tmpByteLEDs[46] = b2t;
  tmpByteLEDs[47] = b3t;
}

void stepDown(){
  //move pixels down by setting each byte equal to the byte 
  //above it
  byte b1t =  tmpByteLEDs[45];
  byte b2t = tmpByteLEDs[46];
  byte b3t = tmpByteLEDs[47];
  for(int i = 15; i > 0; i--) {
    for (int j = 0; j < 3; j++){
      tmpByteLEDs[i*3 + j] = tmpByteLEDs[(i-1)*3 + j];
    }
  }
  tmpByteLEDs[0] = b1t;
  tmpByteLEDs[1] = b2t;
  tmpByteLEDs[2] = b3t;
}


///////////////////////////////////////////////////////////////
//////////////////////TIMER FUNCTIONS////////////////
///////////////////////////////////////////

void scroll(){
  if(brakeOn == false){
    if(rOn){
      translate(0, -1);
    }
    else if(lOn){
      translate(0, 1);
    }
  }
}

void strobe(){
  if(strobeOn && turningOn == false && brakeOn == false){
    blinkOn =! blinkOn;
    if(blinkOn){
      drawBrake();
    }
    else{
      matrix.clearScreen();
    }
  }
}

///////////////////////////////////////////////////////////////
//////////////////////DEBUG FUNCTIONS////////////////
///////////////////////////////////////////

void debugBrake(){
  int br = analogRead(brakeVPin);
  lcd.setCursor(1, 0); 
  lcd.print(br);
}