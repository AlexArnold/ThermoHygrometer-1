//-------------------- ESP8266 ESP-12F ---------------------------------------
//         ДЛЯ прошивки
// GPIO0 — подключен через выключатель к земле(GND) для включения режима ПЕРЕПРОШИВКИ модуля. 
//         Для обычного старта модуля GPIO0 можно оставить никуда не подключенным
// ESP8266  TX ---> RX  == USB-UART / USB-TTL конвертер на чипе CP2102
// ESP8266  RX ---> TX  == USB-UART / USB-TTL конвертер на чипе CP2102
// ESP8266  GND --> GND == USB-UART ---> Power GND
// ESP8266  VCC --> +

//         ДЛЯ работы 
// GPIO0 — отключен
// ESP8266  TX ---> pin 3 == Arduino NANO 
// ESP8266  RX ---> pin 8 == Arduino NANO
// ESP8266  GND --> GND == Arduino NANO ---> Power GND
// ESP8266  VCC --> +
//----------------------------------------------------------  
//        2 - DHT22 input
// 4 pin GND --> GND
// 3 pin  n.c.
// 2 pin DATA <---> 10kOm <---> +3.3v-5.5v 
// 1 pin VCC  --> +
//----------------------------------------------------------
//        10 - LCD5110
// RST ---> pin 9 
// CE ---> pin 10
// DC ---> pin 7
// DIN ---> pin 6
// CLK ---> pin 5
// VCC --->    +3.3v
// LIGHT --->  GND
// GND --->    GND
//----------------------------------------------------------
//        4 - SD-Card
// MOSI - pin 17                                          /////// MOSI - pin 11 
// MISO - pin 18                                          /////// MISO - pin 12
// CLK - pin 19                                           /////// CLK - pin 13
// CS -  pin 4 
//------------------------
#include <LCD5110_Basic.h>
#include "DHT.h"
#include <SPI.h>
#include <DS3231.h>
//#include <SD.h>
#include <SoftwareSerial.h>
//#include "nRF24L01.h"  
//#include "RF24.h"  
#include "printf.h"

//============= DHT  (AM2302), AM2321 =====================================
#define DHTPIN5 2                  // what digital pin we're connected to
#define DHTTYPE DHT22              // DHT 22  (AM2302), AM2321
DHT Dht5(DHTPIN5, DHTTYPE);
//============= LCD NOKIA 5110 ============================================
///////////////////////////////////// LCD5110 myGLCD(8, 9, 10, 11, 12);
LCD5110 myGLCD(5, 6, 7,    9, 10);
//============= RTC DS3231 + EEPROM 24C32 32K =============================
DS3231  rtc(SDA, SCL);
//Time t; // Инициализация структуры 
//------- nRF24L01 --------------------  
//const uint64_t pipe = 0xE8E8F0F0E1LL;  
//RF24 radio(8, 3); // CE, CSN
//int joystick[4];  
//int counter = 0; 

//============= Arduino NANO ===> отправляет на => WIFI ESP8266 ==========
SoftwareSerial esp8266(3, 8); // RX, TX    

// ------------------------------------
//bool isSD = false; // Флаг присутствия карты
//bool isRF = false;

//========================================================================================================================================
void setup(){
  esp8266.begin(9600);
                                           Serial.begin(9600);
///////////////////////////////////// SPI.begin();
pinMode(3, OUTPUT); // RF
pinMode(8, OUTPUT); // RF
pinMode(4, OUTPUT); // SD 

///////////////////////////////////// printf_begin();
  Serial.println("setDHT22");
  setDHT22();
  Serial.println("setLCD");
  setLCD();
  Serial.println("setRTC");
  setRTC();

  Serial.println("setSD");
  //setSD();
  //setNRF24();
  
////////////////////////////////////// digitalWrite(8, LOW);   //select
////////////////////////////////////// digitalWrite(8, HIGH);  //de-select
} 
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// -------- DHT22 -------- 
void setDHT22(){
  Dht5.begin();
}

// -------- LCD5110 -------- 
void setLCD(){
  myGLCD.InitLCD();  
}

// -------- RTC -------
void setRTC(){
  rtc.begin();
  //////////////////////////////rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  //rtc.setDate(14, 07, 2017);   // Set the date to January 1st, 2014
  //rtc.setTime(11, 44, 30);      // Set the time to 12:00:00 (24hr format)  
}

// -------- setup MicroSD-Card --------
//void setSD(){
// digitalWrite(4,LOW); //  Для SD
////////////////////////////////////////  pinMode(4,LOW); //  Для SD
//  if (!SD.begin(4)) {     // PIN 4
////     ///////////////////////////////  isSD = false;
//     Serial.println("InitSDCard Failed");
//  }else{
//     Serial.println("InitSDCard -Trued-.");
//  }
//  digitalWrite(4, HIGH); // CSN
//  
//}

