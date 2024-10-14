#include "WString.h"
#ifndef sensor_h
#define sensor_h

void initialization(void);
int readAir(void);
int readTemperature(void);
int readHumidity(void);
int readLight(void);
int readSoil(void);
String send(void);
void checkData(void);


#endif