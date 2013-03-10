/*
  David Chatting - david@davidchatting.com
  10th March 2013
  ---
  For Close and Remote Smart City Lab - http://www.closeandremote.net/smart-city-lab/ 
  ---
  For continuous servo such as - http://www.coolcomponents.co.uk/catalog/servo-full-rotation-p-368.html
  servo red wire to 5V
  servo brown wire to GND
  servo yellow to to Arduino pin 9
*/

#include <Servo.h> 

int stillValue=90;
Servo theServo;

void setup() {
  Serial.begin(9600);
  
  theServo.attach(9);    
}

void loop() {
  //1. run the code with this line and make sure the motor is still when the sketch is uploaded
  //if it's not alter the stillValue variable above slightly (eg 88, 92, etc)
  theServo.write(stillValue+0);
  
  //2. Once the motor is still, comment out that line and uncomment this block:
  /*
  theServo.write(stillValue+10);  //+-15
  delay(1000);
  theServo.write(stillValue+0);  //+-15
  delay(1000);
  theServo.write(stillValue-10);  //+-15
  delay(1000);
  theServo.write(stillValue+0);  //+-15
  delay(1000);
  */
}
