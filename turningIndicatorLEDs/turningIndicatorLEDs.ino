#include "HT1632.h"

#define DATA 2
#define WR   3
#define CS   4
#define CS2  5

// use this line for single matrix
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
// use this line for two matrices!
//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

void setup() {
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen(); 
}

void loop() {
  arrow(1, 1);
  delay(700);
  arrow(1, 0);
  delay(700);
  arrow(2, 1);
  delay(700);
  arrow(2, 0);
  delay(700);
  arrow(3, 1);
  delay(700);
  arrow(3, 0);
  delay(700);
}

 void arrow(int s, int t){
  if(t == 1){
    matrix.clearScreen();
  }
  else if(s == 1){
     matrix.drawLine(0, 0, (matrix.width()-1)/3, (matrix.height()-1)/2, 1);
     matrix.drawLine((matrix.width()-1)/3, (matrix.height())/2, 0, matrix.height()-1, 1);
     //matrix.drawLine((matrix.width()-1)/2, 0, 0, matrix.height()-1, 1);
     matrix.writeScreen();
  }
  else if(s == 2){
     matrix.drawLine(0, 0, (matrix.width()-1)/2, matrix.height()-1, 1);
     matrix.drawLine((matrix.width()-1)/2, 0, 0, matrix.height()-1, 1);
     matrix.writeScreen();
  }
  else if(s == 3){}
}
