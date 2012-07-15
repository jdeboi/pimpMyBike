
int numMatrices = 2;
boolean [][] LEDpixels;
int wLEDs = 24 * numMatrices;
int hLEDs = 16;
int circleD = 12;
int padding = 5;
int space = circleD + 2 * padding;
int w = wLEDs*space;
int h = hLEDs*space;
boolean label;

void setup(){
  size(w, h);
  LEDpixels = new boolean[wLEDs][hLEDs];
}

void draw(){
  background(220);
  ellipseMode(CORNER);
  stroke(0);
  for(int i = 0; i < wLEDs; i ++){
    for(int j = 0; j < hLEDs; j++){
      fill(0, 0, 0);
      if(LEDpixels[i][j] == true){
        fill(255, 0, 0);
      }
      ellipse(i*space, j*space, circleD, circleD);
    }
  }
  line(0, h/2-padding, w, h/2-padding);
  for(int i = 0; i < numMatrices*3; i++){
    line(i*w/(3*numMatrices)- padding, 0, i*w/(3*numMatrices) - padding, h);
  }
  if(label == true){
    String pixelLoc = ("x: " + mouseX/space + ", y: " + mouseY/space);
    fill(0, 0, 0, 170);
    rectMode(CORNER);
    noStroke();
    rect(mouseX-4, mouseY-12, 80, 18);
    fill(0, 255, 0);
    text(pixelLoc, mouseX, mouseY);
  }
}

void mousePressed() {
   int x = mouseX/space;
   int y = mouseY/space;
   LEDpixels[x][y] = !LEDpixels[x][y];
}

void keyPressed(){
  if(key == 'o'){
    label = !label;
  }
}
