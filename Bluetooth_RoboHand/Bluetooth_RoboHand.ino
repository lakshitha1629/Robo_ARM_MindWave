/*
When the brains Attention is high, this code will move a servo attached to the 
throttle joystick of a drone controller and turn 2 LEDs on. December 26, 2020.
     Yellow LED on when Attention is more than 50
     Green LED on when Attention is more than 70
     Servo moves to position set by potentiometer (between 0 and 30 degrees)

Hardware: Arduino with HC-05 Bluetooth and NeuroSky MindWave Mobile 2 
*/

#include <Servo.h>
#define BAUDRATE 57600
#define YLED 4
#define GLED 2

//////////    Variables
Servo myservo;
byte payloadData[32] = {0};
byte Attention = 0;
byte checksum = 0;
byte generatedchecksum = 0;
int Plength;
int val;         // variable to read the value from the analog pin
int val2;        // variable to hold temporary value for gradual ascent
int countup = 0; // counter for steps in gradual ascent
int potpin = 0;  // analog pin used to connect the potentiometer

//////////    Arduino setup
void setup()
{
  Serial.begin(BAUDRATE); // baud rate for the MindWave
  pinMode(YLED, OUTPUT);  // initialize the LED pins as output
  pinMode(GLED, OUTPUT);
  Serial.println("Attention Values"); // display title in Serial Monitor
  myservo.attach(9);                  // attach the servo on pin 9 to the servo object
  myservo.write(0);                   // move the servo to 0 degrees
  delay(15);                          // give the servo time to move there
}

//////////    Read data from the MindWave
byte ReadOneByte()
{
  int ByteRead;
  while (!Serial.available());
  ByteRead = Serial.read();
  return ByteRead;
}

//////////    Main program
void loop()
{

  //////    Look for sync bytes and read data from the MindWave
  while (1)
  {
    if (ReadOneByte() == 170)
    {
      if (ReadOneByte() == 170)
      {
        Plength = ReadOneByte();
        Serial.println(Plength);
        if (Plength == 32)
        {
          generatedchecksum = 0;
          for (int i = 0; i < Plength; i++)
          {
            payloadData[i] = ReadOneByte(); //Read payload into memory
            generatedchecksum += payloadData[i];
          }
          generatedchecksum = 255 - generatedchecksum;
          checksum = ReadOneByte();

          //////    Obtain Attention data and display it in the Serial Monito
          if (checksum == generatedchecksum)
          {
            if (payloadData[28] == 4)
            {
              Attention = payloadData[29];
              Serial.println(Attention, DEC);

              //////    Light LEDs and move the servo
              if (Attention > 50)
              {
                Serial.println("Attention 50");
                digitalWrite(YLED, HIGH);       // turn yellow LED on
                val = analogRead(potpin);       // read the value of the potentiometer
                                                // (value between 0 and 1023)
                                                // The potentiometer adjusts the maximum throttle. With a fully
                                                // charged drone battery, the potentiometer should be at its
                                                // mid-point. As the drones battery is being used up, the
                                                // potentiometer should be turned higher.
                val = map(val, 0, 1023, 0, 30); // scale it to use it with the servo
                                                // (value between 0 and 30)
                                                // This makes the servo move a maximum of 30 degrees. My
                                                // throttle joystick doesnt allow any more movement than that.

                //// gradual ascent, slowly increasing the throttle
                if (countup == 0)
                {
                  countup = 1; // First, set throttle to 30% for 0.3 seconds
                  val2 = val * 0.3;
                  myservo.write(val2);
                  delay(300);
                }
                else
                {
                  if (countup == 1)
                  {
                    Serial.println("countup 1");
                    countup = 2; // Now, set throttle to 50% for 0.3 seconds
                    val2 = val * 0.5;
                    myservo.write(val2);
                    delay(300);
                  }
                  else
                  {
                    if (countup == 2)
                    {
                      Serial.println("countup 1");
                      countup = 3; // Then, set throttle to 70% for 0.3 seconds
                      val2 = val * 0.7;
                      myservo.write(val2);
                      delay(300);
                    }
                    else
                    {
                      if (countup == 3)
                      {
                        Serial.println("countup 1");
                        myservo.write(val); // Finally, set throttle to 100%
                        delay(15);
                      }
                      else
                      {
                      }
                    }
                  }
                }
              }
              else
              {
                digitalWrite(YLED, LOW); // turn yellow LED off if Attention is 50 or lower
                countup = 0;             // reset the counter
                myservo.write(0);        // set throttle to 0
                delay(15);
              }
              if (Attention > 70) // turn green LED on if Attention is over 70
              {
                digitalWrite(GLED, HIGH);
              }
              else // turn green LED off if Attention is 70 or lower
              {
                digitalWrite(GLED, LOW);
              }
            }
          }
        }
      }
    }
  }
}
