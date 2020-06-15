const int buttonPin = 2;
const int ledPin = 13;
int buttonState = 0;
int count = 0;
void setup() {
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
  } break;
  case 2: {
    count = 0;
  } break;
  }
}
