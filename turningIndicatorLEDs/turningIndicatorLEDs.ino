#include "HT1632.h"
#include "Timer.h"

#define DATA 2
#define WR   3
#define CS   4
#define CS2  5

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

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
  delay(500);
  matrix.clearScreen();
  //arrow(LEFT); 
  //t.every(scrollTime, scroll);
  drawBrake();
}

void loop() {

  t.update();
}

void arrow(int d){
  //right arrow
  if(d == 1){
    matrix.drawLine(0, 0, ((matrix.width())/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((matrix.width()/3)-1, (matrix.height())/2, 0, matrix.height()-1, 1);

    matrix.drawLine((matrix.width()/3), 0, (2*matrix.width()/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((2*matrix.width()/3)-1, (matrix.height())/2,matrix.width()/3, matrix.height()-1, 1);

    matrix.drawLine((2*matrix.width()/3), 0, matrix.width()-1, (matrix.height()/2)-1, 1);
    matrix.drawLine(matrix.width()-1, matrix.height()/2, 2*matrix.width()/3, matrix.height()-1, 1);
    matrix.writeScreen();
  }
  //left arrow
  else if(d == 2){
    matrix.drawLine(matrix.width()-1, 0, 2*matrix.width()/3, matrix.height()/2-1, 1);
    matrix.drawLine(2*matrix.width()/3, matrix.height()/2, matrix.width()-1, matrix.height()-1, 1);
    matrix.drawLine(2*matrix.width()/3-1, 0, matrix.width()/3, matrix.height()/2-1, 1);
    matrix.drawLine(matrix.width()/3, matrix.height()/2, 2*matrix.width()/3-1, matrix.height()-1, 1);
    matrix.drawLine(matrix.width()/3-1, 0, 0, matrix.height()/2-1, 1);
    matrix.drawLine(0, matrix.height()/2, matrix.width()/3-1, matrix.height()-1, 1);
    matrix.writeScreen();
  }
}

void scroll(){
  //matrix.translate(-1, 0);
  drawBrake();
  //matrix.writeScreen();
  //matrix.clearScreen();
}

