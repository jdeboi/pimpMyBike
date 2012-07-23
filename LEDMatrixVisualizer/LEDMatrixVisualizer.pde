int numMatrices = 2;
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
boolean click1;
boolean lineOn;
boolean circleOn;
boolean rectOn;
boolean fillOn = false;
boolean LEDOn = true;
int [][] LEDPixels;
LinkedList<LEDCircle> LEDCircles = new LinkedList<LEDCircle>();
LinkedList<LEDLine> LEDLines = new LinkedList<LEDLine>();
LinkedList<LEDRect> LEDRects = new LinkedList<LEDRect>();

///////////////////////////////////////////////
/////////////////////////////SETUP//////////////////////////
///////////////////////////////////////////////////////
void setup(){
  size(w, h+100);
  LEDPixels = new int[wLEDs][hLEDs];
}

///////////////////////////////////////////////
/////////////////////////////DRAW//////////////////////////
///////////////////////////////////////////////////////
void draw(){
  background(220);
  ellipseMode(CORNER);
  stroke(0);
   
  ///////////write the stored pixels to the visualizer///////////
  for(int i = 0; i < wLEDs; i ++){
    for(int j = 0; j < hLEDs; j++){
      fill(0, 0, 0);
      if(LEDPixels[i][j] == 1){
        fill(255, 0, 0);
      }
      ellipse(i*space+padding, j*space+padding, circleD, circleD);
    }
  }
  
  /////////////set pixels if currently drawing//////////////////
  if(drawing && click1 == false){
    if(lineOn){
      LEDLines.getLast().setLineCursor(mouseX, mouseY);
      LEDLines.getLast().drawLine();
    }
    else if(circleOn){
      LEDCircles.getLast().setCircleCursor(mouseX, mouseY);
      LEDCircles.getLast().drawCircle();
    }
    else if(rectOn){
      LEDRects.getLast().setRectCursor(mouseX, mouseY);
      LEDRects.getLast().drawRect();
    }
  }
  
  /////////////////////////Aesthetic Parts of Matrix/////////////
  //draw the matrix lines
  fill(0);
  line(0, h/2, w, h/2);
  line(0, h, w, h);
  for(int i = 1; i < numMatrices*3; i++){
    line(i*w/(3*numMatrices), 0, i*w/(3*numMatrices), h);
  }
  //draw pixel labels if labels are on
  if(label == true){
    String pixelLoc = ("x: " + mouseX/space + ", y: " + mouseY/space);
    fill(0, 0, 0, 170);
    rectMode(CORNER);
    noStroke();
    rect(mouseX-4, mouseY-12, 80, 18);
    fill(0, 255, 0);
    text(pixelLoc, mouseX, mouseY);
  } 
  //draw text
  text("C: draw circle", 20, h+20);
  text("F: toggle fill", 20, h+40);
  text("L: draw line", 20, h+60);
  text("O: toggle LED on/off", 20, h+80);
}



///////////////////////////////////////////////
/////////////////////////////MOUSE PRESSED////////////////////
///////////////////////////////////////////////////////
void mousePressed() {
  int x = mouseX/space;
  int y = mouseY/space;
  if(lineOn){
    if(click1){
      LEDLine l = new LEDLine(mouseX, mouseY, LEDOn);
      LEDLines.add(l);
      drawing = true;
      click1 = false;
      setShape(LEDLines.getLast().getLine());
    }
    else{
      lineOn = false;
      drawing = false;
      click1 = true;
    }
  }
  else if(circleOn){
    if(click1){
      LEDCircle c = new LEDCircle(mouseX, mouseY, fillOn, LEDOn);
      LEDCircles.add(c);
      drawing = true;
      click1 = false;
    }
    else{
      circleOn = false;
      drawing = false;
      click1 = true;
      setShape(LEDCircles.getLast().getCircle());
    }
  }
  else if(rectOn){
    if(click1){
      LEDRect r = new LEDRect(mouseX, mouseY, fillOn, LEDOn);
      LEDRects.add(r);
      drawing = true;
      click1 = false;
    }
    else{
      rectOn = false;
      drawing = false;
      click1 = true;
      setShape(LEDRects.getLast().getRect());
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
      LEDOn =! LEDOn;
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
    else if(key == 'c'){
      circleOn = true;
      click1 = true;
      drawing = true;
    }
    else if(key == 'r'){
      rectOn = true;
      click1 = true;
      drawing = true;
    }
    else if(key == 'f'){
      fillOn = ! fillOn;
    }
  }
}


void setPixel(int x, int y, int on){
  LEDPixels[x][y] = on;
}

void setShape(int [] shapePoints){
  for(int i = 0; i < shapePoints.length; i=i+2){
   int x = shapePoints[i];
   int y = shapePoints[i+1];
   if(LEDOn){
     LEDPixels[x][y] = 1;
   }
   else{
     LEDPixels[x][y] = 0;
   }
  }
}



 
 

