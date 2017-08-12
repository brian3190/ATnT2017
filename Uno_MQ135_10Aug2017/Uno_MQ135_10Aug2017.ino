
#include "MQ135.h"
#define ANALOGPIN A4

MQ135 gasSensor = MQ135(ANALOGPIN);


int mq135;


void setup()
{
  Serial.begin(115200);      // sets the serial port to 115200
}

void loop()
{
  mq135 = analogRead(4);       // read analog input pin 4

   
  //Serial.print("reading = ");
  //Serial.println(mq135, DEC);  // prints the value read

  float rzero = gasSensor.getRZero(); //this to get the rzero value
  float ppm = gasSensor.getPPM(); // this to get ppm value


  //Serial.print("rzero = ");
  //Serial.println(rzero); // this to display the rzero value continuously, uncomment this to get ppm value
  
  Serial.print("PPM = ");
  Serial.println(ppm*1667); // this to display the ppm value continuously, uncomment this to get rzero value

  Serial.println(" ");
  
  delay(5000);                        // wait 6000ms for next reading



  
}
