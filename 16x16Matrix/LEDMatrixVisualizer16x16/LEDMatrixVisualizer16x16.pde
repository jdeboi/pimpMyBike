/*
Jenna deBoisblanc
 July, 2012
 Shout out to Adafruit Industries
 
 This LED Visualizer makes it easy to design patterns for use with the 
 2, 16x16 LED Matrix Backpacks, which is produced by Adafruit Industries
 
 Once your design is complete, you can export the pixel values to a text 
 file or import previous designs (edit the file paths at the top of the sketch).  
 The print button allows you to generate a bitmap of the LED values (either 1 or 
 0). If you're using the Arduino bike circuit code, you can copy/paste the LED 
 values into the brake light or turning indicator LED pixel arrays.
 
 All of the shapes are stored in linked lists.  At some point, it'd be nice 
 to write functions to animate individual shape objects.
 */

import java.util.*;
////////////////////////////////////////////////////////////////////////////////////
/////////modify these variables/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
/*
Make sure that the import file name is different from the export file 
 before the sketch is run; otherwise, the former will be wiped in the setup().
 To create new export files while the sketch is running (instead of overwriting
 the same file each time), follow the instructions below in the savesFrame()
 function.
 */
String saveFile = "files/saved.txt";
String openFile = "files/open.txt";
String uploadImage = "images/mushroom.jpg";
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
int wLEDs = 16;
int hLEDs = 16;
int numLEDs = wLEDs * hLEDs;
int circleD = 14;
int padding = 3;
int space = circleD + 2 * padding;
int w = wLEDs*space;
int h = hLEDs*space;
int exportCounter;
PrintWriter output;
String[] input;
boolean drawing;
boolean click1;
boolean lineOn;
boolean circleOn;
boolean rectOn;
boolean fillOn = false;
boolean LEDOn = true;
boolean label;
char [][] LEDPixels;
LinkedList<LEDCircle> LEDCircles = new LinkedList<LEDCircle>();
LinkedList<LEDLine> LEDLines = new LinkedList<LEDLine>();
LinkedList<LEDRect> LEDRects = new LinkedList<LEDRect>();
int matrixpad = 50;
int spacing = (w+matrixpad*2)/12/11;
int groupSpacing = 0;
int vertSpacing = 10;
int buttonWidth = (w+matrixpad*2)/12;
int buttonHeight = buttonWidth +10;
int bgColor = 60;
int windowWidth = w+matrixpad*2;
int windowHeight = h+buttonWidth+3*vertSpacing;
PImage img;

//buttons
ImageButtons saveButton;
ImageButtons openButton;
ImageButtons uploadButton;
ImageButtons printButton;
ImageButtons fillButton;
ImageButtons ledButton;
ImageButtons labelButton;
ImageButtons circleButton;
ImageButtons rectButton;
ImageButtons lineButton;
ImageButtons clearButton;

