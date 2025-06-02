#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

void setup() {
     servo1.attach(2);
     servo2.attach(9);
     servo3.attach(4);
     servo4.attach(5);
     servo5.attach(6);
     servo6.attach(7);
    
}

void loop() {
      servo2.write(180);
      delay(1200);
      servo2.write(0);
      delay(1200);
}