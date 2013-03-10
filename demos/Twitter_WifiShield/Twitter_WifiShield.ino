/*
  David Chatting - david@davidchatting.com
  10th March 2013
  ---
  For Close and Remote Smart City Lab - http://www.closeandremote.net/smart-city-lab/ 
  ---
  LED and 220 ohm resistor between Arduino pin 3 and GND
  ---
  Heavily based on http://arduino.cc/en/Tutorial/WiFiTwitterClient
*/


#include <SPI.h>
#include <WiFi.h>

char ssid[] = "TheNetworkName"; //  your network SSID (name) 
char pass[] = "password";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;
WiFiClient client;

const unsigned long requestInterval = 30*1000;    // delay between requests; 30 seconds
char server[] = "api.twitter.com";                // name address for twitter API

boolean requested;                     // whether you've made a request since connecting
unsigned long lastAttemptTime = 0;     // last time you connected to the server, in milliseconds

String currentLine = "";               // string to hold the text from server
String tweet = "";                     // string to hold the tweet
boolean readingTweet = false;          // if you're currently reading the tweet

void setup() {
  currentLine.reserve(256);
  tweet.reserve(150);
  
  Serial.begin(9600);
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);  
 
    // wait 10 seconds for connection:
    delay(10000);
  } 
  // you're connected now, so print out the status:
  printWifiStatus();
  connectToServer();
  
  pinMode(3,OUTPUT);
  digitalWrite(3,LOW);
}

void loop() {
  if (client.connected()) {
    if (client.available()) {
      char inChar = client.read();
      
      currentLine += inChar;  // add incoming byte to end of line
      if (inChar == '\n') currentLine = "";
      
      // if the current line ends with <text>, it will
      // be followed by the tweet:
      if ( currentLine.endsWith("<text>")) {
        // tweet is beginning. Clear the tweet string:
        readingTweet = true; 
        tweet = "";
        // break out of the loop so this character isn't added to the tweet:
        return;
      }
      // if you're currently reading the bytes of a tweet,
      // add them to the tweet String:
      if (readingTweet) {
        if (inChar != '<') {
          tweet += inChar;
        } 
        else {
          // if you got a "<" character,
          // you've reached the end of the tweet:
          readingTweet = false;
          processTweet(tweet);
          // close the connection to the server:
          client.stop(); 
        }
      }
    }   
  }
  else if (millis() - lastAttemptTime > requestInterval) {
    // if you're not connected, and two minutes have passed since
    // your last connection, then attempt to connect again:
    connectToServer();
  }
}

void processTweet(String t){
  Serial.println(t);
  if(t.indexOf("#loungelab")>0) digitalWrite(3,HIGH);
}

void connectToServer() {
  // attempt to connect, and wait a millisecond:
  Serial.println("connecting to server...");
  if (client.connect(server, 80)) {
    Serial.println("making HTTP request...");
    // make HTTP GET request to twitter:
    client.println("GET /1/statuses/user_timeline.xml?screen_name=davidchatting&count=1 HTTP/1.1");
    client.println("Host:api.twitter.com");
    client.println("Connection:close");
    client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}   

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}




