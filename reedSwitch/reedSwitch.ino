int reedPin = 0;    //analog input, but could also be digital
int circleNum = 0;
float wheelDiameter = 25.2;
float wheelC = 3.14 * wheelDiameter;
float odometer = 0;
float miles = 0;
float kilometers = 0;
float speedometer = 0;
float MPH = 0;
float KPH = 0;
int reedTime;
int reedTimeDelta;
boolean reedOn = false;

void setup(){
  Serial.begin(9600);
  reedTime = millis();
}

void loop(){
  checkReed();
  getSpeed();
  getDistance();
  //testReed();
}

void checkReed(){
  int r = analogRead(reedPin);
  if(r > 10 && reedOn == false){
    reedOn = true;
    reedTimeDelta = millis() - reedTime;
    reedTime = millis();
    circleNum++;
   
   //prints all metrics when magnet passes switch
    printAll();
  }
  else if (r < 10 && reedOn){
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

void printAll(){
  Serial.print("Circles: ");
  Serial.println(circleNum);
  Serial.print("MPH: ");
  Serial.println(MPH, 2);
  Serial.print("Distance: ");
  Serial.println(miles, 2);
}

void testReed(){
  int voltage = analogRead(reedPin);
  if(voltage > 10){
    Serial.println(voltage);
  }
}
