/*
*To do- figure out why drawStrobe() causes the entire
*sketch to malfunction- stack overflow?
*drawRight() is exactly the same and works fine
*have to talk to someone who knows more about comp sci
*or electronics than I do
*/
char strobePixels [] =
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

void drawStrobe(){
 for(int i = 0; i < 16; i++) {
    for(int j = 0; j < 24; j++) {
      matrix.drawPixel(j, i, (strobePixels[j+i*24]-'0'));
      LEDs[j+i*24] = rightArrow[j+i*24];
    }    
 }
 matrix.writeScreen();
}


void setStrobe(){
  if(stateChange && turningOn == false && brakeOn == false){
    if (strobeOn){
      drawStrobe();
    }
    else{
      matrix.clearScreen();
    }
  }
}


