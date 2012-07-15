
int numMatrices = 1;
int [][] LEDpixels;
int wLEDs = 24 * numMatrices;
int hLEDs = 16;
int circleD = 12;
int padding = 5;
int space = circleD + 2 * padding;


void setup(){
  size(wLEDs*space, hLEDs*space);
  LEDpixels = new int[wLEDs][hLEDs];
}

void draw(){
  ellipseMode(CORNER);
  for(int i = 0; i < wLEDs; i ++){
    for(int j = 0; j < hLEDs; j++){
      int on = LEDpixels[i][j];
      fill(on, 0, 0);
      ellipse(i*space, j*space, circleD, circleD);
    }
  }
}

void 