///////////////////////////////////////////////
/////////////////////////////SETUP//////////////////////////
///////////////////////////////////////////////////////
void setup() {

  size(800, 800);
  LEDPixels = new char[wLEDs][hLEDs];
  output = createWriter("frames.txt");

  /////////////button details//////////////////////
  int ht = h+vertSpacing;
  int xCoord = buttonWidth+spacing;
  color bColor = color(201, 240, 208);
  color hColor = color(201, 240, 208);
  color pColor = color(181, 220, 188);

  ///////save buttons///////////////
  // upload
  PImage b = loadImage("icons/upload.png");
  PImage r = b;
  PImage d = b;
  uploadButton = new ImageButtons(groupSpacing, ht, buttonWidth, 
    buttonHeight, b, r, d, bColor, hColor, pColor, " Upload", false);
  //open
  b = loadImage("icons/open.png");
  r = loadImage("icons/open.png");
  d = loadImage("icons/open.png");
  openButton = new ImageButtons(xCoord+groupSpacing, ht, 
    buttonWidth, buttonHeight, b, r, d, bColor, hColor, pColor, " Open", false);  
  // save
  b = loadImage("icons/save.png");
  r = loadImage("icons/save.png");
  d = loadImage("icons/save.png");
  saveButton = new ImageButtons(xCoord*2+groupSpacing, ht, buttonWidth, 
    buttonHeight, b, r, d, bColor, hColor, pColor, " Save", false);
  //print
  b = loadImage("icons/print.png");
  r = loadImage("icons/print.png");
  d = loadImage("icons/print.png");
  printButton = new ImageButtons(xCoord*3+groupSpacing, ht, 
    buttonWidth, buttonHeight, b, r, d, bColor, hColor, pColor, " Print", false);

  ////////on/off buttons////////////
  bColor = color(243, 247, 192);
  hColor = color(243, 247, 192);
  pColor = color(223, 227, 172);  
  //LED
  b = loadImage("icons/light.png");
  r = loadImage("icons/light.png");
  d = loadImage("icons/light.png");
  ledButton = new ImageButtons(xCoord*4+groupSpacing*2, ht, 
    buttonWidth, buttonHeight, b, r, d, bColor, hColor, pColor, "On/Off", true);
  //fill
  b = loadImage("icons/pencil.png");
  r = loadImage("icons/pencil.png");
  d = loadImage("icons/pencil.png");
  fillButton = new ImageButtons(xCoord*5+groupSpacing*2, ht, 
    buttonWidth, buttonHeight, b, r, d, bColor, hColor, pColor, "  Fill", false);
  //labels
  b = loadImage("icons/tag.png");
  r = loadImage("icons/tag.png");
  d = loadImage("icons/tag.png");
  labelButton = new ImageButtons(xCoord*6+groupSpacing*2, ht, 
    buttonWidth, buttonHeight, b, r, d, bColor, hColor, pColor, "Labels", false);

  ////////draw buttons//////////////
  bColor = color(227, 250, 247); 
  hColor = color(227, 250, 247);
  pColor = color(207, 230, 227); 
  //circle button
  circleButton = new ImageButtons(xCoord*7+groupSpacing*3, ht, 
    buttonWidth, buttonHeight, bColor, hColor, pColor, "Circle", false); 
  //rect button
  rectButton = new ImageButtons(xCoord*8+groupSpacing*3, ht, 
    buttonWidth, buttonHeight, bColor, hColor, pColor, "Rect", false); 
  //line button
  lineButton = new ImageButtons(xCoord*9+groupSpacing*3, ht, 
    buttonWidth, buttonHeight, bColor, hColor, pColor, "Line", false); 
  //clear button
  bColor = color(240); 
  hColor = color(240); 
  pColor = color(220); 
  b = loadImage("icons/eraser.png");
  clearButton = new ImageButtons(xCoord*10+groupSpacing*4, ht, 
    buttonWidth, buttonHeight, b, b, b, bColor, hColor, pColor, "Clear", false);
}

