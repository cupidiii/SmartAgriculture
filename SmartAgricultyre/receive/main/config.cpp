#include "HardwareSerial.h"
#include "config.h"

int temperature = 0;
int humidity = 0;
int light = 0;
int soil = 0;
String data;

void initialization(void)
{
  Serial.begin(9600);
}

void receiveData(void)//接收数据
{
  if (Serial.available() > 0) 
  {
    data = Serial.readString();
    temperature = parseValue(data, "T:");
    humidity = parseValue(data, "H:");
    light = parseValue(data, "L:");
    soil = parseValue(data, "S:");
  }
  Serial.println(data);
}

float parseValue(const String& data, const String& prefix) //解析数据
{
  size_t startPos = data.indexOf(prefix);
  if (startPos == -1) 
  {
    return 0;  // Not a number
  }

  startPos += prefix.length();  // Move past the prefix
  size_t endPos = data.indexOf(',', startPos);

  if (endPos == -1) 
  {
    return data.substring(startPos).toFloat();
  } 
  else 
  {
    return data.substring(startPos, endPos).toFloat();
  }
}
