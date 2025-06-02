#include <Servo.h>
Servo servoMotor;
int stop = 13;
int incremento1 = 12;
int incremento2 = 8;
int incremento3 = 7;
int incremento4 = 4;

int potenciometro = 0;


void setup() {
   servoMotor.attach(3);
   pinMode(stop, INPUT_PULLUP);
   pinMode(incremento1, INPUT_PULLUP);
   pinMode(incremento2, INPUT_PULLUP);
   pinMode(incremento3, INPUT_PULLUP);
   pinMode(incremento4, INPUT_PULLUP);
   Serial.begin(9600);

}

void loop() {

    if(digitalRead(stop) == LOW){
     potenciometro = 1;
  }

  else if(digitalRead(incremento1) == LOW){
     potenciometro = 2;
  }

  else if(digitalRead(incremento2) == LOW){
     potenciometro = 3;
  }

  else if(digitalRead(incremento3) == LOW){
     potenciometro = 4;
  }

  else if(digitalRead(incremento4) == LOW){
     potenciometro = 5;
  }
  


  switch (potenciometro){
      
      case 1:
      servoMotor.write(90);
      break;

      case 2:
      servoMotor.write(96);
      break;

      case 3:
      servoMotor.write(110);
      break;

      case 4:
      servoMotor.write(124);
      break;

      case 5:
      servoMotor.write(138);
      break;

  }

}
