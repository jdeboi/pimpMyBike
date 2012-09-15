int LED = A5;
int readLED = A3;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(readLED, INPUT);
}

void loop(){
  if(digitalRead(readLED) == HIGH){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
}
    
