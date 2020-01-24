#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>
//Вставляем ссылку в поле «Дополнительные ссылки для Менеджера плат:
//http://arduino.esp8266.com/stable/package_esp8266com_index.json
//В среде Arduino IDE из меню выбираем тип платы, которую будем тестировать.
//В данном случае это "NodeMCU 0.9 (ESP-12 Module)

// ============================== WiFi -Connect =======================================
ESP8266WiFiMulti wifiMulti;
boolean connectioWasAlive = true;

WiFiClient clnt1; 

//================================ MySQL ===============================================
IPAddress server_addr(192,168,2,10);  // IP of the MySQL *server* here
char usr[] = "term";              // MySQL user login username
char psw[] = "1234";        // MySQL user login password
char query[128];
byte srv_ip[] = {192,168,2,10};
byte mac[6];                     // the MAC address of your Wifi shield

//WiFiClient client;
///\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\
//\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
void setup() {
  //esp8266.begin(9600);
  Serial.begin(9600);
  Serial.println();
  delay(1000);

  wifiMulti.addAP("Net_0", "12345678");
  delay(1000);
  wifiMulti.addAP("NET_1", "12345678");
  delay(1000);
  wifiMulti.addAP("NET_2", "12345678");
  delay(1000);

  WiFi.macAddress(mac);
  Serial.print(mac[0],HEX); 
  Serial.print("-");
  Serial.print(mac[1],HEX);
  Serial.print("-");
  Serial.print(mac[2],HEX);
  Serial.print("-");
  Serial.print(mac[3],HEX);
  Serial.print("-");
  Serial.print(mac[4],HEX);
  Serial.print("-");
  Serial.print(mac[5],HEX);
  Serial.println("");

  delay(1000);
  Serial.println(WiFi.localIP());
  
  Serial.println("Connecting...");
  clnt1.connect(srv_ip, 80);
  delay (2000);
  //потом отключаемся
  clnt1.stop();

  Serial.println("!@#");
  Serial.printf("... %s\n", WiFi.SSID().c_str());

}
//========================================================================================================================================================================
//========================================================================================================================================================================

void monitorWiFi(){
  if (wifiMulti.run() != WL_CONNECTED)   {
    if (connectioWasAlive == true)     {
      connectioWasAlive = false;
      Serial.print("Looking for WiFi ");
    }
    Serial.print(".");
    delay(500);
  }  else if (connectioWasAlive == false)  {
    connectioWasAlive = true;
    Serial.printf(" connected to %s\n", WiFi.SSID().c_str());
  }
}

//==================================================================================================================================================================== 
//========================================================================================================================================================================
void loop() {
   monitorWiFi();

String IncoStr="";
boolean StringReady = false;
int in1=0;
int in2=0;
int ih1=0;
int ih2=0;
int it1=0;
int it2=0;

int N1=NULL;   
int H1=NULL;
float T1=NULL;

String strN1="";
String strH1="";
String strT1="";
//===============================================================================
//                  IncoStr="#333#%77%*55.5*";
//                  StringReady = true;
//===============================================================================
while (Serial.available())  {
   IncoStr = Serial.readStringUntil('\r\n');   
   StringReady = true;
}
 delay(10);

 
if (StringReady){
    Serial.println("*True*" );
    if (IncoStr.length()>12 && IncoStr.length()<24 ){
       in1 = IncoStr.indexOf("#");
       in2 = IncoStr.lastIndexOf("#");
       ih1 = IncoStr.indexOf("%");
       ih2 = IncoStr.lastIndexOf("%");
       it1 = IncoStr.indexOf("*");
       it2 = IncoStr.lastIndexOf("*");
       //Serial.println(it1); 
       //Serial.println(it2); 
        if ( (in2-in1) >2  && (in2-in1) <10 ) {
            strN1 = IncoStr.substring(in1+1, in2);
            N1 =  strN1.toInt();                      //Serial.println(strN1); 
          
        }
        if ( (ih2-ih1) >0  && (ih2-ih1) <4  ) {
            strH1 = IncoStr.substring(ih1+1, ih2);
            H1 =  strH1.toInt();                      //Serial.println(strH1); 
         
        }
        if ( (it2-it1)>0  && (it2-it1) <7  ) {
            strT1 = IncoStr.substring(it1+1, it2);
            char carray[strT1.length() + 1];
                                                      //Serial.println(strT1); 
            strT1.toCharArray(carray, sizeof(carray));
            T1 =  atof( carray );                     //Serial.println(strT1); 
          
        }
  //     delay(10);
       Serial.println("---" + IncoStr + "---");

monitorWiFi();

    if (N1!=0 && H1!=0 && T1!=0) {
//      Serial.println("Connecting...");
        Serial.println("-1-");
        clnt1.connect(srv_ip, 80);
        delay(2000);
        String msg = "GET /tg_ins.php?tbl="+String(mac[0], HEX)+"-"
                                           +String(mac[1], HEX)+"-"
                                           +String(mac[2], HEX)+"-"
                                           +String(mac[3], HEX)+"-"
                                           +String(mac[4], HEX)+"-"
                                           +String(mac[5], HEX)
                       +"&h1="+String(H1)+
                       +"&t1="+String(T1);
        // Для отладки включим отправку данных в COM порт
        Serial.println(msg);
        clnt1.println(msg);
        
       //потом отключаемся
        clnt1.stop();
        Serial.println("-2-");
           
    }
  }    
}
//======================================================================================================================= 
delay(1000);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


