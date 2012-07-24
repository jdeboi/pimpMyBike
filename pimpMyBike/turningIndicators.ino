

void checkRightTurning(){
  right = digitalRead(turnRpin);
  if(right == HIGH && rightOld == LOW){
      rOn =! rOn;
      if(rOn && lOn){
        stepUp = true;
        state = 4;
      }
      else if(rOn && lOn == false){
        stepUp = true;
        state = 1;
      }
      else if(rOn == false && lOn){
        stepUp = false;
        //not going to happen because reset rOn and lOn when they're both HIGH
      }
      else if(rOn == false && lOn == false){
        stepUp = false;
        state = 0;
      }
  }
  setLEDShape(); 
  rightOld = right;
}

void checkLeftTurning(){
  left = digitalRead(turnLpin);
  if(left == HIGH && leftOld == LOW){
     lOn =! lOn;
     if(rOn && lOn){
        stepUp = true;
        state = 4;
      }
      else if(rOn && lOn == false){
        stepUp = false;
        //not going to happen b/c reset values when they're both HIGH
      }
      else if(rOn == false && lOn){
        stepUp = true;
        state = 2;
      }
      else if(rOn == false && lOn == false){
        stepUp = false;
        state = 0;
      }
   }
   setLEDShape(); 
   leftOld = left;
}

void drawRight(){
    blankScreen();
    matrix.drawLine(0, 0, ((matrix.width())/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((matrix.width()/3)-1, (matrix.height())/2, 0, matrix.height()-1, 1);
     
    matrix.drawLine((matrix.width()/3), 0, (2*matrix.width()/3)-1, (matrix.height()/2)-1, 1);
    matrix.drawLine((2*matrix.width()/3)-1, (matrix.height())/2,matrix.width()/3, matrix.height()-1, 1);
     
    matrix.drawLine((2*matrix.width()/3), 0, matrix.width()-1, (matrix.height()/2)-1, 1);
    matrix.drawLine(matrix.width()-1, matrix.height()/2, 2*matrix.width()/3, matrix.height()-1, 1);
    matrix.writeScreen();
}


void drawLeft(){
     matrix.drawLine(matrix.width()-1, 0, 2*matrix.width()/3, matrix.height()/2-1, 1);
     matrix.drawLine(2*matrix.width()/3, matrix.height()/2, matrix.width()-1, matrix.height()-1, 1);
     matrix.drawLine(2*matrix.width()/3-1, 0, matrix.width()/3, matrix.height()/2-1, 1);
     matrix.drawLine(matrix.width()/3, matrix.height()/2, 2*matrix.width()/3-1, matrix.height()-1, 1);
     matrix.drawLine(matrix.width()/3-1, 0, 0, matrix.height()/2-1, 1);
     matrix.drawLine(0, matrix.height()/2, matrix.width()/3-1, matrix.height()-1, 1);
     matrix.writeScreen();
}

