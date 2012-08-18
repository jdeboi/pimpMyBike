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
  

// use this line for single matrix
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
// use this line for two matrices!
//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

Timer t;
int scrollTime = 130;

void setup() {
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);  
  //matrix.fillScreen();
  drawLeft();
  delay(1000);
  matrix.clearScreen();
  delay(500);
}

void loop() {
  //drawLeft();
  delay(500);
}


void drawLeft(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, leftArrow[j+i*24]);
      matrix.fillScreen();
    }    
  }
}

void drawRight(int d){
  //right arrow
    matrix.drawLine(0, 0, ((matrix.width())/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((matrix.width()/3)-1, (matrix.height())/2, 0, matrix.height()-1, 1);

    matrix.drawLine((matrix.width()/3), 0, (2*matrix.width()/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((2*matrix.width()/3)-1, (matrix.height())/2,matrix.width()/3, matrix.height()-1, 1);

    matrix.drawLine((2*matrix.width()/3), 0, matrix.width()-1, (matrix.height()/2)-1, 1);
    matrix.drawLine(matrix.width()-1, matrix.height()/2, 2*matrix.width()/3, matrix.height()-1, 1);
    matrix.writeScreen();
}



