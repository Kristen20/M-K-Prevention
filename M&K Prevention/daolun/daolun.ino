
//头文件引入
#include "ESP8266.h"        //引入ESP8266.h头文件
#include "SoftwareSerial.h"

//配置ESP8266WIFI设置
#define SSID  "HONOR 30"     //WIFI名称
#define PASSWORD "z13688051584" //WIFI密码


//OneNet部分
#define HOST_NAME "api.heclouds.com"            //API主机名称，连接到OneNET平台(定)
#define DEVICE_ID "657848813"                   //自己的OneNet设备ID
#define HOST_PORT (80)                          //API端口，连接到OneNET平台(定)
String APIKey = "202vFdNn=bX9lGyZRUUOEqXvLT q········1o="; //OneNET平台与设备绑定的APIKey
char buf[10];


SoftwareSerial mySerial(3, 2);  /* RX:D3, TX:D2 */  //定义ESP8266所连接的软串口
ESP8266 wifi(mySerial);                             //定义一个ESP8266（wifi）的对象

//数据名称定义
#define INTERVAL_NET      1000             //定义发送时间
unsigned long net_time1 = millis();        //数据上传服务器时间
int trig=4;
int echo=5;
float distance;
String postString;                                //用于存储发送数据的字符串
int score;


//初始化函数===================================================================================
void setup() {
//初始化串口波特率；
    Serial.begin(115200);
 
//ESP8266初始化
    Serial.print("setup begin\r\n");   
    Serial.print("FW Version:");
    Serial.println(wifi.getVersion().c_str());

//设置操作模式
    if (wifi.setOprToStation()) {
    Serial.print("to station ok\r\n");
  } else {
    Serial.print("to station err\r\n");
  }
  
//连接WIFI
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

    
//设置连接模式
    if (wifi.disableMUX()) {
    Serial.print("single ok\r\n");
  } else {
    Serial.print("single err\r\n");
  }

  Serial.print("setup end\r\n");

//设置脚位输出
    pinMode(trig,OUTPUT);
    pinMode(echo,INPUT);
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(10,OUTPUT);
}

//循环函数=====================================================================================
void loop() {
    //读取计算距离
    digitalWrite(trig,LOW);
    delayMicroseconds(20);
    digitalWrite(trig,HIGH);
    delayMicroseconds(20);
    digitalWrite(trig,LOW);
    distance=pulseIn(echo,HIGH)*340/2/10000;
    Serial.print("Distance:"); 
    Serial.println(distance);
    delay(1000);
    //控制亮灯
    light();
    //将数据上传到服务器
    updateSensorData();
}


//根据距离控制亮灯函数===========================================================================
void light(){
  //距离大于40亮绿灯
  if(distance>40){
  score=2;  
  digitalWrite(12,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(10,LOW);
  delay(500);//设置读取时间间隔
  }
  //距离小于40大于30亮蓝灯
  else if(distance<=40 and distance>30){
  score=1; 
  digitalWrite(12,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  delay(500);
  }
  //距离小于30亮红灯
  else{
  score=0; 
  digitalWrite(12,LOW);
  digitalWrite(11,LOW);
  digitalWrite(10,HIGH);
  delay(500);
  }
}


//建立TCP连接及数据传递函数======================================================================
void updateSensorData() {
  
//创建TCP连接
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) { 
    Serial.print("\n create tcp connection ok\r\n");
    
//拼接发送data字段字符串
   String jsonToSend ="{\"distance\":";
   jsonToSend+=distance;
   jsonToSend+="{\"score\":";
   jsonToSend+=score;
   jsonToSend+="}";
   
   Serial.println("\nSend:"+jsonToSend);

//拼接POST请求字符串
   String postString = "POST /devices/";
   postString += DEVICE_ID;
   postString += "/datapoints?type=3 HTTP/1.1";
   postString += "\r\n";
   postString += "api-key:";
   postString += APIKey;
   postString += "\r\n";
   postString += "Host:api.heclouds.com\r\n";
   postString += "Connection:close\r\n";
   postString += "Content-Length:";
   postString += jsonToSend.length();
   postString += "\r\n";
   postString += "\r\n";
   postString += jsonToSend;
   postString += "\r\n";
   postString += "\r\n";
   postString += "\r\n";
   //将str转化为char数组
   const char *postArray = postString.c_str(); 
   //发送字符串
   wifi.send((const uint8_t *)postArray, strlen(postArray)); //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)
   Serial.println("send success");
   
//释放TCP连接
   if (wifi.releaseTCP()) {                                 
     Serial.print("release tcp ok\r\n");
     } 
   else {
     Serial.print("release tcp err\r\n");
     }
     postArray = NULL; //清空数组，等待下次传输数据
  
 } 
  else {
  Serial.print("\ncreate tcp err\r\n");
  }

   
  }

   
    

    
