#include <Wire.h>
#include "Adafruit_16x16matrix.h"
#include "Adafruit_GFX.h"

Adafruit_16x16matrix matrix = Adafruit_16x16matrix();
int buttonLED1 = 4;
int buttonLED2 = 5;
int buttonPin1 = 2;
int buttonPin2 = 3;
int scrollDelay = 50;
int blinkTime = 200;
double lastTime = 0;

boolean blinkOn = false;
boolean leftOn = false;
boolean rightOn = false;
boolean ledsOn = false;

static const uint8_t PROGMEM
  blinky_bmp[] = { 
    B11111000, B00011111, 
    B11100110, B01100111, 
    B11001111, B11110011, 
    B10000110, B01100001, 
    B10001100, B00110001, 
    B01111110, B01111110, 
    B01110011, B11001110, 
    B01100001, B10000110, 
    B00110011, B11001100, 
    B00011111, B11111000, 
    B00100000, B00000100, 
    B10001101, B10110001, 
    B11011101, B10111011, 
    B11011111, B11111011, 
    B11101111, B11110111, 
    B11110000, B00001111
};

void setup() {
  Serial.begin(9600);
  Serial.println("16x16 LED Matrix Test");
  pinMode(buttonLED1, OUTPUT);
  pinMode(buttonLED2, OUTPUT); 
  pinMode(buttonPin1, INPUT_PULLUP); 
  pinMode(buttonPin2, INPUT_PULLUP); 
  
  matrix.begin(0x71, 0x70);  // pass in the addresses
  matrix.setBrightness(3);
  blinkyOff();
}

void loop() {
  
  checkButtons();
  loopBlinky();
  
  // CUSTOM BLINKY b/c of timing
  // interrupt turning or blinky if there's a change
  
}

void checkButtons() {
  setButtonState();
  setButtons();
}

void setButtons() {
  if(leftOn && rightOn) {
    digitalWrite(buttonLED1, HIGH);
    digitalWrite(buttonLED2, HIGH);
    blinkOn = true;
  }
  else if (leftOn && !rightOn) {
    digitalWrite(buttonLED1, HIGH);
    digitalWrite(buttonLED2, LOW);
    leftArrow();
  }
  else if (!leftOn && rightOn) {
    digitalWrite(buttonLED1, LOW);
    digitalWrite(buttonLED2, HIGH);
    rightArrow();
  }
  else {
    matrix.clear();
    matrix.writeDisplay();
    resetButtons();
  }
}

boolean checkChangeState() {
  if(leftOn == digitalRead(buttonPin1) || rightOn == digitalRead(buttonPin2)) return true;
  return false;
}

void setButtonState() {
  if(leftOn == digitalRead(buttonPin1)) {
    delay(1);
    leftOn = !digitalRead(buttonPin1);
  }
  else if (rightOn == digitalRead(buttonPin2)) {
    delay(1);
    rightOn = !digitalRead(buttonPin2);
  }
}

void resetButtons() {
  digitalWrite(buttonLED1, LOW);
  digitalWrite(buttonLED2, LOW);
  blinkOn = false;
}

/*
void checkButtons() {
  if(!digitalRead(buttonPin1) && !digitalRead(buttonPin2)) {
    if(!blinkyOn) {
      blinkyOn();
    }
  }
  else if(!digitalRead(buttonPin1)) {
    digitalWrite(buttonLED1, HIGH);
    leftArrow();
  }
  else if(!digitalRead(buttonPin2)) {
    digitalWrite(buttonLED2, HIGH);
    rightArrow();
  }
  else {
    digitalWrite(buttonLED1, LOW);
    digitalWrite(buttonLED2, LOW);    
    matrix.clear();
    matrix.writeDisplay();
    if(blinkyOn) {
      blinkyOff();
    }
  }
}
*/
    
void leftArrow() {
  matrix.setTextSize(2);
  matrix.setTextWrap(false);  
  matrix.setTextColor(LED_ON);
  for (int8_t x=0; x>=-24; x--) {
    matrix.clear();
    if(checkChangeState()) break;
    matrix.setCursor(x,1);
    matrix.print("<<<<");
    matrix.writeDisplay();
    
    delay(scrollDelay);
  }
}

void rightArrow() {
  matrix.setTextSize(2);
  matrix.setTextWrap(false);  
  matrix.setTextColor(LED_ON);
  for (int8_t x=-24; x<=0; x++) {
    if(checkChangeState()) break;
    matrix.clear();
    matrix.setCursor(x,1);
    matrix.print(">>>>");
    matrix.writeDisplay();
    delay(scrollDelay);
  }
}

void blinkyOn() {
  //matrix.blinkRate(1);
  matrix.clear();
  matrix.drawBitmap(0, 0, blinky_bmp, 16, 16, LED_ON);
  matrix.writeDisplay();
}

void blinkyOff() {
  //matrix.blinkRate(0);
  matrix.clear();
  matrix.writeDisplay();
  blinkOn = false;
}

void loopBlinky() {
  if(blinkOn) {
    if(millis() - lastTime > blinkTime) {
      lastTime = millis();
      ledsOn = !ledsOn;
      if(ledsOn) blinkyOn();
      else blinkyOff();
    }
  }
}
