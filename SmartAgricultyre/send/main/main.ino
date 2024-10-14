#include "sensor.h"


void setup() {
  initialization();
  
}

void loop() 
{
  Serial.println(send());
  //checkData(); 
  delay(1000);
}
