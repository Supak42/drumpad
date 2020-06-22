void setup() {

pinMode(9, OUTPUT);

}

void loop() {
beep(255);
beep(200);
beep(200);
beep(200);
}

void beep(unsigned char delayms){

analogWrite(9, 3); 
delay(delayms);
analogWrite(9, 0);
delay(300); 


}
