#include "MQ135.h"
int MQ135;

void setup()
{
  Serial.begin(115200);      // sets the serial port to 9600
}

void loop()
{
  MQ135 = analogRead(4);       // read analog input pin 0
  Serial.println(MQ135, DEC);  // prints the value read
  delay(1000);                        // wait 100ms for next reading
}
