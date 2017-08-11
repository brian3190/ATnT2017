int mq135;

void setup()
{
  Serial.begin(115200);      // sets the serial port to 9600
}

void loop()
{
  mq135 = analogRead(4);       // read analog input pin 0
  Serial.println(mq135, DEC);  // prints the value read
  delay(100);                        // wait 100ms for next reading
}
