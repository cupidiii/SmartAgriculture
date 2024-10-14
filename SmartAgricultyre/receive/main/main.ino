#include "config.h"



void setup() 
{
  initialization();
}

void loop() 
{
 receiveData();
 delay(1000);
 //Serial.println(temperature);
}
