/*
  David Chatting - david@davidchatting.com
  10th March 2013
  ---
  For Close and Remote Smart City Lab - http://www.closeandremote.net/smart-city-lab/ 
  ---
  ID12 RFID Reader - https://www.sparkfun.com/products/8419
  ---
  id12 pin 11 to Arduino 5V
  id12 pin 1 to Arduino GND
  id12 pin 9 to Arduino pin 2
  ---
  LED between Arduino pin 13 and GND
*/

#include <SoftwareSerial.h>

SoftwareSerial rfidReader(2,3); //RX,TX
int ledPin=13;

void setup() {
  Serial.begin(9600);
  rfidReader.begin(9600);

  pinMode(ledPin,OUTPUT);  //LED
}

void loop() {
  String thisTag=readTag();

  if(!thisTag.equals("NOTAG")){
    
    Serial.println(thisTag);
    if(thisTag.equals("010AC893ACFC")){
      digitalWrite(ledPin,HIGH);
      delay(5000);
    }
    else {
      digitalWrite(ledPin,HIGH);
      delay(200);
      digitalWrite(ledPin,LOW);
      delay(200);
      digitalWrite(ledPin,HIGH);
      delay(200);
      digitalWrite(ledPin,LOW);
    }
  }
  else {
    digitalWrite(13,LOW);
  }
}

String readTag(){
  String thisTag;

  char b;
  if(rfidReader.available()) {
    if(rfidReader.read()==2){
      do{
        b=rfidReader.read();
        if(b!=3 && b!=-1) thisTag+=b;
      }
      while(b!=3);
    }
  }
  thisTag.trim();

  if(thisTag.length()==0) thisTag="NOTAG";

  return(thisTag);
}



