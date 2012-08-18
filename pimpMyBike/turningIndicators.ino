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

void checkTurning(){
  stateChange = false;
  right = digitalRead(turnRPin);
  left = digitalRead(turnLPin);
  if(right == HIGH && rightOld == LOW){
      rOn =! rOn;
      stateChange = true;
  }
  else if(left == HIGH && leftOld == LOW){
     lOn =! lOn;
     stateChange = true;
  }
  rightOld = right;
  leftOld = left;
}
     
void setTurning(){
  if(stateChange && brakeOn == false){  
    if(rOn && lOn){
      strobeOn =! strobeOn;
      //drawStrobe();
      /*
      *To do- figure out why drawStrobe() causes the entire
      *sketch to malfunction- stack overflow?
      *drawRight() is exactly the same and works fine
      *have to talk to someone who knows more about comp sci
      *or electronics than I do
      */
      matrix.clearScreen();
      delay(50);
      rOn = false;
      lOn = false;
      digitalWrite(turnRLED, LOW);
      digitalWrite(turnLLED, LOW);
      turningOn = false;
      turningROn = false;
      turningLOn = false;
    }
    else if(rOn && lOn == false){
      drawRight();
      digitalWrite(turnRLED, HIGH);
      turningOn = true;
      turningROn = true;
    }
    else if(rOn == false && lOn){
      drawLeft();
      digitalWrite(turnLLED, HIGH);
      turningOn = true;
      turningLOn = true;
    }
    else if(rOn == false && lOn == false){
      matrix.clearScreen();
      digitalWrite(turnRLED, LOW);
      digitalWrite(turnLLED, LOW);
      turningOn = false;
      turningROn = false;
      turningLOn = false;
    }
  }
}

void drawRight(){
 for(int i = 0; i < 16; i++) {
    for(int j = 0; j< 24; j++) {
      matrix.drawPixel(j, i, (rightArrow[j+i*24]-'0'));
      LEDs[j][i] = rightArrow[j+i*24];
    }    
 }
 matrix.writeScreen();
}

void drawLeft(){
  for(int i = 0; i < 16; i++) {
    for(int j = 0; j< 24; j++) {
      matrix.drawPixel(j, i, (leftArrow[j+i*24]-'0'));
      //LEDs[j+i*24] = leftArrow[j+i*24];
      LEDs[j][i] = leftArrow[j+i*24];
    }    
 }
 matrix.writeScreen();
}



