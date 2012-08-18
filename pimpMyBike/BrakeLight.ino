
char brakePixels [] =
  "000000000001100000000000"
  "000000000011110000000000"
  "000000000111111000000000"
  "000000001110011100000000"
  "000000011100001110000000"
  "000000111001100111000000"
  "000001110011110011100000"
  "000011100111111001110000"
  "000011100111111001110000"
  "000001110011110011100000"
  "000000111001100111000000"
  "000000011100001110000000"
  "000000001110011100000000"
  "000000000111111000000000"
  "000000000011110000000000"
  "000000000001100000000000";

void checkBraking(){
  brakeV = digitalRead(brakeVPin);
  if(brakeV == HIGH && brakeOld == LOW){
    brakeOn = true;
    drawBrake();
  }
  else if (brakeV == LOW && brakeOld == HIGH){
    brakeOn = false;
    stateChange = true;
    setTurning();
  }
  brakeOld = brakeV;
}

void drawBrake(){
  for(int i = 0; i < numLEDs; i++){
    matrix.drawPixel(i%width, i/24, (brakePixels[i]-'0'));
  }
  matrix.writeScreen();
}

