#include "WString.h"
#include "Arduino.h"
#include "HardwareSerial.h"
#include <DHT11.h>
#include "sensor.h"

#define DHT_PIN 2
#define AIR_PIN A0
#define LIGHT_PIN A1
#define SOIL_PIN A2

int temperature = 0;
int humidity = 0;
int air = 0;
int light = 0;
int soil = 0;


DHT11 dht11(DHT_PIN);


void initialization()
{
  Serial.begin(9600);
  pinMode(AIR_PIN, INPUT);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(SOIL_PIN, INPUT);
}

int readAir()
{
  air = analogRead(AIR_PIN);
  return air;
}

int readTemperature()
{
  temperature = dht11.readTemperature();
  return temperature;
}

int readHumidity()
{
  humidity = dht11.readHumidity();
  return humidity;
}

int readLight(void)
{
  light = analogRead(LIGHT_PIN);
  return light;
}

int readSoil(void)
{
  soil = analogRead(SOIL_PIN);
  soil = map(soil, 0, 1023, 0, 100);
  return soil;
}

String send()
{
  air = readAir();
  temperature = readTemperature();
  humidity = readHumidity();
  light = readLight();
  soil = readSoil();
  String data = "T:" + String(temperature) + ",H:" + String(humidity) + ",L:" + String(light) + ",S:" + String(soil) + ",A:" + String(air);
  return data;
}

void checkData()
{
  Serial.print("Temperature: ");
  Serial.print(readTemperature());
  Serial.print(", Humidity: ");
  Serial.print(readHumidity());
  Serial.print(", Light: ");
  Serial.print(readLight());
  Serial.print(", soil: ");
  Serial.print(readSoil());
  Serial.print(", air: ");
  Serial.println(readAir());
  delay(1000);
}





