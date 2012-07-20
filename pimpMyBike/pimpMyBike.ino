// include the library code:
#include <LiquidCrystal.h>
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

///////Turning Indicator Buttons////////
int turnRpin = 0;  //digital input; tell if right turning indicator button was pushed
int turnLpin = 1;  //digital input; tell if leftt turning indicator button was pushed 
int rBlinkNum = 0;
int lBlinkNum = 0;
boolean rOn = false;
boolean lOn = false;
int blinkTime = 1000;
int rTime = 0;
int lTime = 0;
int right;
int left;
int rightOld;
int leftOld;
int state;
int stepSize = 2;
int type;


Timer scrollTimer;
int scrollTime = 130;
Timer flashTimer;
int flashTime;

///////Turning Indicator Matrix///////////
// use this line for single matrix
//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
// use this line for two matrices!
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

///////Accelerometer////////////
//The minimum and maximum values that came from
//the accelerometer while standing still
//You very well may need to change these
int minVal = 265;
int maxVal = 402;
int xPin = 4;  //analog input
int yPin = 5;  //analog input
int zPin = 6;  //analog input


///////LCD//////////////////////
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //initialize the library with the numbers of the interface pins
int LCDButton

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
boolean reedOn = false;

////////////////////////////////////////////////////////
////////////////////////////SETUP////////////////////////////
////////////////////////////////////////////////////////
void setup() {
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  reedTime = millis();
  pinMode();
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  matrix.clearLEDs();
  scrollTimer.every(scrollTime, scroll);
  flashTimer.every(flashTime, flash);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////LOOP////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void loop() {
  checkTurning();
  checkBraking();
  checkReed();
  getSpeed();
  getDistance();
  printLCD();
  scrollTimer.update();
}

////////////////////////////////////////////////////////
//////////////////////LOOP FUNCTIONS////////////////////////
////////////////////////////////////////////////////////

void checkTurning(){
  right = digitalRead(turnRpin);
  left = digitalRead(turnLpin);
  if(right == HIGH && rightOld == LOW){
      rOn =! rOn;
      turningChanged();
  }
   else if(left == HIGH && leftOld == LOW){
     lOn =! lOn;
     turningChanged();
   } 
   rightOld = right; 
   leftOld = left;
}

void checkBraking(){
  //declare int brakeV and int brakeVPin and boolean brakeOn///////////////////////////////////////////
  brakeV = digitalRead(brakeVPin);
  if(brakeV == HIGH){
    brakeOn = true;
  }
  else if (brakeV == LOW){
    brakeOn = false;
  }
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

void getSpeed(){
  speedometer = wheelC/reedTimeDelta;
  MPH = speedometer * 22.369; 
  KPH = speedometer * 36; 
}

void getDistance(){
  odometer = wheelC*circleNum;
  miles = odometer / 160934.4;
  kilometers = odometer / 100000;
}

void printLCD(){
  lcd.setCursor(1, 0);      // set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0):
  lcd.print("MPH: " + speedometer); // print the number of seconds since reset:
  lcd.setCursor(1, 1); 
  lcd.print("MPH: " + miles);
}




  //also turning indicators...
////////////////////////////////////////////////////////
//////////////REFERENTIAL* FUNCTIONS////////////////////////
////////////////////////////////////////////////////////

////////////////////////////////
///////////SET FUNCTIONS//////////
////////////////////////////////

void setLEDShape(){
  if(brakeOn){
    draw
  }
  //right turning indicator is on, left off
  if (rOn && lOn == false){
    type = 1;
    draw(RIGHT);
  }
  //left turning indicator is on, right off
  else if (lOn && rOn == false){
    type = 2;
    draw(LEFT);
  }
  else if(rOn && lOn){
    type = 3;
    draw(FLASH);
  }
  //left and right turning indicators are off
  //
  else if(rOn == flase && lOn == false)
    //everything off/ flushed
    matrix.clrScreen();
    matrix.clrLEDs();
    type = 4;
  }
}

void braking(){
  if(brakeOn){
    type = 5;
    draw(BRAKING); 
}

////////////////////////////////
////////SHAPE FUNCTIONS///////////
////////////////////////////////

void draw(int t){
  matrix.clearScreen();
  matrix.clearLEDs();
  //right arrow
  if(t == 1){
    matrix.drawLine(0, 0, ((matrix.width())/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((matrix.width()/3)-1, (matrix.height())/2, 0, matrix.height()-1, 1);
     
    matrix.drawLine((matrix.width()/3), 0, (2*matrix.width()/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((2*matrix.width()/3)-1, (matrix.height())/2,matrix.width()/3, matrix.height()-1, 1);
     
    matrix.drawLine((2*matrix.width()/3), 0, matrix.width()-1, (matrix.height()/2)-1, 1);
    matrix.drawLine(matrix.width()-1, matrix.height()/2, 2*matrix.width()/3, matrix.height()-1, 1);
  }
  //left arrow
  else if(t == 2){
     matrix.drawLine(matrix.width()-1, 0, 2*matrix.width()/3, matrix.height()/2-1, 1);
     matrix.drawLine(2*matrix.width()/3, matrix.height()/2, matrix.width()-1, matrix.height()-1, 1);
     matrix.drawLine(2*matrix.width()/3-1, 0, matrix.width()/3, matrix.height()/2-1, 1);
     matrix.drawLine(matrix.width()/3, matrix.height()/2, 2*matrix.width()/3-1, matrix.height()-1, 1);
     matrix.drawLine(matrix.width()/3-1, 0, 0, matrix.height()/2-1, 1);
     matrix.drawLine(0, matrix.height()/2, matrix.width()/3-1, matrix.height()-1, 1);
  }
  //flash shape
  else if (t == 3){
    //flash shape
  }
  //brake shape
  else if (t == 4){
    //brake shape
  }
  matrix.writeScreen();
}

////////////////////////////////
////////TIMER FUNCTIONS///////////
////////////////////////////////
void scroll(){ //or turning on
  if(type == 1){
    matrix.translate(RIGHT, stepSize));
  }
  else if(type == 2){
    matrix.translate(LEFT, stepSize);
    matrix.writeScreen();
  }
}

void flash(){
  if(type == 3){
    blinkOn =! blinkOn;
    matrix.blink(blinkOn);
  }
}

