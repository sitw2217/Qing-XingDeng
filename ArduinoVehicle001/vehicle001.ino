#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


//引入ESP8266.h头文件，建议使用教程中修改后的文件
#include "ESP8266.h"

#include "SoftwareSerial.h"

//配置ESP8266WIFI设置
#define SSID "CVN-85 Donald Trump"    //填写2.4GHz的WIFI名称，不要使用校园网
#define PASSWORD "lzewxy666"//填写自己的WIFI密码
#define HOST_NAME "api.heclouds.com"  //API主机名称，连接到OneNET平台，无需修改
#define DEVICE_ID "652209764"       //填写自己的OneNet设备ID
#define HOST_PORT (80)                //API端口，连接到OneNET平台，无需修改
String APIKey = "CXtHFQSRa0fPZ2Vsf87bylgTKOg="; //与设备绑定的APIKey

#define INTERVAL_SENSOR 50 //定义传感器采样及发送时间间隔

#define C0 -1
#define C1 262
#define C2 294
#define C3 330
#define C4 350
#define C5 393
#define C6 441
#define C7 495  
#define CH1 525
#define CH2 589
#define CH3 661
#define CH4 700
#define CH5 786
#define CH6 882
#define CH7 990
//音符(甩葱歌)
#define NTC0 -1
#define NTC1 262
#define NTC2 294
#define NTC3 330
#define NTC4 350
#define NTC5 393
#define NTC6 441
#define NTC7 495
#define NTCL5 196
#define NTCL6 221
#define NTCL7 248   
#define NTCH1 525
//音符（大鱼）
const int PROGMEM tune2[]=                 
{
  NTC3,NTC2,NTC3,NTC6,NTC3,NTC2,NTC3,NTC7,
  NTC3,NTC2,NTC3,NTCH1,NTC7,NTC5,
  NTC3,NTC2,NTC3,NTC6,NTC3,NTC2,NTC3,NTC7,
  NTC5,NTC2,NTCL7,
  NTC3,NTC2,NTC3,NTC6,NTC3,NTC2,NTC3,NTC7,
  NTC3,NTC2,NTC3,NTCH1,NTC7,NTC5,
  NTC2,NTC3,NTCL6,NTC2,NTC3,NTCL6,NTCL5,
  NTCL6,NTC1,NTCL7,
  
  NTCL6,NTC1,NTC1,NTC2,NTC2,NTC3,NTC3,NTC5,NTC6,
  NTC5,NTC3,NTC2,
  NTCL6,NTC1,NTC1,NTC2,NTC2,NTC3,NTC3,NTCL6,NTCL5,
  NTCL6,NTC1,NTC1,NTC2,NTC2,NTC3,NTC3,NTC5,NTC6,
  NTC5,NTC3,NTC2,
  NTC2,NTC3,NTCL6,NTC2,NTC3,NTCL6,NTCL5,NTCL6,
 
  NTCL6,NTC1,NTC2,NTC1,NTCL6,
  NTCL6,NTC1,NTC2,NTC1,NTC3,
  NTC3,NTC5,NTC6,NTC6,NTC5,NTC3,NTC2,NTC1,NTC2,NTC3,
  NTCL6,NTC1,NTC2,NTC1,NTCL6,
  NTCL6,NTC1,NTC2,NTC1,NTC3,
  NTC2,NTC3,NTCL6,NTC2,NTC3,NTCL6,NTCL5,NTCL6,
  
  NTC3,NTC5,NTCH1,NTC7,NTC3,
  NTC3,NTC2,NTC1,NTC1,NTC2,NTC3,
  NTC3,NTC2,NTC1,NTC6,NTCH1,NTC7,NTC6,NTC5,NTC2,NTC3,
  NTC3,NTC5,NTCH1,NTC7,NTC3,
  NTC3,NTC2,NTC1,NTC1,NTC2,NTC3,
  NTC2,NTC3,NTCL6,NTC2,NTC3,NTCL6,NTCL5,NTCL6,
};
//节拍
const int PROGMEM durt2[]=                   
{
250,250,250,250,250,250,250,250,
250,250,250,250,500,500,
250,250,250,250,250,250,250,250,
500,500,1000,
250,250,250,250,250,250,250,250,
250,250,250,250,500,500,
250,250,500,250,250,250,250,500,500,1000,
 
250,250,250,250,250,250,250,125,125,
750,250,1000,
250,250,250,250,250,250,500,500,1500,
250,250,250,250,250,250,250,125,125,
750,250,1000,
250,250,500,250,250,250,250,1500,

250,250,750,250,500,250,250,
750,250,500,250,250,500,250,250,250,250,500,500,1000,
250,250,875,125,500,250,250,500,500,1000,
250,250,500,250,250,250,250,1500,

250,250,750,250,500,250,250,
500,250,250,500,250,250,500,250,250,250,250,250,250,1500,
250,250,750,250,500,250,250,
500,250,250,1000,250,250,500,250,250,250,250,2000,
 
};

  


