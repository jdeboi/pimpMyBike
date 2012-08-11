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
int spacing = w/numMatrices/10/14;
int groupSpacing = spacing*3;
int vertSpacing = 10;
int buttonWidth = w/numMatrices/10;
int bgColor = 220;
int windowWidth = w;
int windowHeight = h+buttonWidth+2*vertSpacing;

//buttons
ImageButtons exportButton;
ImageButtons importButton;
ImageButtons printButton;
ImageButtons fillButton;
ImageButtons ledButton;
ImageButtons labelButton;
ImageButtons circleButton;
ImageButtons rectButton;
ImageButtons lineButton;

///////////////////////////////////////////////
/////////////////////////////SETUP//////////////////////////
///////////////////////////////////////////////////////
void setup(){
  size(windowWidth, windowHeight);
  LEDPixels = new int[wLEDs][hLEDs];
  LEDPixels = new int[wLEDs][hLEDs];
  output = createWriter("frames.txt");
  
  /////////////button details//////////////////////
  int ht = h+vertSpacing;
  int xCoord = buttonWidth+spacing;
  color bColor = color(201, 240, 208);
  color hColor = color(250);
  color pColor = color(80);
  
  ///////save buttons///////////////
  //export
  PImage b = loadImage("icons/save.png");
  PImage r = loadImage("icons/save.png");
  PImage d = loadImage("icons/save.png");
  exportButton = new ImageButtons(groupSpacing, ht, buttonWidth, 
    buttonWidth, b, r, d, bColor, hColor, pColor, "Save", false);
  //import
  b = loadImage("icons/open.png");
  r = loadImage("icons/open.png");
  d = loadImage("icons/open.png");
  importButton = new ImageButtons(xCoord+groupSpacing, ht, 
    buttonWidth, buttonWidth, b, r, d, bColor, hColor, pColor, "Import", false);
  //print
  b = loadImage("icons/print.png");
  r = loadImage("icons/print.png");
  d = loadImage("icons/print.png");
  printButton = new ImageButtons(xCoord*2+groupSpacing, ht, 
    buttonWidth, buttonWidth, b, r, d, bColor, hColor, pColor, "Print", false);

  ////////on/off buttons////////////
  bColor = color(243, 247, 192);
  pColor = color(245, 136, 143);  
  //LED
  b = loadImage("icons/light.png");
  r = loadImage("icons/light.png");
  d = loadImage("icons/light.png");
  ledButton = new ImageButtons(xCoord*3+groupSpacing*2, ht, 
    buttonWidth, buttonWidth, b, r, d, bColor, hColor, pColor, "On/Off", true);
  //fill
  b = loadImage("icons/pencil.png");
  r = loadImage("icons/pencil.png");
  d = loadImage("icons/pencil.png");
  fillButton = new ImageButtons(xCoord*4+groupSpacing*2, ht, 
    buttonWidth, buttonWidth, b, r, d, bColor, hColor, pColor, "Fill", false);
  //labels
  b = loadImage("icons/tag.png");
  r = loadImage("icons/tag.png");
  d = loadImage("icons/tag.png");
  labelButton = new ImageButtons(xCoord*5+groupSpacing*2, ht, 
    buttonWidth, buttonWidth, b, r, d, bColor, hColor, pColor, "Labels", false);
    
  ////////draw buttons//////////////
  bColor = color(227, 250, 247); 
  //circle button
  circleButton = new ImageButtons(xCoord*6+groupSpacing*3, ht, 
    buttonWidth, buttonWidth, bColor, hColor, pColor, "Circle", false); 
  //rect button
  rectButton = new ImageButtons(xCoord*7+groupSpacing*3, ht, 
    buttonWidth, buttonWidth, bColor, hColor, pColor, "Rect", false); 
  //line button
  lineButton = new ImageButtons(xCoord*8+groupSpacing*3, ht, 
    buttonWidth, buttonWidth, bColor, hColor, pColor, "Line", false); 
}

///////////////////////////////////////////////
/////////////////////////////DRAW//////////////////////////
///////////////////////////////////////////////////////
void draw(){
  background(bgColor);
  ellipseMode(CORNER);
  stroke(0);
  
  displayButtons(); 
  
  //write the stored pixels to the visualizer///////////
  for(int i = 0; i < wLEDs; i ++){
    for(int j = 0; j < hLEDs; j++){
      stroke(0);
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
  stroke(0);
  strokeWeight(2);
  fill(0);
  line(0, h/2, w, h/2);
  line(0, h, w, h);
  for(int i = 1; i < numMatrices*3; i++){
    line(i*w/(3*numMatrices), 0, i*w/(3*numMatrices), h);
  }
  strokeWeight(1);
  //draw pixel labels if labels are on
  if(label == true && mouseY < h){
    String pixelLoc = ("x: " + mouseX/space + ", y: " + mouseY/space);
    fill(255, 255, 255, 210);
    rectMode(CORNER);
    noStroke();
    rect(mouseX-4, mouseY-14, 80, 18);
    fill(0);
    text(pixelLoc, mouseX, mouseY);
  } 
}



///////////////////////////////////////////////
/////////////////////////////MOUSE PRESSED////////////////////
///////////////////////////////////////////////////////
void mousePressed() {
  if(mouseY< h){
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
  else{
    checkButtons();
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
///////////////////////////////IMPORT/EXPORT/PRINT///////////
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

///////////////////////////////////////////////
//////////////////////////BUTTON FUNCTIONS///////////////////
///////////////////////////////////////////////////////
void displayButtons(){
  //update and draw buttons
  exportButton.update();
  exportButton.display();
  importButton.update();
  importButton.display();
  printButton.update();
  printButton.display();
  fillButton.update();
  fillButton.display();
  ledButton.update();
  ledButton.display();
  labelButton.update();
  labelButton.display();
  circleButton.update();
  circleButton.display();
  rectButton.update();
  rectButton.display();
  lineButton.update();
  lineButton.display();
}

void checkButtons(){
  if(exportButton.overRect()){
    exportFrame();
  }
  else if(importButton.overRect()){
    importFrame();
  }
  else if(fillButton.overRect()){
    fillButton.pressed();
    fillOn = ! fillOn;
    circleButton.switchFilled();
    rectButton.switchFilled();
  }
  else if(ledButton.overRect()){
    ledButton.pressed();
    LEDOn = ! LEDOn;
    circleButton.switchOn();
    rectButton.switchOn();
    lineButton.switchOn();
  }
  else if(printButton.overRect()){
    printFrame();
  }
  else if(labelButton.overRect()){
    labelButton.pressed();
    label = !label;
  }
  if(drawing == false){ 
    if(lineButton.overRect()){
      lineOn = true;
      click1 = true;
      drawing = true;
      lineButton.pressed();
    }
    else if(circleButton.overRect()){
      circleOn = true;
      click1 = true;
      drawing = true;
      circleButton.pressed();
    }
    else if(rectButton.overRect()){
      rectOn = true;
      click1 = true;
      drawing = true;
      rectButton.pressed();
    }
  }
}







