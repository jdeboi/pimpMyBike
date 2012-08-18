#include "HT1632.h"
#include "Timer.h"

#define DATA 11
#define WR   12
#define CS   10
//#define CS2  5

#define RIGHT 1
#define LEFT 2
#define UP 3
#define DOWN 4

int rightArrow [108] = {
  11, 12, 34, 35, 36, 37, 57, 58, 
  59, 60, 61, 62, 80, 81, 82, 85, 
  86, 87, 103, 104, 105, 110, 111, 112, 
  126, 127, 128, 131, 132, 135, 136, 137, 
  149, 150, 151, 154, 155, 156, 157, 160, 
  161, 162, 172, 173, 174, 177, 178, 179, 
  180, 181, 182, 185, 186, 187, 196, 197, 
  198, 201, 202, 203, 204, 205, 206, 209, 
  210, 211, 221, 222, 223, 226, 227, 228, 
  229, 232, 233, 234, 246, 247, 248, 251, 
  252, 255, 256, 257, 271, 272, 273, 278, 
  279, 280, 296, 297, 298, 301, 302, 303, 
  321, 322, 323, 324, 325, 326, 346, 347, 
  348, 349, 371, 372
};

int leftArrow [16*24] = {
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 
  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
  0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
  0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
  1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 
  0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 
  0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 
  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 
  0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 
  0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1  
};

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
  matrix.clearLEDs();
  //arrow(LEFT); 
  //t.every(scrollTime, scroll);
  //drawRight();
  //delay(1000);
  //matrix.clearScreen();
  drawLeft();
  delay(500);
  matrix.fillScreen();
}

void loop() {
  //matrix.clearScreen();
  //drawRight();
  delay(500);
  //t.update();
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
  drawLeft();
  //matrix.writeScreen();
  //matrix.clearScreen();
}


void drawRight(){
 //for(int i = 0; i < 108; i++) {
   matrix.clearScreen();
   matrix.clearLEDs();
   matrix.drawPixel(rightArrow[4]%(24), 6, 1);
   matrix.writeScreen();
// }    
}

void drawLeft(){
  //for(int i = 0; i < 16; i++) {
      //matrix.drawPixel(j, i, leftArrow[j+i*24]);
      matrix.fillScreen();
   // }    
 //}
}

