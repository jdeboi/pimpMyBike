char rightArrow [] = 
  "100000001000000010000000"
  "010000000100000001000000"
  "001000000010000000100000"
  "000100000001000000010000"
  "000010000000100000001000"
  "000001000000010000000100"
  "000000100000001000000010"
  "000000010000000100000001"
  "000000010000000100000001"
  "000000100000001000000010"
  "000001000000010000000100"
  "000010000000100000001000"
  "000100000001000000010000"
  "001000000010000000100000"
  "010000000100000001000000"
  "100000001000000010000000";

char leftArrow [] = 
  "000000010000000100000001"
  "000000100000001000000010"
  "000001000000010000000100"
  "000010000000100000001000"
  "000100000001000000010000"
  "001000000010000000100000"
  "010000000100000001000000"
  "100000001000000010000000"
  "100000001000000010000000"
  "010000000100000001000000"
  "001000000010000000100000"
  "000100000001000000010000"
  "000010000000100000001000"
  "000001000000010000000100"
  "000000100000001000000010"
  "000000010000000100000001";


void checkRightTurning(){
  right = digitalRead(turnRPin);
  if(right == HIGH && rightOld == LOW){
      rOn =! rOn;
      if(rOn && lOn){
        digitalWrite(turnRLED, HIGH);
        stepUp = true;
        state = 4;
      }
      else if(rOn && lOn == false){
        digitalWrite(turnRLED, HIGH);
        stepUp = true;
        state = 1;
      }
      else if(rOn == false && lOn){
        digitalWrite(turnRLED, LOW);
        stepUp = false;
        //not going to happen because reset rOn and lOn when they're both HIGH
      }
      else if(rOn == false && lOn == false){
        digitalWrite(turnRLED, LOW);
        stepUp = false;
        state = 0;
      }
      setLEDShape();
  }
  rightOld = right;
}

void checkLeftTurning(){
  left = digitalRead(turnLPin);
  if(left == HIGH && leftOld == LOW){
     lOn =! lOn;
     if(rOn && lOn){
       stepUp = true;
       digitalWrite(turnLLED, HIGH);
       state = 4;
      }
      else if(rOn && lOn == false){
        stepUp = false;
        //not going to happen b/c reset values when they're both HIGH
      }
      else if(rOn == false && lOn){
        stepUp = true;
        digitalWrite(turnLLED, HIGH);
        state = 2;
      }
      else if(rOn == false && lOn == false){
        stepUp = false;
        digitalWrite(turnLLED, LOW);
        state = 0;
      }
      setLEDShape();
   }
   leftOld = left; 
}

void drawRight(){
 //blankScreen();
 for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, (rightArrow[j+i*24]-'0'));
    }    
 }
 matrix.writeScreen();
}

void drawLeft(){
  //blankScreen();
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j<24; j++) {
      matrix.drawPixel(j, i, (leftArrow[j+i*24]-'0'));
      
    }    
 }
 matrix.writeScreen();
}


