#include "MQ135.h"
#include "CayenneDefines.h"
#include "CayenneWiFi.h"
#include "CayenneWiFiClient.h"
#define CAYANNE_DEBUG
#define CAYANNE_PRINT Serial
#define VIRTUAL_PIN 5
#define ANALOGPIN A0

char token[] = ""; // Insert your token here
char ssid[] = ""; // Insert your SSID here
char pwd[] = ""; // Insert your SSID password here
MQ135 gasSensor = MQ135(ANALOGPIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Cayenne.begin(token, ssid, pwd);
}

void loop() {
  // put your main code here, to run repeatedly:
  Cayenne.run();
//  float rzero = gasSensor.getRZero(); //this to get the rzero value, uncomment this to get ppm value
//  float ppm = gasSensor.getPPM(); // this to get ppm value, uncomment this to get rzero value
//  Serial.println(rzero); // this to display the rzero value continuously, uncomment this to get ppm value
//  Serial.println(ppm); // this to display the ppm value continuously, uncomment this to get rzero value
//  Cayenne.virtualWrite(VIRTUAL_PIN,ppm); // uncomment after rzero define and get your ppm calculation
}
