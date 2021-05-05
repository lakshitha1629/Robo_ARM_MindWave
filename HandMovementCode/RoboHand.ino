#include <Servo.h>
Servo myservo_thumb;
Servo myservo_index;
Servo myservo_middle;
Servo myservo_ring;
Servo myservo_pinkie;
char serialData;
boolean flag = false;

void setup() {
        Serial.begin(9600);       
        myservo_thumb.attach(11);
        myservo_index.attach(10);
        myservo_middle.attach(9);
        myservo_ring.attach(6);
        myservo_pinkie.attach(5);
}

void loop() {
//Servo start
          myservo_thumb.write(0);
          myservo_index.write(0);
          myservo_middle.write(0);
          myservo_ring.write(0);
          myservo_pinkie.write(0);
          
  if(Serial.available()) {
         serialData = Serial.read();
         
        if (serialData == 'a') 
        {         
          myservo_index.write(90);
          flag=true;
        }
        if (serialData == 'b') 
        {         
          myservo_middle.write(90);
          flag=true;
        }
        if (serialData == 'c') 
        {         
          myservo_ring.write(90);
          flag=true;
        }
        if (serialData == 'd') 
        {         
          myservo_pinkie.write(90);
          flag=true;
        }
        if (serialData == 'e') 
        {         
          myservo_thumb.write(90);
          flag=true;
        }
        
        //Servos make a Closing all
        if (serialData == 'f') 
        {         
          myservo_thumb.write(0);
          myservo_index.write(0);
          myservo_middle.write(0);
          myservo_ring.write(0);
          myservo_pinkie.write(0);
          flag=true;
        }
        
     if(flag)
        {
          delay(1000);
          flag=false;
        }
   }
}
 
