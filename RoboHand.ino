#include <Servo.h>
Servo myservo_thumb;
Servo myservo_index;
Servo myservo_middle;
Servo myservo_ring;
Servo myservo_pinkie;
char serialData;

void setup()
{
  Serial.begin(9600);
  //Servo start
  myservo_thumb.write(0);
  myservo_index.write(0);
  myservo_middle.write(0);
  myservo_ring.write(0);
  myservo_pinkie.write(0);

  myservo_thumb.attach(11);
  myservo_index.attach(10);
  myservo_middle.attach(9);
  myservo_ring.attach(6);
  myservo_pinkie.attach(5);
}

void loop()
{

  if (Serial.available() > 0)
  {
    serialData = Serial.read();

    //Servos make a Open all
    if (serialData == 'a')
    {
      myservo_thumb.write(90);
      myservo_index.write(90);
      myservo_middle.write(90);
      myservo_ring.write(90);
      myservo_pinkie.write(90);
      delay(1000);
    }
    //Servos make a Closing all
    else if (serialData == 'b')
    {
      myservo_thumb.write(0);
      myservo_index.write(0);
      myservo_middle.write(0);
      myservo_ring.write(0);
      myservo_pinkie.write(0);
      delay(1000);
    }
  }
}
