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
/*char LEDs [] =
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
*/
char LEDs [24][16];
int firstRow[24];
int lastRow[24];
int firstCol[24];
int lastCol[24];
  
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



     

