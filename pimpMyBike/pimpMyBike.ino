// include the library code:
#include <LiquidCrystal.h>

///////Turning Indicator////////
int turnRpin = 0;  //digital input; tell if right turning indicator button was pushed
int turnLpin = 1;  //digital input; tell if leftt turning indicator button was pushed 
int transRpin = 2; //output; power transistor to turn on right turning indicator
int transLpin = 3; //output; power transistor to turn on left turning indicator
int rBlinkNum = 0;
int lBlinkNum = 0;
boolean rOn = false;
boolean lOn = false;
int blinkTime = 1000;
int rTime = 0;
int lTime = 0;

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

void setup() {
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  reedTime = millis();
  pinMode();
}


void loop() {
  checkTurning();
  setTurning();
  checkBraking();
  checkReed();
  speedometer();
  odometer();
  printLCD();
}

void checkTurning(){
  int right = digitalRead(turnRpin);
  int left = digitalRead(turnLpin);
  
  if (right == HIGH){    
    if(rOn == false){
      rOn = true;
      digitalWrite(transRpin, HIGH);
      rTime = millis();
      rBlinkNum = 0;
    }
    else if(rOn && (millis()- rTime) > 300){
      rOn = false;
      digitalWrite(transRpin, LOW);
    }
  }
 
  if (left == HIGH){   
    if(lOn == false){
      lOn = true;
      digitalWrite(transLpin, HIGH);
      lTime = millis();
      lBlinkNum = 0;
    }
    else if(lOn && (millis() - lTime) > 300){
      lOn = false;
      digitalWrite(transLpin, LOW);
    }
  }   
}

void setTurning(){
  if(rOn && lOn == false){
    if(changeState(rTime)){
      rTime = millis();
      rBlinkNum++;
      int state = rBlinkNum%2;
      digitalWrite(transRpin, state);
    }
  }
  else if(lOn && rOn == false){
    if(changeState(lTime)){
      lTime = millis();
      lBlinkNum++;
      int state = lBlinkNum%2;
      digitalWrite(transLpin, state);
    }
  }
  else if(lOn && rOn){
    if(changeState(rTime)){
        rTime = millis();
        rBlinkNum++;
        int state = rBlinkNum%2;
        digitalWrite(transRpin, state);
        digitalWrite(transLpin, state);
      }
  }
}


boolean changeState(int time){
  int n = (millis() - time)/blinkTime;
  if(n > 1){
    return true;
  }
  else{
    return false;
  }   
}

void checkBraking(){
  //read the analog values from the accelerometer
  int xRead = analogRead(xPin);
  int yRead = analogRead(yPin);
  int zRead = analogRead(zPin);
}

void checkReed(){
  int r = digitalRead(reedPin);
  if(r == 1 && reedOn == false){
    reedOn = true;
    reedTime = millis();
    circleNum++;
  }
  else if (r == 0 && reedOn){
    reedOn = false;
  }
}

void speedometer(){
  speedometer = (millis() - reedTime)/wheelC;
  int m = (int) speedometer * 2236.9; 
  int m = (int) speedometer * 3600; 
  MPH = m/100.0;
  KPH = k/100.0;
}

void odometer(){
  odometer = wheelC*circleNum;
  int m = (int) odometer / 1609.344;
  int k = (int) odometer / 1000;
  miles = m / 100.0; 
  kilometers = k / 100.0;
}

void printLCD(){
  lcd.setCursor(1, 0);      // set the cursor to column 0, line 1 (note: line 1 is the second row, since counting begins with 0):
  lcd.print("MPH: " + speedometer); // print the number of seconds since reset:
  lcd.setCursor(1, 1); 
  lcd.print("MPH: " + miles);
}




