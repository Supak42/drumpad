void setup()
{
Serial.begin(9600); //Open the serial to set the baud rate as 9600bps

}
void loop()
{
int val=analogRead(A0); //Connect the sensor to analog interface A0
Serial.println("Val ");
if(val > 100){
Serial.println("Detect");//Print the analog value read via serial port
}
delay(100);

}
