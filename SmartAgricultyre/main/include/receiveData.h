#ifndef receiveData_h
#define receiveData_h
#include"arduino.h"

void receiveData(void);
float parseValue(const String& data, const String& prefix); 

#endif