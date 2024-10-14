#include "wave.h"
#include "stdio.h"
#include "dispDirver.h"
#include <Fonts/FreeSans12pt7b.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

int margin = 10;  // 坐标轴距离屏幕边缘的距离
int graphWidth = SCREEN_WIDTH - 2 * margin;  // X轴有效宽度
int graphData[SCREEN_WIDTH / 2];  // 用于存储传感器数据
int dataIndex = 0;
int stepSize = 10;  // 曲线点之间的水平距离
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void plotinit() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void plotCure(xpMenu Menu) {
    int mappedValue = map((float)(*(int *)(Menu->now_item->element->data->ptr)), Menu->now_item->element->data->min,  Menu->now_item->element->data->max, 0, SCREEN_HEIGHT - 3 * margin); // 将传感器数据从实际范围映射到屏幕的像素范围
    graphData[dataIndex] = mappedValue;
    dataIndex = (dataIndex + 1) % (graphWidth / stepSize); // 依据X轴有效宽度更新索引

    display.clearDisplay();

    // 将X轴上移10个像素
    int xAxisYPosition = SCREEN_HEIGHT - margin - 5;

    display.drawLine(margin, xAxisYPosition, SCREEN_WIDTH - margin, xAxisYPosition, WHITE);                        // 绘制X轴
    display.drawLine(SCREEN_WIDTH - margin, xAxisYPosition, SCREEN_WIDTH - margin - 5, xAxisYPosition - 5, WHITE); // 向上箭头
    display.drawLine(SCREEN_WIDTH - margin, xAxisYPosition, SCREEN_WIDTH - margin - 5, xAxisYPosition + 5, WHITE); // 向下箭头
    display.drawLine(margin, xAxisYPosition, margin, margin, WHITE);                                               // 绘制Y轴
    display.drawLine(margin, margin, margin - 5, margin + 5, WHITE);                                               // 向左箭头
    display.drawLine(margin, margin, margin + 5, margin + 5, WHITE);                                               // 向右箭头

    for (int i = 0; i < graphWidth / stepSize - 1; i++) { // 绘制曲线
        int thisIndex = (dataIndex + i) % (graphWidth / stepSize);
        int nextIndex = (dataIndex + i + 1) % (graphWidth / stepSize);
        display.drawLine(margin + i * stepSize, xAxisYPosition - graphData[thisIndex], margin + (i + 1) * stepSize, xAxisYPosition - graphData[nextIndex], WHITE);
    }

    // 在底部显示字符串，防止与X轴重叠
    display.setTextSize(1); // 设置文本大小
    display.setTextColor(WHITE); // 设置文本颜色
    display.setCursor(margin, SCREEN_HEIGHT - margin + 2); // 设置文本显示的起始位置，X轴下方
    display.print(Menu->now_item->element->data->name);
    display.print(":");
    display.print(*(int *)(Menu->now_item->element->data->ptr));
    display.print(Menu->now_item->element->data->unit);

    display.display();
    delay(100);
}