// ------- nRF24L01 -------- 
//void setNRF24(){
//  radio.begin();
//  radio.powerUp();
//  delay(10);
//  
//  radio.setPALevel(RF24_PA_MAX); // мощьность передатчика, RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MAX       After you have good 3.3V power, set the RF "Power Amplifier Level" to MAX
//  radio.setDataRate(RF24_250KBPS); // скорость, RF24_250KBPS, RF24_1MBPS или RF24_2MBPS  RF24_250KBPS на nRF24L01 (без +) неработает.  меньше скорость, выше чувствительность приемника.
////////////////////////////  radio.setAutoAck(1); // Ensure autoACK is enabled
////////////////////////////  radio.setChannel(100); // канал (0-127)
////////////////////////////  radio.setCRCLength(RF24_CRC_8);  // length: RF24_CRC_8 for 8-bit or RF24_CRC_16 for 16-bit Cyclic Redundancy Check (Error checking)
//  radio.setRetries(15,15); // Set the number and delay of retries upon failed transmit. Parameters: delay: How long to wait between each retry, in multiples of 250us, max is 15. 0 means 250us, 15 means 4000us. count: How many retries before giving up, max 15
//    
//  radio.openWritingPipe(pipe);  
//////////////////////////  //radio.powerDown();  
//}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//==================================================================================================================================
//==================================================================================================================================
void loop(){ 
  delay(10);
  myGLCD.clrScr();
  Serial.print("myGLCD.clrScr");
extern uint8_t SmallFont[];
//extern uint8_t TinyFont[];
extern uint8_t MediumNumbers[];
//extern uint8_t BigNumbers[]; 

//---------------------------- pin-2 DHT-22 ----------------------------------
 int h5 = Dht5.readHumidity();
 float t5 = Dht5.readTemperature();
  if (isnan(h5) || isnan(t5) ) {
      //h5=-111;
      //t5=-111;
      h5=111;
      t5=111;
  }
  Serial.print(rtc.getDateStr());
  Serial.print("; ");
  Serial.print(rtc.getTimeStr());  
  Serial.print("; ");
  
  Serial.print(h5);
  Serial.print("; ");
  Serial.print(t5);
  Serial.print("; ");
  
 myGLCD.setFont(SmallFont);
 myGLCD.print("Rh %", 0, 0);
 myGLCD.print("T C~", 0, 22);

 myGLCD.setFont(MediumNumbers);
 myGLCD.printNumI(h5, 36, 0);
 myGLCD.printNumF(t5, 2, 36, 22);

 myGLCD.setFont(SmallFont);
 Time t; // Инициализация структуры 
 t = rtc.getTime(); // Получение времени и его запись в структуру t
  myGLCD.printNumI(int(t.hour), 0, 35); // Вывод часов
 myGLCD.print(":", 12, 35);
 myGLCD.printNumI(int(t.min), 18, 35); // Вывод минут
 
 myGLCD.print(rtc.getDateStr(), 0, 45);
   delay(100);


//============================= nRF24L01 ==============================================
  Serial.println("; ");
//  digitalWrite(4,HIGH);

//  digitalWrite(8,LOW);
//  digitalWrite(3,LOW);
//  delay(15);
////////////  radio.powerUp();
////////////
////////////  //radio.printDetails();
////////////  delay(1000);
////////////  joystick[0] = counter;  
////////////  joystick[1] = counter + 1;  
////////////  joystick[2] = counter + 2;  
////////////  joystick[3] = counter + 3;  
////////////
////////////  isSD = radio.write(joystick, sizeof(joystick));  
////////////  if (isSD == 1) {
////////////        myGLCD.print("   Ok", RIGHT, 45);
////////////  }else{
////////////        myGLCD.print("Error", RIGHT, 45);
////////////  }
////////////  delay(100);
////////////  
////////////  Serial.println(isSD);
////////////  counter++;
////////////  radio.powerDown();

  
//delay(100);

//  digitalWrite(8,HIGH);
//  digitalWrite(3,HIGH);

//============================= CD-Card ===============================================
//   digitalWrite(4, LOW);  // В-ключить SD
//   delay(15);
//   File dataFile = SD.open("test.csv", FILE_WRITE);
//   delay(100);
//  if (dataFile) {
//    dataFile.print(h5);
//    dataFile.print("; ");
//    dataFile.println(t5);
//    dataFile.close();
//    myGLCD.print("  .", 66, 45);
//    Serial.println("; true FW");
//  } else {
//    myGLCD.print("Err", 66, 45);
//    Serial.println("; Error FW");
//  }
//  digitalWrite(4, HIGH);
  
//====================================================================================  
  esp8266.println("");
  esp8266.print("#");
  esp8266.print("123");
  esp8266.print("#");
  esp8266.print("%");
  esp8266.print(h5);
  esp8266.print("%");
  esp8266.print("*");
  esp8266.print(t5);
  esp8266.println("*");    
//  
//  esp8266.println("");
//  esp8266.print("#");
//  esp8266.print("456");
//  esp8266.print("#");
//  esp8266.print("%");
//  esp8266.print("61");
//  esp8266.print("%");
//  esp8266.print("*");
//  esp8266.print("17.7");
//  esp8266.println("*");     


//---------------------------------------------------------------------------
  delay(60000);
}



