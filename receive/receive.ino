#include "configure.h"
#include "Arduino.h"
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>//默认，加载WIFI头文件
#include "PubSubClient.h"//默认，加载MQTT库文件
/*接线说明
syn   yellow--tx（yellow-rx,white-tx）
oled  scl--d1 sda--d2
button out--d0
lora  rxd--d3  txd--d4
*/
#define rxPin D4
#define txPin D3
const char* ssid = "esp8266";                  //修改，修改为你的路由的WIFI名字
const char* password = "123456789";           //修改为你的WIFI密码
const char* mqtt_server = "bemfa.com";       //默认，MQTT服务器地址
const int mqtt_server_port = 9501;          //默认，MQTT服务器端口
#define ID_MQTT  "ab5c3e8a289e8ebe2a7426cb392da9a7"   //mqtt客户端ID，修改为你的开发者密钥
const char*  topic = "led002";                       //Led主题名字，可在巴法云控制台自行创建，名称随意
const char * dhttopic = "temp004";                 //温湿度主题名字，可在巴法云mqtt控制台创建
long timeval = 1 * 1000;                  //上传的传感器时间间隔，默认3秒
int h;//温度数据最佳温度16-20
int t;//湿度数据最佳湿度55-65
const int buttonPin = D0;//按键 
int buttonState = 1;//按键状态 
String ledstatus = "off";//led状态默认off
long lastMsg = 0;//时间戳
WiFiClient espClient;
PubSubClient client(espClient);//mqtt初始化
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

//灯光函数及引脚定义
void turnOnLed();
void turnOffLed();
void baojing() {
  if(t > 23)
  {
    Serial.println("<U>当前温度过高请注意降温");
  }
  else if(t < 20)
  {
    Serial.println("<U>当前温度过低请注意加温");
    delay(1000);
  }

}
void wendu()
{
 Serial.println("<U>现在的温度是");
 Serial.println(t);
 Serial.println("度");
}
void shidu()
{
 Serial.println("<U>现在的湿度是百分之");
 Serial.println(h);
}
void button() 
{
  if (buttonState == 0) 
  {
    wendu();
    delay(4000);
    shidu();
  }
}
void setup_wifi() {
  delay(10);
  // Serial.println();
  // Serial.print("Connecting to ");
  // Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }

  // Serial.println("");
  // Serial.println("WiFi connected");
  // Serial.println("IP address: ");
  // Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String Mqtt_Buff = "";
  for (int i = 0; i < length; i++) {
    Mqtt_Buff += (char)payload[i];
  }
  Serial.print(Mqtt_Buff);
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if (Mqtt_Buff == "on") {//如果接收字符on，亮灯
    turnOnLed();//开灯函数

  } else if (Mqtt_Buff == "off") {//如果接收字符off，亮灯
    turnOffLed();//关灯函数
  }
  Mqtt_Buff = "";
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected())
   {
    if (client.connect(ID_MQTT)) {//连接mqtt;
      client.subscribe(topic);//修改，修改为你的主题
  }
}
}
void setup() 
{
  Serial.begin(9600);
  mySerial.begin(9600);
  OLED_Init();//oled初始化
  Oled_Show();
  pinMode(buttonPin, INPUT);
  setup_wifi();
  pinMode(buttonPin, INPUT);
  client.setServer(mqtt_server, mqtt_server_port);
  client.setCallback(callback);
}
void loop() 
{   
  buttonState = digitalRead(buttonPin);//获取按键状态
  if (mySerial.available()>0) 
    {
      String data = mySerial.readString();
      int data1 = data.toInt();// 类型转换,string -> int
      h = data1/100;
      t = data1%100;
      OLED_ShowNum(60,3,t,2,16);
      OLED_ShowNum(60,5,h,2,16);
    }  
    if (t > 23) 
    {
      String data = mySerial.readString();
      int data1 = data.toInt();// 类型转换,string -> int
      h = data1/100;
      t = data1%100;
      OLED_ShowNum(60,3,t,2,16);
      OLED_ShowNum(60,5,h,2,16);
    }
    button();baojing();
  if (!client.connected())//判断mqtt是否连接
   {
      reconnect();
   } 
  client.loop();//mqtt客户端
  long now = millis();//获取当前时间戳
  if (now - lastMsg > timeval) //如果达到3s，进行数据上传
  {
    lastMsg = now;
    String  msg = "#" + (String)t + "#" + (String)h; //数据封装#温度#湿度#开关状态#
    client.publish(dhttopic, msg.c_str());//数据上传
  }
  
}
//打开灯泡
void turnOnLed() {
  ledstatus = "on";
  Serial.println("turn on light");
  //digitalWrite(B_led, LOW);
}
//关闭灯泡
void turnOffLed() {
  ledstatus = "off";
  Serial.println("turn off light");
  //digitalWrite(B_led, HIGH);
}
