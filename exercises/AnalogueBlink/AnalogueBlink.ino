/*
  David Chatting - david@davidchatting.com
  10th March 2013
  ---
  For Close and Remote Smart City Lab - http://www.closeandremote.net/smart-city-lab/ 
  ---
  LED and 220 ohm resistor between Arduino pin 3 and GND
  ---
  Adapted from http://arduino.cc/en/Tutorial/blink
*/

void setup() {
  Serial.begin(9600);
  Serial.print("*");
  
  pinMode(3, OUTPUT);     
}

void loop() {
  Serial.print(".");
  
  analogWrite(3,128);  
  delay(300);
  
  analogWrite(3,255);  
  delay(300);
  
  analogWrite(3,0);  
  delay(300);
}
