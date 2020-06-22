const int buttonPin = 2;
const int ledPin = 13;
int buttonState = 0;
int count = 0;
void setup() {
  pinMode(9, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}
void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    count++;
  }
  switch (count) {
  case 0: {
    digitalWrite(ledPin, LOW);
  } break;
  case 1: {
    digitalWrite(ledPin, HIGH);
    beep(255);
    beep(200);
    beep(200);
    beep(200);
  } 
  case 2: {
    count = 0;
  } break;
  }
}

void beep(unsigned char delayms){

analogWrite(9, 3); 
delay(delayms);
analogWrite(9, 0);
delay(300); 


}