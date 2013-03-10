/*
  David Chatting - david@davidchatting.com
  10th March 2013
  ---
  For Close and Remote Smart City Lab - http://www.closeandremote.net/smart-city-lab/ 
  ---
  Button between 5V and Arduino pin 4
  10K ohm resistor between Arduino pin 4 and GND
  LED and 220 ohm resistor between Arduino pin 3 and GND
  ---
  Adapted from http://arduino.cc/en/Tutorial/Button
*/

boolean buttonState;

void setup() {
  Serial.begin(9600);  
  
  pinMode(3, OUTPUT);
  pinMode(4, INPUT);     
}

void loop() {
  buttonState=digitalRead(4);
  Serial.println(buttonState);
  
  if(buttonState == HIGH){
    digitalWrite(3, HIGH);
  }
  else{
    digitalWrite(3, LOW);
  }
}
