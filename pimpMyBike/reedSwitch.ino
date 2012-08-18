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

String getSpeedString(){
  speedometer = wheelC/reedTimeDelta; 
  if(metric){
    KPH = speedometer * 36;
    char tmp[25] = "KPH: ";
    dtostrf(KPH,1,2, &tmp[12]);
    return tmp;
  }
  else{
    MPH = speedometer * 22.369;
    char tmp[25] = "KPH: ";
    dtostrf(MPH,1,2, &tmp[12]);
    return tmp;
  } 
}

String getDistanceString(){
  odometer = wheelC*circleNum;
  if(metric){
    kilometers = odometer / 100000;
    char tmp[25] = "Distance: ";
    dtostrf(kilometers,1,2, &tmp[12]);
    return tmp; 
  }
  else{
    miles = odometer / 160934.4;
    char tmp[25] = "Distance: ";
    dtostrf(miles,1,2, &tmp[12]);
    return tmp; 
  }
}

void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
  // normalize the red LED - its brighter than the rest!
  r = map(r, 0, 255, 0, 100);
  g = map(g, 0, 255, 0, 150);
 
  r = map(r, 0, 255, 0, brightness);
  g = map(g, 0, 255, 0, brightness);
  b = map(b, 0, 255, 0, brightness);
 
  // common anode so invert!
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);
  Serial.print("R = "); Serial.print(r, DEC);
  Serial.print(" G = "); Serial.print(g, DEC);
  Serial.print(" B = "); Serial.println(b, DEC);
  analogWrite(REDLITE, r);
  analogWrite(GREENLITE, g);
  analogWrite(BLUELITE, b);
}
