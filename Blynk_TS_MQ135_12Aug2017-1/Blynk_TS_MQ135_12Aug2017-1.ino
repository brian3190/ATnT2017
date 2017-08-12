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
int mq135;

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
  
  
 
  //timer.setInterval(7000L, getSoilMoisterData);
 
  digitalWrite (soilMoisterVcc, LOW);
}

void loop()
{
  displayData();

  Blynk.run();
}


/***************************************************
 * Get MQ 135 Sensor data
 **************************************************/
void getMQ135Data(void)
{
  
  mq135 = analogRead(4);       // read analog input pin 0
  Serial.println(mq135, DEC);  // prints the value read
  delay(1000);                        // wait 100ms for next reading
  {
    //soilMoister += analogRead(soilMoisterPin);   
    
    delay(150);
  }
  
}

/***************************************************
 * Send DHT data to Blynk
 **************************************************/
void sendUptime()
{
 
  
}



/***************************************************
 * Display data at Serial Monitora & OLED Display
 **************************************************/
void displayData(void)
{ 

 
 
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
