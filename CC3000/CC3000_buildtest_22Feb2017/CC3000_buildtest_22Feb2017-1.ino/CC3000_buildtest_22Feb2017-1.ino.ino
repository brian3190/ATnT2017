#include <SPI.h>
 #include <Adafruit_CC3000.h>
 #include <IPStack.h>
 #include <Countdown.h>
 #include <MQTTClient.h>
 
 #define MS_PROXY                "tfj1f0.messaging.internetofthings.ibmcloud.com"
 #define MQTT_PORT               1883
 #define MQTT_MAX_PACKET_SIZE    100
 #define MQTT_CLIENT_ID          "d:tfj1f0:iotsample-arduino:08002857A450"               // d:org_id:device_type:device_id, d - device, <org_id>, <device_type>, <device_id>
 #define MQTT_TOPIC              "iot-2/evt/status/fmt/json"
 #define AUTHMETHOD              "use-token-auth"
 #define AUTHTOKEN               "XXXXXXXXXXXXX"
 byte mac[] = { 0x08, 0x00, 0x28, 0x57, 0xA4, 0x50 };                                    // consistent with <device_id>
 
 //For Arduino Yun, instantiate a YunClient and use the instance to declare
 //an IPStack ipstack(c) instead of EthernetStack with c being the YunClient
 // e.g. YunClient c;
 // IPStack ipstack(c);
 // EthernetClient c;            // replace by a YunClient if running on a Yun
 Adafruit_CC3000_Client c;
 IPStack ipstack(c);
 
 MQTT::Client<IPStack, Countdown, 100, 1> client = MQTT::Client<IPStack, Countdown, 100, 1>(ipstack);
 
 // Wifi/WLAN
 #define WLAN_SSID       "Aurora"
 #define WLAN_PASS       "63Fj*4Jbe"
 #define WLAN_SECURITY   WLAN_SEC_WPA2                           // Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
 
 // CC3000
 #define ADAFRUIT_CC3000_IRQ     3                               // MUST be an interrupt pin!
 #define ADAFRUIT_CC3000_VBAT    5                               // Can be any pin
 #define ADAFRUIT_CC3000_CS      10                              // Can be any pin
 // Use hardware SPI for the remaining pins, for UNO, SCK = 13, MISO = 12, MOSI = 11
 Adafruit_CC3000                 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT, SPI_CLOCK_DIVIDER); // you can change this clock speed but DI
 
 const int inputPin = 9; // la pin sur laquel la sortie du micro est branchée
 
 void setup() {
   
   pinMode(inputPin, INPUT);
   
   Serial.begin(9600);
 
   if (!cc3000.begin())
   {
     Serial.println(F("Unable to initialise the CC3000! Check your wiring?"));
     while (1);
   }
   displayMACAddress();
 
   // connect to Wifi
   cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
   while (!cc3000.checkDHCP())                                   // wait until get DHCP address
     delay(100);
 }
 
 
 void loop() {
   int rc = -1;
   if (!client.isConnected()) {
     Serial.println("Connecting to IoT Foundation for publishing Sound");
     while (rc != 0) {
       rc = ipstack.connect(MS_PROXY, MQTT_PORT);
     }
     Serial.println("TCP connected");
 
     MQTTPacket_connectData options = MQTTPacket_connectData_initializer;
     options.MQTTVersion = 3;
     options.clientID.cstring = MQTT_CLIENT_ID;
     options.username.cstring = AUTHMETHOD;
     options.password.cstring = AUTHTOKEN;
     options.keepAliveInterval = 10;
     rc = -1;
     while ((rc = client.connect(options)) != 0 )
     {
       Serial.print("rc=");
       Serial.println(rc);
       delay (2000);
     }
     Serial.println("MQTT connected");
 
     Serial.println("Connected successfully\n");
     Serial.println("____________________________________________________________________________");
   }
 
   MQTT::Message message;
   message.qos = MQTT::QOS0;
   message.retained = false;
   
   char json[41] = "{\"d\":{\"myRoom\":\"5001\",\"mySound\":"; // Remplacer le numéro après myRoom par l'identifiant de la salle
   float val = digitalRead(inputPin);
   if (val == HIGH) {
     json[32] = '1';
   } else {
     json[32] = '0';
   }
   json[33] = '}';
   json[34] = '}';
   json[35] = '\0';
   Serial.print("\t");
   Serial.print(val);
   Serial.print("\t\t");
   Serial.println(json);
   Serial.print("\t");
   message.payload = json;
   message.payloadlen = strlen(json);
 
   rc = client.publish(MQTT_TOPIC, message);
   if (rc != 0) {
     Serial.print("return code from publish was ");
     Serial.println(rc);
   }
   client.yield(1000);
 }
 
 
 /**************************************************************************/
 /*!
     @brief  Tries to read the 6-byte MAC address of the CC3000 module
 */
 /**************************************************************************/
 void displayMACAddress(void)
 {
   uint8_t macAddress[6];
 
   if(!cc3000.getMacAddress(macAddress))
   {
     Serial.println(F("Unable to retrieve MAC Address!\r\n"));
   }
   else
   {
     Serial.print(F("MAC Address : "));
     cc3000.printHex((byte*)&macAddress, 6);
   }
 }
