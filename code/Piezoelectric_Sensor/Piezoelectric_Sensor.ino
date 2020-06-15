void setup()
{
Serial.begin(9600); //Open the serial to set the baud rate as 9600bps

}
void loop()
{
int val=analogRead(A0); //Connect the sensor to analog interface A0


if(val > 100){
Serial.println("HeavyHit");//Print the analog value read via serial port
}

else if (val < 100){
    Serial.println("LightHit");
}
delay(100);
}
