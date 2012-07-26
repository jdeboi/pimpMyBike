void checkReed(){
  int r = digitalRead(reedPin);
  if(r == 1 && reedOn == false){
    reedOn = true;
    reedTimeDelta = millis() - reedTime;
    reedTime = millis();
    circleNum++;
  }
  else if (r == 0 && reedOn){
    reedOn = false;
  }
}

void getSpeed(){
  speedometer = wheelC/reedTimeDelta;
  MPH = speedometer * 22.369; 
  KPH = speedometer * 36; 
}

void getDistance(){
  odometer = wheelC*circleNum;
  miles = odometer / 160934.4;
  kilometers = odometer / 100000;
}
