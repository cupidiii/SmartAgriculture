#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 2  
#define DHTTYPE DHT11 
#define rxPin 10
#define txPin 11

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  dht.begin();
}
void loop() 
{
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  String h1 = String(h);
  String t1 = String(t);
  String data = h1+t1;
  //Serial.println(data);
  mySerial.println(data);
  delay(1000);
}
