#include "HT1632.h"
#include "Timer.h"

#define DATA 11 //orange
#define WR   12 //yellow
#define CS   10 //white
//#define CS2  5

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

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
  
// use this line for single matrix
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
// use this line for two matrices!
//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

Timer t;
int scrollTime = 130;

void setup() {
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(1000);
  matrix.clearScreen();
  delay(500);
}

void loop() {
  drawRight();
  delay(1000);
  drawLeft();
  delay(1000);
}


void drawLeft(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, (leftArrow[j+i*24]-'0'));
    }    
  }
  matrix.writeScreen();
}

void drawRight(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, (rightArrow[j+i*24]-'0'));
    }    
  }
  matrix.writeScreen();
}