const int PROGMEM tune1[]=                 
{C3,C6,C3,C6,C3,C6,C3,C6,C6,C0,C0,C6,C3,C6,C6,C0,C7,CH1,CH1,C6,C6,C6,C0,C6,CH1,C7,C5,C5,C5,C7,C6,C6,C0,C6,C6,C3,C6,C6,C7,CH1,C6,C6,C6,C6,C6,CH1,CH3,CH3,CH3,CH2,CH1,CH1,C7,CH4,C6,C6,C0,C6,CH1,CH3,CH3,CH2,CH1,C7,C5,C5,C5,C5,C5,C7,CH2,CH2,CH2,CH2,CH1,CH1,C7,C7,CH1,C6,C6,C6,C0,C6,CH3,CH3,CH2,CH1,C7,C5,C5,C5,C7,CH2,CH2,CH2,CH2,CH1,C7,CH1,C6,C6,C6,C0,C6,C3,C6,C6,C0,C7,CH1,CH1,C6,C6,C6,C0,C6,CH1,C7,C5,C5,C5,C7,C6,C6,C0,C6,C6,
C3,C6,C6,C7,CH1,C6,C6,C6,C6,C6,CH1,CH3,CH3,CH3,CH2,CH1,CH1,C7,CH1,C6,C6,C0,C6,CH1,CH3,CH3,CH2,CH1,C7,C5,C5,C5,C5,C5,C7,
CH2,CH2,CH2,CH2,CH1,CH1,C7,C7,CH1,C6,C6,C6,C0,C6,CH3,CH3,CH2,CH1,C7,C5,C5,C5,C7,CH2,CH2,CH2,CH2,CH1,C7,CH1,C6,C6,C6,C0,C6
};
//节拍
const int PROGMEM durt1[]=                   
{256,256,256,256,256,256,256,256,128,128,64,128,256,256,256,128,128,128,128,128,128,128,128,128,128,256,256,256,256,256,256,128,128,128,128,256,256,128,128,256,128,128,128,128,128,128,128,128,128,128,128,128,256,256,256,128,128,128,128,
256,256,256,256,256,128,128,128,128,128,128,128,128,128,128,128,128,128,128,256,128,128,256,128,128,256,256,256,256,256,256,256,128,128,128,128,128,128,256,256,256,128,128,256,128,128,256,256,256,128,128,128,128,128,128,128,128,128,128,256,256,256,256,256,256,128,128,128,128,
256,256,256,128,256,128,128,128,128,128,128,128,128,128,128,128,128,256,256,256,128,128,128,128,256,256,256,256,256,128,128,128,128,128,128,128,128,128,128,128,128,128,128,256,128,128,256,128,128,256,256,256,256,256,256,256,128,128,128,128,128,128,128,128,256,256,256,128,128,256,128,128
};
int length1;
int length2;
int tonepin=7;   


SoftwareSerial mySerial(3, 2);
ESP8266 wifi(mySerial);
void setup()
{
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  


 pinMode(tonepin,OUTPUT);
  length1=sizeof(tune1)/sizeof(tune1[0]);
  length2=sizeof(tune2)/sizeof(tune2[0]);//蜂鸣器 
  
  mySerial.begin(115200); //初始化软串口
  Serial.begin(9600);     //初始化串口
  Serial.print("setup begin\r\n");

  //以下为ESP8266初始化的代码
  Serial.print("FW Version: ");
  Serial.println(wifi.getVersion().c_str());

  if (wifi.setOprToStation()) {
    Serial.print("to station ok\r\n");
  } else {
    Serial.print("to station err\r\n");
  }

  //ESP8266接入WIFI
  if (wifi.joinAP(SSID, PASSWORD)) {
    Serial.print("Join AP success\r\n");
    Serial.print("IP: ");
    Serial.println(wifi.getLocalIP().c_str());
  } else {
    Serial.print("Join AP failure\r\n");
  }

  

  mySerial.println("AT+UART_CUR=9600,8,1,0,0");
  mySerial.begin(9600);
  Serial.println("setup end\r\n");
}
void moveBackward(){
    digitalWrite(5,LOW);
    digitalWrite(6,HIGH);
    digitalWrite(12,LOW);
    digitalWrite(13,HIGH);
  }
