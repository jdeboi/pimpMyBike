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
char brakePixels[]  =
  "000000000001100000000000"
  "000000000011110000000000"
  "000000000111111000000000"
  "000000001110011100000000"
  "000000011100001110000000"
  "000000111001100111000000"
  "000001110011110011100000"
  "000011100111111001110000"
  "000011100111111001110000"
  "000001110011110011100000"
  "000000111001100111000000"
  "000000011100001110000000"
  "000000001110011100000000"
  "000000000111111000000000"
  "000000000011110000000000"
  "000000000001100000000000";

prog_uchar indicator[] PROGMEM  = {
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
  "100000001000000010000000"};


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
char LEDs [] =
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000"
  "000000000000000000000000";

char storeLEDs[] = "000000000000000000000000";
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
  drawRight(); 
  delay(500);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////LOOP////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop() {
  //checkBraking();
  //checkTurning();
  //setTurning();
  //translate(1,0);
  drawLeft();
  delay(500);
  matrix.clearScreen();
  delay(500);
  drawRight();
  delay(500);
  //translate(1,0);
  drawBrake();
  delay(500);
 
  /*
  *To do- figure out why drawStrobe() causes the entire
  *sketch to freeze- stack overflow?
  *drawRight() is exactly the same and works fine
  *(if you replace drawStrobe() with drawRight()).
  *I have to talk to someone who knows more about comp sci
  *or electronics than I do.
  *The sketch also freezes when I try to use timers
  *even though I've literally copy/pasted code from a sketch
  *specifically designed to scroll LEDs.  I'm convinced that it has
  *to do with memory/ hardware, but I dunno.
  */
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
     
void setTurning(){
  if(stateChange && brakeOn == false){  
    if(rOn && lOn){
      strobeOn =! strobeOn;
      //drawStrobe();
      /*
      *To do- figure out why drawStrobe() causes the entire
      *sketch to malfunction- stack overflow?
      *drawRight() is exactly the same and works fine
      *have to talk to someone who knows more about comp sci
      *or electronics than I do
      */
      matrix.clearScreen();
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
void drawBrake(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j< 24; j++) {
      //pixel =  pgm_read_byte_near(brakePixels + j+i*24); 
      matrix.drawPixel(j, i, (brakePixels[j+i*24]-'0'));
      LEDs[j+i*24] = brakePixels[j+i*24];
      //LEDs[j+i*24] = pixel;
      //LEDs[j][i] = rightArrow[j+i*24];
    }    
 }
 matrix.writeScreen();
}

void drawRight(){
 for(int i = 0; i < 16; i++) {
    for(int j = 0; j< 24; j++) {
      pixel =  pgm_read_byte_near(indicator + j+i*24); 
      matrix.drawPixel(j, i, (pixel-'0'));
      LEDs[j+i*24] = pixel;
    }    
 }
 matrix.writeScreen();
}

void drawLeft(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j< 24; j++) {
      //trick to save memory
      pixel =  pgm_read_byte_near(indicator + 23-j+i*24); 
      matrix.drawPixel(j, i, (pixel-'0'));
      LEDs[j+i*24] = pixel;
    }    
 }
 matrix.writeScreen();
}


/*
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
    setLEDs();
}
    
void stepRight() {
    //store the last column 
    for (int h = 0; h < height; h++) {
        lastCol[h] = LEDs[width - 1][h];
    }
    
    //move pixels to the right one column at a time
    //by setting each column equal to the column on the left
    for (int w = width; w > 0; w--) {
        for (int h = 0; h < height; h++) {
            LEDs[w][h] = LEDs[w-1][h];
        }
    }
    //set the first column = to last column of array
    for (int h = 0; h < height; h++) {
        LEDs[0][h] = lastCol[h];
    }
}
    
void stepLeft() {
    //store the first column 
    for (int h = 0; h < height; h++) {
        firstCol[h] = LEDs[0][h];
    }
    
    //move pixels to the left one column at a time
    //by setting each column equal to the column on the right
    for (int w = 0; w < width-1; w++) {
        for (int h = 0; h < height; h++) {
            LEDs[w][h] = LEDs[w+1][h];
        }
    }
    
    //set the last column = to first column of the matrix
    for (int h = 0; h < height; h++) {
        LEDs[width-1][h] = firstCol[h];
    }
}
    
void stepUp() {
    //store the first row 
    for (int w = 0; w < width; w++) {
        firstRow[w] = LEDs[w][0];
    }
    
    //move pixels up one row at a time
    //by setting each row = to row below it
    for (int h = 0; h < height; h++){
        for (int w = 0; w < width; w++) {
            LEDs[w][h]=LEDs[w][h+1];
        }
    }
    
    //set the last row equal to the first row
    for (int w = 0; w < width; w++) {
        LEDs[w][height-1]= firstRow[w];
    } 
}
    
void stepDown() {
    //store the last row 
    for (int w = 0; w < width; w++) {
        lastRow[w] = LEDs[w][height-1];
    }
    
    //move pixels down one row at a time
    //by setting each row = to row above it
    for (int h = height-1; h > 0; h++){
        for (int w = 0; w < width; w++) {
            LEDs[w][h]=LEDs[w][h-1];
        }
    }

    //set the first row equal to the last row
    for (int w = 0; w < width; w++) {
        LEDs[w][0]= lastRow[w];
    } 
}    

void clearLEDs() {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            LEDs[w][h] = 0;
        }
    }
}

    
void setLEDs() {
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            matrix.drawPixel(w, h, LEDs[w][h]-'0');
        }
    }
    matrix.writeScreen();
}  
     
*/
