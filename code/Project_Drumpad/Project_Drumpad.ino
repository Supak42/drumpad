#include "LiquidCrystal_I2C.h"
#include <MIDI.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MIDI_CREATE_DEFAULT_INSTANCE();

#define KICKTHRESHOLD 20
#define SNARETHRESHOLD 20
#define HIHATTHRESHOLD 20
const int buttonPin = 2;
const int Buzzer = 9;
int buttonState = 0;
boolean count = false;

unsigned long snareInterval = 10;
unsigned long previousSnareMillis = 0;
unsigned long kickInterval = 10;
unsigned long previousKickMillis = 0;
unsigned long hihatInterval = 10;
unsigned long previousHihatMillis = 0;

int kickPin = A0;
int snarePin = A1;
int hihatPin = A2;
int pedalPin = 8;

int kickValue = 0;
int snareValue = 0;
int hihatValue = 0;
int pedalValue = 0;

boolean pedalPlayed = true;

// MAPPING FOR ADDICTIVE DRUMS
byte KICK = 36;
byte SNARE_RIMCLICK = 44;
byte SNARE_SHALLOW_HIT = 43;
byte SNARE_SIDESTICK = 42;
byte SNARE_SHALLOW_RIMSHOT = 41;
byte SNARE_FLAM_HIT = 40;
byte SNARE_FLAM_RIM = 39;
byte SNARE_OPEN_HIT = 38;
byte SNARE_RIMSHOT = 37;
byte HIHAT_PEDAL_OPEN = 59;
byte HIHAT_OPEN_BELL = 58;
byte HIHAT_OPEN_D = 57;
byte HIHAT_OPEN_C = 56;
byte HIHAT_OPEN_B = 55;
byte HIHAT_OPEN_A = 54;
byte HIHAT_CLOSED_BELL = 53;
byte HIHAT_CLOSED2_SHAFT = 52;
byte HIHAT_CLOSED2_TIP = 51;
byte HIHAT_CLOSED1_SHAFT = 50;
byte HIHAT_CLOSED1_TIP = 49;
byte HIHAT_PEDAL_CLOSED = 48;
byte EXTRA = 47;
byte TOM1_RIMSHOT = 72;
byte TOM1_HIT = 71;
byte TOM2_RIMSHOT = 70;
byte TOM2_HIT = 69;
byte TOM3_RIMSHOT = 68;
byte TOM3_HIT = 67;
byte TOM4_RIMSHOT = 68;
byte TOM4_HIT = 67;

void setup() {
  Serial.begin(9600);
  MIDI.begin();
  pinMode(pedalPin, INPUT);
  digitalWrite(pedalPin, HIGH);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, world!");
  delay(2000);
  lcd.clear();

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(Buzzer, OUTPUT);
}
boolean noteReady(unsigned long previousMillis, unsigned long interval){
  if ((unsigned long)(millis() - previousMillis) >= interval) {
    return true;
  } else {
    return false;
  }
}

void loop(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {
    count = !count;
  }
  if (count == true) {
    beep(5, 200);
    beep(3, 200);
    beep(3, 200);
    beep(3, 200);
    lcd.setCursor(0, 0);
    lcd.println("Botton : ON");
  } else if(count == false) {
    lcd.setCursor(0, 0);
    lcd.println("Botton : OFF");
  }
  piezoElectric();
  lcd.clear();
}

void hitNote(int value, byte note, int multiply, int treshold){
  int velocity = value - treshold;

  if (velocity > 127){
    velocity = 127;}
  else if (velocity < 0){
    velocity = 0;}

  MIDI.sendNoteOn(note, velocity, 1);
  MIDI.sendNoteOff(note, 0, 1);
}

void beep(unsigned char vol, unsigned char delayms) {
  analogWrite(9, vol);
  delay(delayms);
  analogWrite(9, 0);
  delay(300);
}

void piezoElectric(){
  kickValue = analogRead(kickPin);
  snareValue = analogRead(snarePin);
  hihatValue = analogRead(hihatPin);
  pedalValue = digitalRead(pedalPin);

  if (kickValue >= KICKTHRESHOLD &&
      noteReady(previousKickMillis, kickInterval)) {
    previousKickMillis = millis();
    hitNote(kickValue, KICK, 5, KICKTHRESHOLD);
    lcd.setCursor(0, 1);
    lcd.print("Kick");
  }

  if (snareValue >= SNARETHRESHOLD &&
      noteReady(previousSnareMillis, snareInterval)) {
    previousSnareMillis = millis();
    hitNote(snareValue, SNARE_OPEN_HIT, 1, SNARETHRESHOLD);
    lcd.setCursor(0, 1);
    lcd.print("Snare");
  }

  if (hihatValue >= HIHATTHRESHOLD &&
      noteReady(previousHihatMillis, hihatInterval)) {
    previousHihatMillis = millis();
    if (pedalValue == LOW) {
      hitNote(hihatValue, HIHAT_CLOSED1_TIP, 1, HIHATTHRESHOLD);
    } else {
      hitNote(hihatValue, HIHAT_OPEN_A, 1, HIHATTHRESHOLD);
    }
    lcd.setCursor(0, 1);
    lcd.print("Hihat");
  }

  /*if (pad4 > 100) {
    Serial.println("HeavyHit"); // Sound 4
    lcd.setCursor(0, 1);
    lcd.println("Pad : 4");
  } else if (pad4 < 100) {
    Serial.println("LightHit");
    lcd.setCursor(0, 1);
    lcd.println("Pad : 4");
  }

  if (pad5 > 100) {
    Serial.println("HeavyHit"); // Sound 5
    lcd.setCursor(0, 1);
    lcd.println("Pad : 5");
  } else if (pad5 < 100) {
    Serial.println("LightHit");
    lcd.setCursor(0, 1);
    lcd.println("Pad : 5");
  }*/
}
