#include <Arduino.h>
#include "menu.h"
#include "application.h"
#include "wave.h"
#include "receiveData.h"

xMenu menu;

int temperature = 0;
int humidity = 0;
int light = 0;
int soil = 0;
int air = 0;

void setup()
{
    Serial.begin(9600);
    Menu_Init(&menu);//菜单初始化
    plotinit();//绘制曲线初始化
}

void loop()
{
    Menu_Loop(&menu);
    receiveData();
}
