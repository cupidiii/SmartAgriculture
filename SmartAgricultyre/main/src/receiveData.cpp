#include "HardwareSerial.h"
#include "receiveData.h"

extern int temperature, humidity, light, soil, air;
const size_t npos = (size_t)-1;
void initialization(void)
{
  
}

void receiveData(void)//接收数据
{
  if (Serial.available() > 0) 
  {
    String data = Serial.readString();
    temperature = parseValue(data, "T:");
    humidity = parseValue(data, "H:");
    light = parseValue(data, "L:");
    soil = parseValue(data, "S:");
    air = parseValue(data, "A:");
  }
}

float parseValue(const String& data, const String& prefix) //解析数据
{
  size_t startPos = data.indexOf(prefix);
  if (startPos == npos) 
  {
    return 0;  // Not a number
  }

  startPos += prefix.length();  // Move past the prefix
  size_t endPos = data.indexOf(',', startPos);

  if (endPos == npos) 
  {
    return data.substring(startPos).toFloat();
  } 
  else 
  {
    return data.substring(startPos, endPos).toFloat();
  }
}
