/*
----------------------------------------------------------------------------
Falcon Starter Kit V1.0
----------------------------------------------------------------------------

Grove Button & Touch -> Buzzer
Turns buzzer music that connected to digital pin 8, when pressing a Pushbutton attached to pin 2 or Touchbutton 
attach to pin 7.

Grove - Light Sensor
when the value of light sensor ledd than a certain value
led will on, you can set this certain value via change thresholdvalue
such as when you cover light sensor with your hand, you'll find led on

Grove Rotary Angle Sensor
Turn the rotary, the value will vary from 0 to 1023

Grove Sound Sensor
when sound larger than a certain value, led will on

Grove Temperature Sensor
Sense the temperature
*/

//Groove Button, Touch & Buzzer
//constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int touchPin = 7;
int Buzzer1 = 8;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int touchState = 0;



//Light Sensor
const int pinLight = A0;
const int pinLed2   = 4;
int thresholdvalue=400;                 //the threshold to turn on or off the LED


//Rotary Angle Sensor
const int potentiometer = A1;                    // rotary angle sensor connect to A1

//Sound Sensor
const int pinSound = A2;               // pin of Sound Sensor
const int pinLed3   = 3;                // pin of LED
int thresholdValue = 500;                 // the threshold to turn on or off the LED

//Temperature Sensor
const int pinTemp = A3;      // pin of temperature sensor
float temperature;
int B=3975;                  // B value of the thermistor
float resistance;

void setup()
{

//----------------------------------------------------------------------------------------------------
    //Button, Touch & Buzzer

    // initialize the piezo as output:
  pinMode(Buzzer1, OUTPUT);  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  // initialize the pushbutton pin as an input:
  pinMode(touchPin, INPUT);     

    //Light Sensor
    pinMode(pinLed2, OUTPUT);             //set the LED on Digital 12 as an OUTPUT

    //Rotary Angle Sensor
    Serial.begin(115200);                         // set the serial communication frequency at 9600 bits per sec
    pinMode(potentiometer, INPUT);

    //Sound Sensor
    pinMode(pinLed3, OUTPUT);            //set the LED on Digital 12 as an OUTPUT
//---------------------------------------------------------------------------------------------------------------

}

void loop()
{

//-------------------------------------------------------------------------------------------------------  
  //Button, Touch & Buzzer

// read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // read the state of the touchbutton value:
  touchState = digitalRead(touchPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState or touchState is HIGH:

  if (buttonState == HIGH || touchState == HIGH) {     
    // play th Music
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,450,225);
      delay(300);
      tone(Buzzer1,450,225);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,450,200);
      delay(300);
      tone(Buzzer1,600,300);
      delay(300);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,700,300);
      delay(300);
      tone(Buzzer1,700,300);
      delay(500);
      tone(Buzzer1,600,300);
      delay(300);
      tone(Buzzer1,400,200);
      delay(1000);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,650,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,650,200);
      delay(300);
      tone(Buzzer1,650,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(1000);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,600,300);
      delay(500);
      tone(Buzzer1,600,300);
      delay(500);
      tone(Buzzer1,800,300);
      delay(500);
      tone(Buzzer1,800,300);
      delay(500);
      tone(Buzzer1,400,200);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,400,200);
      delay(500);
      tone(Buzzer1,300,150);
      delay(500);
      tone(Buzzer1,300,150);
      delay(500);
      tone(Buzzer1,300,150);
      delay(500);
      tone(Buzzer1,300,150);
      delay(500);
      tone(Buzzer1,300,150);
      tone(Buzzer1,300,150);
      tone(Buzzer1,300,150);
      tone(Buzzer1,300,150);  

  } 


    //Light Sensor
    int sensorValue = analogRead(pinLight);    //the light sensor is attached to analog 0
    if(sensorValue<thresholdvalue)
    {
        digitalWrite(pinLed2, HIGH);
    }
    else
    {
        digitalWrite(pinLed2, LOW);
    }

    
    //Rotary Angle Sensor
    int value = analogRead(potentiometer);
    Serial.print("Rotary: ");
    Serial.println(value);                      // pirnt the value on the serial monitor screen
    delay(100);                                  // wait 1000ms before printing next value

    //Sound Sensor
    int sensorValue2 = analogRead(pinSound);   //read the sensorValue on Analog 0
    if(sensorValue2>thresholdValue)
    digitalWrite(pinLed3,HIGH);
    delay(200);
    digitalWrite(pinLed3,LOW);

    //Temperature Sensor
    int val = analogRead(pinTemp);                               // get analog value
    resistance=(float)(1023-val)*10000/val;                      // get resistance
    temperature=1/(log(resistance/10000)/B+1/298.15)-273.15;     // calc temperature
    Serial.print("Temperature reading = ");
    Serial.print(temperature);
    Serial.println(" degrees C");
    delay(1000);          // delay 1s
//-------------------------------------------------------------------------------------------------------
    
}
