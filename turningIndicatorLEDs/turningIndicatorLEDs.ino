#include "HT1632.h"
#include "Timer.h"

#define DATA 2
#define WR   3
#define CS   4
#define CS2  5

// use this line for single matrix
HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS);
// use this line for two matrices!
//HT1632LEDMatrix matrix = HT1632LEDMatrix(DATA, WR, CS, CS2);

Timer t;

void setup() {
  Serial.begin(9600);
  matrix.begin(HT1632_COMMON_16NMOS);  
  matrix.fillScreen();
  delay(500);
  matrix.clearScreen();
  arrow(); 
  //t.every(blinkTime, arrow);
}

void loop() {
  matrix.translate(
}

 void scroll(int s){
  //if(on){
  //  on = true;
  //}
  if(s == 2){
    /*
    int x0 = i*matrix.width()/3;
    int y0 = 0;
    int x1 = (i+1)*matrix.width()/3-1;
    int y1 = matrix.height()/2-1;
    int x2
    int y2
    */
     
     
     
    
      matrix.translate(3);
      Serial.println(matrix.getLEDValue(0, 8));
      matrix.writeScreen();
      delay(2000);
    
 }
  
  else if(s == 4){
     matrix.drawLine(0, 0, (matrix.width()-1)/2, matrix.height()-1, 1);
     matrix.drawLine((matrix.width()-1)/2, 0, 0, matrix.height()-1, 1);
     matrix.writeScreen();
  }
  else if(s == 3){}
}

void arrow(int d);
  if(d = 1){
    matrix.drawLine(0, 0, ((matrix.width())/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((matrix.width()/3)-1, (matrix.height())/2, 0, matrix.height()-1, 1);
     
    matrix.drawLine((matrix.width()/3), 0, (2*matrix.width()/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((2*matrix.width()/3)-1, (matrix.height())/2,matrix.width()/3, matrix.height()-1, 1);
     
    matrix.drawLine((2*matrix.width()/3), 0, matrix.width()-1, (matrix.height()/2)-1, 1);
    matrix.drawLine(matrix.width()-1, matrix.height()/2, 2*matrix.width()/3, matrix.height()-1, 1);
    matrix.writeScreen();
  }
}
