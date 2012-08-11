//const int buttonPin = A3;     // the number of the pushbutton pin
//const int ledPin =  A5;      // the number of the LED pin
const int buttonPin = A2;     // the number of the pushbutton pin
const int ledPin =  A4;      // the number of the LED pin
boolean on = false;
boolean pressed = false;

int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  pinMode(ledPin, OUTPUT);      
  pinMode(buttonPin, INPUT);     
  Serial.begin(9600);
}

void loop(){
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH && pressed == false) {     
    // turn LED on:
    pressed = true;
    Serial.println("HIGH and not pressed");
    on = !on;
    if(on){  
      digitalWrite(ledPin, HIGH);
      Serial.println(" LED on");
      delay(50);
    }
    else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      Serial.println("LED off");
      delay(50);
    } 
  }
  else if(buttonState == LOW && pressed == true){
    pressed = false;
    Serial.println("LOW and pressed");
  }
}