void moveForward(){
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
  }
void turnRight(){
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(12,HIGH);
    digitalWrite(13,LOW);
  }
void turnLeft(){
    digitalWrite(5,HIGH);
    digitalWrite(6,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
  }
void Stop(){
    digitalWrite(5,LOW);
    digitalWrite(6,LOW);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    }

unsigned long net_time1 = millis(); //数据上传服务器时间
void loop(){

  
    
  static int feedback;

  if (net_time1 > millis())
    net_time1 = millis();

  if (millis() - net_time1 > INTERVAL_SENSOR) //发送数据时间间隔
  {

    

   
    

    if (wifi.createTCP(HOST_NAME, HOST_PORT)) { //建立TCP连接，如果失败，不能发送该数据
      Serial.print("create tcp ok\r\n");
      

      char buffer1[400];
      int timeout=1000;
      int buffer_size=400;




      String postString="GET /devices/";
      postString+=DEVICE_ID;
      postString+="/datapoints?datastream_id=CWH HTTP/1.1";
      postString+="\r\n";
      postString+="Host:api.heclouds.com";
      postString+="\r\n";
      postString+="api-key: ";
      postString+=APIKey;
      postString+="\r\n";
      postString+="\r\n";
     

      const char *postArray = postString.c_str(); //将str转化为char数组

      Serial.println(postArray);
      wifi.send((const uint8_t *)postArray, strlen(postArray)); //send发送命令，参数必须是这两种格式，尤其是(const uint8_t*)
      Serial.println("send success");
      wifi.recv((const uint8_t *)buffer1,(uint32_t)buffer_size, (uint32_t)timeout);
      Serial.print(buffer1);
      

      
      for(int i=0;i<500;i++)
      {
        if(buffer1[i]=='=')
          {
            feedback=(int)buffer1[i+1]-48;
            break;
            }
        };
      Serial.print("\n");
      Serial.print("**************************************");
      Serial.print(feedback);
      
      Serial.print("\n");
      if (wifi.releaseTCP()) { //释放TCP连接
        Serial.print("release tcp ok\r\n");
      } else {
        Serial.print("release tcp err\r\n");
      }
    postArray = NULL; //清空数组，等待下次传输数据*/
    } else {
      Serial.print("create tcp err\r\n");
    }
    

    Serial.println("");

    net_time1 = millis();
  Serial.print("feedback=");
  Serial.print(feedback);
  }

  //开始控制小车
 
  if(feedback==1)
  {
    moveForward();
  }
  else if(feedback==2){
    moveBackward();
  }
  else if(feedback==3){
    turnRight();
  }
  else if(feedback==4){
    turnLeft();
  }
  else if(feedback==5){
    Stop();
  }
  else if(feedback==6){
    for(int x=0;x<length1;x++)
  {
    if((x>=11&&x<=15)||(x>=84&&x<=90)){moveForward();}
    else if((x>=16&&x<=22)||(x>=91&&x<=101)){moveBackward();}
    else if((x>=29&&x<=32)||(x>=56&&x<=80)||(x>=105&&x<=114)||(x>=129&&x<=134)||(x>=149&&x<=172)){turnRight();}
    else if((x>=25&&x<=28)||(x>=33&&x<=55)||(x>=115&&x<=122)||(x>=136&&x<=146)||(x>=174&&x<(length1-1))){turnLeft();}
    else if(x==length1-1){Stop();}
    if(x%3==0){digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    }
    if(x%3==1){digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
      }
    if(x%3==2){digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);}
    tone(tonepin,pgm_read_word_near(tune1+ x));
    delay(pgm_read_word_near(durt1+ x));   
    noTone(tonepin);
  }
  delay(2000);
    }
  else if(feedback==7){
    
    for(int x=0;x<length2;x++)
  {
    if(x%3==0){digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    }
    if(x%3==1){digitalWrite(9,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
      }
    if(x%3==2){digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);}
    
    tone(tonepin,pgm_read_word_near(tune2+ x));
    delay(pgm_read_word_near(durt2+ x));   
    noTone(tonepin);
  }
  delay(2000);}
  digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }
  
