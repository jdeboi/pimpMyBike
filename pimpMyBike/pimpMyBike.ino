// include the library code:
#include <LiquidCrystal.h>
#include "Timer.h"
#include "HT1632.h"
#define DATA 2
#define WR   3
#define CS   4

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
int reedPin = 13;    //digital input
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
///////Turning Indicator Buttons////////
boolean rOn = false;
boolean lOn = false;
boolean stepUp = false;
int right;
int left;
int rightOld;
int leftOld;
int type;
///////Turning Indicator Matrix///////////
// use this line for single matrix
int numMatrices = 1;
int height = 16;
int width = numMatrices * 32;
int stepSize = 2;
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
int turnRpin = 0;  //digital input; tell if right turning indicator button was pushed
int turnLpin = 1;  //digital input; tell if leftt turning indicator button was pushed 

int state = 0;
int blinkTime = 1000;
Timer scrollTimer;
int scrollTime = 130;
Timer strobeTimer;
int strobeTime = 500;

///////LCD//////////////////////
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //initialize the library with the numbers of the interface pins
int LCDButton;



////////////////////////////////////////////////////////
////////////////////////////SETUP////////////////////////////
////////////////////////////////////////////////////////
void setup() {
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  reedTime = millis();
  //pinMode();
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  matrix.clearLEDs();
  scrollTimer.every(scrollTime, scroll);
  strobeTimer.every(strobeTime, strobe);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////LOOP////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop() {
  checkRightTurning();
  checkLeftTurning();
  checkBraking();
  checkReed();
  getSpeed();
  getDistance();
  printLCD();
  scrollTimer.update();
  strobeTimer.update();
}


void printLCD(){
  lcd.setCursor(1, 0);      // set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0):
  //lcd.print("MPH: " + speedometer); // print the number of seconds since reset:
  lcd.setCursor(1, 1); 
  //lcd.print("MPH: " + miles);
}

void setLEDShape(){
  if(brakeOn){
  }
  //right turning indicator is on, left off
  else if (rOn && lOn == false && stepUp){
    drawRight();
    rightIndicator = true;
  }
  //left turning indicator is on, right off
  else if (lOn && rOn == false && stepUp){
    drawLeft();
    leftIndicator = true;
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
    drawStrobe();
  }
  else if(rOn && lOn && strobeOn){
    strobeOn = false;
    rOn = false;
    lOn = false;
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
void scroll(){ //or turning on
  if(type == 1){
    matrix.translate(stepSize, 0);
  }
  else if(type == 2){
    matrix.translate(-stepSize, 0);
    matrix.writeScreen();
  }
}

void strobe(){
  if(strobeOn == false || rOn || lOn || brakeOn){
  }
  else{
    blinkOn = ! blinkOn;
    if(strobeOn && blinkOn){
      drawStrobe();
    }
    else if(strobeOn && blinkOn == false){
      matrix.clearScreen();
    }
  }
}


     

