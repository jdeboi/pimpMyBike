/*
Jenna deBoisblanc
July, 2012
Shout out to Adafruit Industries

This LED Visualizer makes it easy to design patterns for use with the 
16x24 Red LED Matrix Panel - Chainable HT1632C Driver, which is produced 
by Adafruit Industries and available here: https://www.adafruit.com/products/555.

Once your design is complete, you can export the pixel values to a text file.

All of the shapes are stored in linked lists.  At some point, it'd be nice to write
functions to animate individal shape objects.
*/

//change this number if you're using more than one matrix
int numMatrices = 1;
int wLEDs = 24 * numMatrices;
int hLEDs = 16;
int circleD = 12;
int padding = 5;
int space = circleD + 2 * padding;
int w = wLEDs*space;
int h = hLEDs*space;
int x0Click;
int y0Click;
int x1Click;
int y1Click;
int xClick;
int yClick;
int exportCounter;
PrintWriter output;
String[] input;
boolean label;
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
  LEDPixels = new int[wLEDs][hLEDs];
  output = createWriter("frames.txt");
}

///////////////////////////////////////////////
/////////////////////////////DRAW//////////////////////////
///////////////////////////////////////////////////////
void draw(){
  background(220);
  ellipseMode(CORNER);
  stroke(0);
   
  //write the stored pixels to the visualizer///////////
  for(int i = 0; i < wLEDs; i ++){
    for(int j = 0; j < hLEDs; j++){
      fill(0, 0, 0);
      if(LEDPixels[i][j] == 1){
        fill(255, 0, 0);
      }
      ellipse(i*space+padding, j*space+padding, circleD, circleD);
    }
  }
  
  //set pixels if currently drawing//////////////////
  if(drawing && click1 == false){
    if(lineOn){
      LEDLines.getLast().setLineCursor(mouseX, mouseY, LEDOn);
      LEDLines.getLast().drawLine();
    }
    else if(circleOn){
      LEDCircles.getLast().setCircleCursor(mouseX, mouseY, fillOn, LEDOn);
      LEDCircles.getLast().drawCircle();
    }
    else if(rectOn){
      LEDRects.getLast().setRectCursor(mouseX, mouseY, fillOn, LEDOn);
      LEDRects.getLast().drawRect();
    }
  }
  
  //Aesthetic Parts of Matrix////////////////////////
  //draw the matrix lines
  strokeWeight(2);
  fill(0);
  line(0, h/2, w, h/2);
  line(0, h, w, h);
  for(int i = 1; i < numMatrices*3; i++){
    line(i*w/(3*numMatrices), 0, i*w/(3*numMatrices), h);
  }
  strokeWeight(1);
  //draw pixel labels if labels are on
  if(label == true){
    String pixelLoc = ("x: " + mouseX/space + ", y: " + mouseY/space);
    fill(0, 0, 0, 170);
    rectMode(CORNER);
    noStroke();
    rect(mouseX-4, mouseY-14, 80, 18);
    fill(0, 255, 0);
    text(pixelLoc, mouseX, mouseY);
  } 
  //draw text
  fill(0);
  if(circleOn){
    fill(255, 0, 0);
  }
  text("C: circle", 20, h+20);
  fill(0);
  if(rectOn){
    fill(255, 0, 0);
  }
  text("R: rectangle", 20, h+40);
  fill(0);
  if(lineOn){
    fill(255, 0, 0);
  }
  text("L: line", 20, h+60);
  fill(0);
  if(fillOn){
    fill(255, 0, 0);
  }
  text("F: fill ON/OFF", 120, h+20);
  fill(0);
  if(LEDOn){
    fill(255, 0, 0);
  }
  text("O: LEDs ON/OFF", 120, h+40);
  fill(0);
  if(label){
    fill(0, 0, 255);
  }
  text("N: labels ON/OFF", 120, h+60);
  fill(0);
  text("E: export frame", 250, h+20);
  text("I: import frame", 250, h+40);
  text("P: print frame", 250, h+60);
}



///////////////////////////////////////////////
/////////////////////////////MOUSE PRESSED////////////////////
///////////////////////////////////////////////////////
void mousePressed() {
  int x = mouseX/space;
  int y = mouseY/space;
  if(lineOn){
    if(click1){
      LEDLine l = new LEDLine(mouseX, mouseY);
      LEDLines.add(l);
      drawing = true;
      click1 = false;
    }
    else{
      lineOn = false;
      drawing = false;
      click1 = true;
      setShape(LEDLines.getLast().getLine());
    }
  }
  else if(circleOn){
    if(click1){
      LEDCircle c = new LEDCircle(mouseX, mouseY);
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
      LEDRect r = new LEDRect(mouseX, mouseY);
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
  if(key == 'n'){
    label = !label;
  }
  else if(key == 'f'){
    fillOn = ! fillOn;
  }
  else if(key == 'o'){
    LEDOn = ! LEDOn;
  }
  else if(key == 'e'){
    exportFrame();
  }
  else if(key == 'i'){
    importFrame();
  }
  else if(key == 'p'){
    printFrame();
  }
  else if(drawing == false){ 
    if(key == 'l'){
      lineOn = true;
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
  }
}

///////////////////////////////////////////////
//////////////////////////////SET FUNCTIONS/////////////////////
///////////////////////////////////////////////////////

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

///////////////////////////////////////////////
///////////////////////////////IMPORT/EXPORT/////////////////////
///////////////////////////////////////////////////////

void exportFrame(){
  exportCounter++;
  String[] lines = new String[hLEDs];
  for(int y = 0; y < hLEDs; y++){
    String values = "";
    for(int x = 0; x < wLEDs; x++){
        values += LEDPixels[x][y] + "\\s";
    }
    values += LEDPixels[wLEDs-1][y]; 
    lines[y] = values; 
  } 
  //To create new files instead of overwriting use the line below
  //saveStrings("frames" + exportCounter + ".txt", lines);
  saveStrings("frames.txt", lines);
}

void importFrame(){
  //specify a different text file to import other frames
  input = loadStrings("brakeLight.txt");
  for (int i = 0; i < hLEDs; i++) {
    String[] elements = split(input[i], "\\s");
    for(int j = 0; j < elements.length; j++){
      LEDPixels[j][i] = int(elements[j]);
    }
  }
}

void printFrame(){
  for (int i = 0; i < hLEDs; i++) {
    for(int j = 0; j < wLEDs; j++){
      if(i== hLEDs - 1 && j == wLEDs - 1){
        print(LEDPixels[j][i]);
      }
      else{
        print(LEDPixels[j][i] + ", ");
      }
    }
    println();
  }
}




