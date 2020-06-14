int buzzer = 13;

void setup() {
pinMode(buzzer OUTPUT); }
void loop() {
digitalWrite(buzzer , HIGH); // สร้างเสียงเตือน
delay(1000); // ร้องค้างไว้ 1 วินาที
digitalWrite(buzzer , LOW); หยุดร้อง
delay(1000); // หยุดร้อง 1 วินาที 
}