///////////////////////////////////////////////
/////////////////////////////DRAW//////////////////////////
///////////////////////////////////////////////////////
void draw() {
  strokeWeight(0);
  background(bgColor+25);
  stroke(0);
  strokeWeight(2);
  fill(bgColor);
  rect(matrixpad, 0, w, h);
  ellipseMode(CORNER);
  stroke(0);

  displayButtons(); 

  //write the stored pixels to the visualizer///////////
  for (int i = 0; i < wLEDs; i ++) {
    for (int j = 0; j < hLEDs; j++) {
      stroke(0);
      fill(255);
      if (LEDPixels[i][j] == '1') {
        fill(255, 0, 0);
      }
      ellipse(i*space+padding+matrixpad, j*space+padding, circleD, circleD);
    }
  }

  //set pixels if currently drawing//////////////////
  if (drawing && click1 == false) {
    if (lineOn) {
      LEDLines.getLast().setLineCursor(mouseX, mouseY, LEDOn);
      LEDLines.getLast().drawLine();
    } else if (circleOn) {
      LEDCircles.getLast().setCircleCursor(mouseX-matrixpad, mouseY, fillOn, LEDOn);
      LEDCircles.getLast().drawCircle();
    } else if (rectOn) {
      LEDRects.getLast().setRectCursor(mouseX-matrixpad, mouseY, fillOn, LEDOn);
      LEDRects.getLast().drawRect();
    }
  }

  //Aesthetic Parts of Matrix////////////////////////
  //draw the matrix lines
  stroke(0);
  strokeWeight(2);
  fill(0);
  line(w/2+matrixpad, 0, w/2+matrixpad, h);
  line(matrixpad, h/2, w+matrixpad, h/2);

  strokeWeight(1);
  //draw pixel labels if labels are on
  if (label == true && mouseY < h) {
    String pixelLoc = ("x: " + (mouseX-matrixpad)/space + ", y: " + mouseY/space);
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
  if (mouseY< h && mouseX < w+matrixpad && mouseX > matrixpad) {
    int x = (mouseX-matrixpad)/space;
    int y = (mouseY)/space;
    if (lineOn) {
      if (click1) {
        LEDLine l = new LEDLine(mouseX, mouseY);
        LEDLines.add(l);
        drawing = true;
        click1 = false;
      } else {
        lineOn = false;
        drawing = false;
        click1 = true;
        lineButton.pressed();
        setShape(LEDLines.getLast().getLine());
      }
    } else if (circleOn) {
      if (click1) {
        LEDCircle c = new LEDCircle(mouseX-matrixpad, mouseY);
        LEDCircles.add(c);
        drawing = true;
        click1 = false;
      } else {
        circleOn = false;
        drawing = false;
        click1 = true;
        circleButton.pressed();
        setShape(LEDCircles.getLast().getCircle());
      }
    } else if (rectOn) {
      if (click1) {
        LEDRect r = new LEDRect(mouseX-matrixpad, mouseY);
        LEDRects.add(r);
        drawing = true;
        click1 = false;
      } else {
        rectOn = false;
        drawing = false;
        click1 = true;
        rectButton.pressed();
        setShape(LEDRects.getLast().getRect());
      }
    } else {
      if (LEDPixels[x][y] == '1') {
        LEDPixels[x][y] = '0';
      } else {
        LEDPixels[x][y] = '1';
      }
    }
  } else {
    checkButtons();
  }
}

///////////////////////////////////////////////
//////////////////////////////KEY PRESSED///////////////////////
///////////////////////////////////////////////////////
void keyPressed() {
  if (drawing == false) {
    if (key == 'c') {
      clearAll();
    } else if (key == 'l') {
      lineOn = true;
      circleOn = false;
      rectOn = false;
      click1 = true;
      lineButton.pressed();
      rectButton.reset();
      circleButton.reset();
    } else if (key == 'c') {
      circleOn = true;
      lineOn = false;
      rectOn = false;
      click1 = true;
      circleButton.pressed();
      rectButton.reset();
      lineButton.reset();
    } else if (key == 's') {
      savesFrame();
    } else if (key == 'p') {
      printFrame();
    } else if (key == 'i') {
      openFrame();
    } else if (key == 'r') {
      rectOn = true;
      circleOn = false;
      lineOn = false;
      click1 = true;
      rectButton.pressed();
      lineButton.reset();
      circleButton.reset();
    }
  }
}

///////////////////////////////////////////////
//////////////////////////////SET FUNCTIONS/////////////////////
///////////////////////////////////////////////////////

void setPixel(int x, int y, char on) {
  LEDPixels[x][y] = on;
}

void setShape(int [] shapePoints) {
  for (int i = 0; i < shapePoints.length; i=i+2) {
    int x = shapePoints[i];
    int y = shapePoints[i+1];
    if (LEDOn) {
      LEDPixels[x][y] = '1';
    } else {
      LEDPixels[x][y] = '0';
    }
  }
}

///////////////////////////////////////////////////////
///////////////////////////////UPLOAD/OPEN/SAVE/PRINT///////////
///////////////////////////////////////////////////////

void savesFrame() {
  exportCounter++;
  String[] lines = new String[hLEDs];
  for (int y = 0; y < hLEDs; y++) {
    String values = "";
    for (int x = 0; x < wLEDs; x++) {
      values += LEDPixels[x][y] + "\\s";
    }
    values += LEDPixels[wLEDs-1][y]; 
    lines[y] = values;
  } 
  //To create new files instead of overwriting use the line below
  //saveStrings("frames" + exportCounter + ".txt", lines);
  saveStrings(saveFile, lines);
  println("Matrix design saved: " + saveFile);
}

void openFrame() {
  //specify a different text file to import other frames
  input = loadStrings(openFile);
  for (int i = 0; i < hLEDs; i++) {
    String[] elements = split(input[i], "\\s");
    for (int j = 0; j < elements.length-1; j++) {
      LEDPixels[j][i] = elements[j].charAt(0);
    }
  }
}

//print function to create bytes[] of 0s and 1s
void printFrame() {
  println();
  println("-------------NEW IMAGE-------------");
  print("{ ");
  for (int i = 0; i < hLEDs; i++) {
    // first byte (left to right)
    for (int j = 0; j < 8; j++) {
      if (j == 0 ) print("B"); 
      print(getLED(j, i));
      if (j == 7) print(", ");
    }
    // second byte (left to right)
    for (int j = 8; j < 16; j++) {
      if (j == 8) {
        print("B"); 
         print(getLED(j, i));
      } else if (j == 15 && i == hLEDs-1) println(getLED(j, i));
      else if (j == 15) println(getLED(j, i) + ", ");
      else print(getLED(j, i));
    }
  }
  println("};");
}

String getLED(int j, int i) {
  if (LEDPixels[j][i] == 0) return "0";
  else return "1";
}

void printlnLED(int j, int i) {
  if (LEDPixels[j][i] == 0) println("0");
  else println("1");
}

///////////////////////////////////////////////
//////////////////////////BUTTON FUNCTIONS///////////////////
///////////////////////////////////////////////////////
void displayButtons() {
  //update and draw buttons
  fill(220);
  strokeWeight(1);
  rect(0, h, windowWidth, windowHeight - h); 
  uploadButton.display();
  printButton.display();
  openButton.display();
  openButton.update();
  saveButton.display();
  fillButton.display();
  ledButton.display();
  labelButton.display();
  circleButton.display();
  rectButton.display();
  lineButton.display();
  circleButton.display();
  clearButton.display();

  printButton.update();
  uploadButton.update();
  fillButton.update();
  saveButton.update();
  ledButton.update();
  labelButton.update();
  circleButton.update();
  rectButton.update();
  lineButton.update();
  clearButton.update();
}

void checkButtons() {
  if (fillButton.overRect()) {
    fillButton.pressed();
    fillOn = ! fillOn;
    circleButton.switchFilled();
    rectButton.switchFilled();
  } else if (ledButton.overRect()) {
    ledButton.pressed();
    LEDOn = ! LEDOn;
    circleButton.switchOn();
    rectButton.switchOn();
    lineButton.switchOn();
  } else if (labelButton.overRect()) {
    labelButton.pressed();
    label = !label;
  }
  if (drawing == false) { 
    if (saveButton.overRect()) {
      savesFrame();
    } else if (openButton.overRect()) {
      openFrame();
    } else if (uploadButton.overRect()) {
      uploadImage();
    } else if (printButton.overRect()) {
      printFrame();
    } else if (clearButton.overRect()) {
      clearAll();
    } else if (lineButton.overRect()) {
      lineOn = true;
      circleOn = false;
      rectOn = false;
      click1 = true;
      lineButton.pressed();
      rectButton.reset();
      circleButton.reset();
    } else if (circleButton.overRect()) {
      circleOn = true;
      lineOn = false;
      rectOn = false;
      click1 = true;
      circleButton.pressed();
      rectButton.reset();
      lineButton.reset();
    } else if (rectButton.overRect()) {
      rectOn = true;
      circleOn = false;
      lineOn = false;
      click1 = true;
      rectButton.pressed();
      lineButton.reset();
      circleButton.reset();
    }
  }
}

void clearAll() {
  lineButton.reset();
  circleButton.reset();
  rectButton.reset();
  lineOn = false;
  circleOn = false;
  rectOn = false;
  for (int i=0; i < wLEDs; i++) {
    for (int j=0; j< hLEDs; j++) {
      LEDPixels[i][j] = '0';
    }
  }
}

void uploadImage() {
  println("uploading image");
  img = loadImage(uploadImage);
  img.loadPixels();
  if (img.width == wLEDs && img.height == hLEDs) {
    for (int i = 0; i < wLEDs; i++) {
      for (int j = 0; j < hLEDs; j++) {
        float red=red(img.pixels[i*wLEDs + j]);
        float green=green(img.pixels[i*wLEDs + j]);
        float blue=blue(img.pixels[i*wLEDs + j]);
        if ((red + green + blue) / 3 > 100) LEDPixels[j][i] = '1';
        else LEDPixels[j][i] = '0';
      }
    }
  } else println ("must a be "+wLEDs+"x"+hLEDs+" image");
}
