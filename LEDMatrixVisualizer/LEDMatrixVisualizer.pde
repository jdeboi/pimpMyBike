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
int l0x;
int l0y;
int l1x;
int l1y;
boolean lineOn;
boolean lclick1;

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
  if(lineOn){
    if(lclick1){
      l0x = x;
      l0y = y;
      lclick1 = false;
    }
    else{
      l1x = x;
      l1y = y;
      lineOn = false;
      lclick1 = true;
      drawLine(l0x, l0y, l1x, l1y);
    }
  }
  else{
    LEDpixels[x][y] = !LEDpixels[x][y];
  }
}

void keyPressed(){
  if(key == 'o'){
    label = !label;
  }
  if(key == 'l'){
    lineOn = true;
  }
}

void drawLine(int x0, int y0, int x1, int y1){
 boolean steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    swap(x0, y0);
    swap(x1, y1);
  }

  if (x0 > x1) {
    swap(x0, x1);
    swap(y0, y1);
  }

  int dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int err = dx / 2;
  int ystep;

  if (y0 < y1) {
    ystep = 1;
  } else {
    ystep = -1;}

  for (; x0<=x1; x0++) {
    if (steep) {
      LEDpixels[y0][x0] = 1;
    } else {
      LEDpixels[x0][y0] = 1;
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}
 
 
 

