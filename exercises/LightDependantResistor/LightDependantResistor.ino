/*
  David Chatting - david@davidchatting.com
  10th March 2013
  ---
  For Close and Remote Smart City Lab - http://www.closeandremote.net/smart-city-lab/ 
  ---
  LDR between 5V and Arduino pin A0
  10k ohm resistor between Arduino pin A0 and GND
  LED and 220 ohm resistor between Arduino pin 3 and GND
  ---
  Adapted from http://arduino.cc/en/Tutorial/AnalogInput
*/

int ldrValue;

void setup() {
  Serial.begin(9600);  
  
  pinMode(3, OUTPUT);    
}

void loop() {
  ldrValue=analogRead(A0);
  Serial.println(ldrValue);
  
  digitalWrite(3, HIGH);
  delay(ldrValue);
  digitalWrite(3, LOW);
  delay(ldrValue);
}
