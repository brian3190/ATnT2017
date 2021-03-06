/***************************************************************************************************************
 *  Air Pollution Sensor Musing NodeMCU ESP-12 Develop Kit V1.0
 *  DHT connected to NodeMCU pin D3
 *  MQ-135 connected to A0
 *  Sensor Data on local OLED Display
 *  Sensor data sent to Thingspeak Channel: https://thingspeak.com/channels/135305 
 *  Sensor data sent to Blynk app
 *  Downloads, docs, tutorials: http://www.blynk.cc
 *  Version Blynk&TS - Developed by Kam 11 Aug 2017
 ********************************************************************************************************************************/
#define SW_VERSION "(Blynk & TS)" // SW version will appears at innitial LCD Display

/* ESP */
#include <ESP8266WiFi.h>
#include "MQ135.h"
WiFiClient client;
#define ANALOGPIN A0

/* Blynk */
#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <BlynkSimpleEsp8266.h>
char auth[] = "777d4648b51a4635b24578a90f4de2e3";
char ssid[] = "MyDD2017";
char pass[] = "mydd@2017";
MQ135 gasSensor = MQ135(ANALOGPIN);

/* Thinkspeak*/
const char* TS_SERVER = "api.thingspeak.com";
String TS_API_KEY ="POL8W5JHBPYFUPEP";

/* OLED */
#include <ACROBOTIC_SSD1306.h> // library for OLED: SCL ==> D1; SDA ==> D2
#include <SPI.h>
#include <Wire.h>

/* DHT22*/
#include "DHT.h"
#define DHTPIN D3  
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
float hum = 0;
float temp = 0;

/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;

/* Air Pollution */
//#define soilMoisterPin A0

#define ANALOGPIN A0
#define soilMoisterVcc D4
int soilMoister = 0;

void setup()
{
  pinMode(soilMoisterVcc, OUTPUT);
  Serial.begin(115200);
  delay(10);
  Blynk.begin(auth, ssid, pass);
  oledStart();
  dht.begin();
  timer.setInterval(2000L, getDhtData);
  //timer.setInterval(7000L, getSoilMoisterData);
  timer.setInterval(7000L, getMQ135Data);
  timer.setInterval(5000L, sendUptime);
  timer.setInterval(19000L, sendDataTS);
  digitalWrite (soilMoisterVcc, LOW);
}

void loop()
{
  displayData();
  timer.run(); // Initiates SimpleTimer
  Blynk.run();
}

/***************************************************
 * Get DHT data
 **************************************************/
void getDhtData(void)
{
  float tempIni = temp;
  float humIni = hum;
  temp = dht.readTemperature();
  hum = dht.readHumidity();
  if (isnan(hum) || isnan(temp))   // Check if any reads failed and exit early (to try again).
  {
    Serial.println("Failed to read from DHT sensor!");
    temp = tempIni;
    hum = humIni;
    return;
  }
}

/***************************************************
 * Get MQ 135 Sensor data
 **************************************************/
void getMQ135Data(void)
{
  //soilMoister = 0;
  MQ135 = 0;
  digitalWrite (soilMoisterVcc, HIGH);
  delay (500);
  int N = 3;
  for(int i = 0; i < N; i++) // read sensor "N" times and get the average
  {
    //soilMoister += analogRead(soilMoisterPin);   
    MQ135 += analogRead(MQ135Pin);
    delay(150);
  }
  digitalWrite (soilMoisterVcc, LOW);
  //soilMoister = soilMoister/N; 
  MQ135 = MQ135/N;
  //Serial.println(soilMoister);
  Serial.println(MQ135);
  //soilMoister = map(soilMoister, 380, 0, 0, 100);
MQ135 = map(MQ135, 380, 0, 0, 100);
}

/***************************************************
 * Send DHT data to Blynk
 **************************************************/
void sendUptime()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(10, temp); //virtual pin V10
  Blynk.virtualWrite(11, hum); // virtual pin V11
  Blynk.virtualWrite(12, MQ135); // virtual pin V12
}


/***************************************************
 * Start OLED
 **************************************************/
void oledStart(void)
{
  Wire.begin();  
  oled.init();                      // Initialze SSD1306 OLED display
  clearOledDisplay();
  //oled.setFont(font5x7);            // Set font type (default 8x8)
  oled.clearDisplay();              // Clear screen
  oled.setTextXY(0,0);              
  oled.putString("Plant Monitor");
  oled.setTextXY(1,0);              
  oled.putString(String(SW_VERSION));
}

/***************************************************
 * Display data at Serial Monitora & OLED Display
 **************************************************/
void displayData(void)
{ 

  Serial.print(" Temperature: ");
  Serial.print(temp);
  Serial.print("oC   Humidity: ");
  Serial.print(hum);
  Serial.print("%    Air Pollution: ");
  Serial.print(MQ135);
  Serial.println("PPM");
  
  oled.setTextXY(3,0);              // Set cursor position, start of line 2
  oled.putString("Temp: " + String(temp) + " oC");
  oled.setTextXY(5,0);              // Set cursor position, start of line 2
  oled.putString("Hum:  " + String(hum) + " %");
  oled.setTextXY(7,0);              // Set cursor position, start of line 2
  //oled.putString("MQ135: " + String(soilMoister) + " %");
  oled.putString("MQ135: " + String(MQ135) + " %");
}

/***************************************************
 * Clear OLED Display
 **************************************************/
void clearOledDisplay()
{
  oled.setFont(font8x8);
  oled.setTextXY(0,0); oled.putString("                ");
  oled.setTextXY(1,0); oled.putString("                ");
  oled.setTextXY(2,0); oled.putString("                ");
  oled.setTextXY(3,0); oled.putString("                ");
  oled.setTextXY(4,0); oled.putString("                ");
  oled.setTextXY(5,0); oled.putString("                ");
  oled.setTextXY(6,0); oled.putString("                ");
  oled.setTextXY(7,0); oled.putString("                ");
  oled.setTextXY(0,0); oled.putString("                ");              
}

/***************************************************
 * Sending Data to Thinkspeak Channel
 **************************************************/
void sendDataTS(void)
{
   if (client.connect(TS_SERVER, 80)) 
   { 
     String postStr = TS_API_KEY;
     postStr += "&field1=";
     postStr += String(temp);
     postStr += "&field2=";
     postStr += String(hum);
     postStr += "&field3=";
     //postStr += String(soilMoister);
     postStr += String(MQ135);
     postStr += "\r\n\r\n";
   
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: " + TS_API_KEY + "\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(postStr.length());
     client.print("\n\n");
     client.print(postStr);
     delay(1000); 
   }
   client.stop();
}
