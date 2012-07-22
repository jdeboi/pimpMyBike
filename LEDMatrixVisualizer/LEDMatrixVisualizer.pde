int numMatrices = 2;
int [][] LEDPixels;
int [][] LEDTempPixels;
int wLEDs = 24 * numMatrices;
int hLEDs = 16;
int circleD = 12;
int padding = 5;
int space = circleD + 2 * padding;
int w = wLEDs*space;
int h = hLEDs*space;
boolean label;
int x0Click;
int y0Click;
int x1Click;
int y1Click;
int xClick;
int yClick;
boolean drawing;
boolean lineOn;
boolean click1;
boolean circleOn;
boolean fillCircle = false;
int LEDon = 1;
LinkedList<Circle> circles = new LinkedList<Circle>();
//LinkedList<PLine> LEDlines = new LinkedList<PLine>();

void setup(){
  size(w, h+100);
  LEDPixels = new int[wLEDs][hLEDs];
}

void draw(){
  background(220);
  text("C: draw circle", 20, h+20);
  text("F: toggle fill", 20, h+40);
  text("L: draw line", 20, h+60);
  text("O: toggle LED on/off", 20, h+80);
  ellipseMode(CORNER);
  stroke(0);
  for(int i = 0; i < wLEDs; i ++){
    for(int j = 0; j < hLEDs; j++){
      fill(0, 0, 0);
      if(circleOn && click1 == false && circles.getLast().inCircle(i, j)){
        if(LEDon == 1){
          fill(255, 0, 0);
        }
      }
      else if(LEDPixels[i][j] == 1){
        fill(255, 0, 0);
      }
      ellipse(i*space+padding, j*space+padding, circleD, circleD);
    }
  }
  line(0, h/2, w, h/2);
  line(0, h, w, h);
  for(int i = 1; i < numMatrices*3; i++){
    line(i*w/(3*numMatrices), 0, i*w/(3*numMatrices), h);
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
  if(lineOn && click1 == false){
    line(xClick, yClick, mouseX, mouseY);
  }
  else if(circleOn && click1 == false){
    circles.getLast().drawCircleCursor(mouseX, mouseY);
  }
 
}
///////////////////////////////////////////////
/////////////////////////////MOUSE PRESSED////////////////////
///////////////////////////////////////////////////////
void mousePressed() {
  int x = mouseX/space;
  int y = mouseY/space;
  if(lineOn){
    if(click1){
      //PLine l = new PLine(mouseX, mouseY, space);
      setPixel(mouseX/space, mouseY/space, LEDon);
      drawing = true;
      click1 = false;
    }
    else{
      x1Click = mouseX/space;
      y1Click = mouseY/space;
      lineOn = false;
      click1 = true;
      drawing = false;
      setLine(x0Click, y0Click, x1Click, y1Click, LEDon);
    }
  }
  else if(circleOn){
    if(click1){
      Circle c = new Circle(mouseX, mouseY, fillCircle, space);
      circles.add(c);
      drawing = true;
      click1 = false;
    }
    else{
      x1Click = mouseX;
      y1Click = mouseY;
      circleOn = false;
      click1 = true;
      drawing = false;
      setCircle(LEDon);
    }
  }
  
  else{
    if(LEDPixels[x][y] == 1){
      LEDPixels[x][y] = 0;
    }
    else{
      LEDPixels[x][y] = 1;
    }
  }
}

///////////////////////////////////////////////
////////////////////////////////////KEYS/////////////////////
///////////////////////////////////////////////////////
void keyPressed(){
  if(key == 'i'){
    label = !label;
  }
  
  if(drawing == false){
    if(key == 'o'){
      if(LEDon == 1){
        LEDon = 0;
      }
      else{
        LEDon = 1;
      }
    }
    else if(key == 'l'){
      lineOn = true;
      click1 = true;
      drawing = true;
    }
    else if(key == 'c'){
      circleOn = true;
      click1 = true;
      drawing = true;
    }
    else if(key == 'f'){
      fillCircle = ! fillCircle;
    }
  }
}


void setLine(int x0, int y0, int x1, int y1, int on){
  //int x0 = x0T/space;
 // int y0 = y0T/space;
  //int x1 = x1T/space;
  //int y1 = y1T/space;
 boolean steep = abs(y1 - y0) > abs(x1 - x0);
  if (steep) {
    int xtemp0 = y0;
    int xtemp1 = y1;
    y0 = x0;
    y1 = x1;
    x0 = xtemp0;
    x1 = xtemp1;
  }

  if (x0 > x1) {
    int xtemp0 = x0;
    int ytemp0 = y0;
    x0 = x1;
    y0 = y1;
    x1 = xtemp0;
    y1 = ytemp0;
  }

  int dx, dy;
  dx = x1 - x0;
  dy = abs(y1 - y0);

  int err = dx / 2;
  int ystep;

  if (y0 < y1) {
    ystep = 1;
  } 
  else {
    ystep = -1;
  }
  for (; x0<=x1; x0++) {
    if (steep) {
      setPixel(y0, x0, on);
    } else {
      setPixel(x0, y0, on);
    }
    err -= dy;
    if (err < 0) {
      y0 += ystep;
      err += dx;
    }
  }
}


void setPixel(int x, int y, int on){
  LEDPixels[x][y] = on;
}

void setCircle(int on){
  for(int x = 0; x < wLEDs; x++){
    for(int y = 0; y < hLEDs; y++){
      if(circles.getLast().inCircle(x, y)){
        LEDPixels[x][y] = on;
      }
    }
  }
}

/*
void buttons(){
 int boxD = 55;
 int padX = 10;
 int padY = 20;
 
 
 rect((padX+boxD)+padX, h+padY, boxD, boxD);
 rect(2*(padX+boxD)+padX, h+padY, boxD, boxD);
 rect(3*(padX+boxD)+padX, h+padY, boxD, boxD);
 
 ellipseMode(CENTER);
 rectMode(CENTER);
 
 rectMode(CORNER);
 noFill();
 if(circleOn){
   fill(90,250,220);
 }
 rect(padX, h+padY, boxD, boxD);
 if(fillCircle){
   fill(255,0,0);
   stroke(255, 0, 0);
   ellipse(padX+boxD/2, h+boxD/2+padY, 40, 40);
 }
 else if(fillCircle == false){
   noFill();
   stroke(255, 0, 0);
   ellipse(padX+boxD/2, h+boxD/2+padY, 40, 40);
 }
 rect(3*(boxD)/2+2*padX, h+boxD/2+padY, 20, 20);
 line(2*boxD+2*padX+padX+10, h+boxD+padY-10, 3*boxD+2*padX+padX-10, h+padY+10);
 text("Fill", 3.5*boxD+3*padX, h+boxD/2+padY+5);
}
 */


 
 

