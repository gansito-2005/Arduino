#include <Servo.h>

int LEDAZUL = 10;
int LEDROJO = 11;

Servo servo1;    // Movimiento en eje Y
Servo servo2;    // Movimiento de ojo izquierdo en eje X
Servo servo3;    // Movimiento de ojo derecho en eje de las X
Servo servo4;

int posI1 = 0;
int posF1 = 90;
int incremento1 = 3;

int posI2 = 25;
int posF2 = 90;
int incremento2 = 3;


void setup() {
  pinMode(LEDAZUL, OUTPUT);
  pinMode(LEDROJO, OUTPUT);

  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
}

void loop() {

  miColor(-200, 255);

  servo4.write(25);

  servo1.write(25);
  servo2.write(25);
  servo3.write(25);

 
 for (int i = posI1; i <= posF1; i += incremento1) {
      servo1.write(i);
      delay(100);
 }
    
    delay(50);

    servo1.write(20);   servo2.write(90);  servo3.write(90);
    delay(5000);

    servo1.write(25);   servo2.write(120);  servo3.write(120);
    delay(5000);
 
   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo1.write(i);  servo2.write(i + 40);  servo3.write(i + 40);
      delay(20);
  

    delay(100);

  }

  
    
 for (int i = posI1; i <= posF1; i += incremento1) {
      servo2.write(i);  servo3.write(i);
      delay(100);
    }   

    delay(50);
 
   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo2.write(i);  servo3.write(i);
      delay(70);
    }

    delay(100);


    servo1.write(0);   servo2.write(70);  servo3.write(70);
    delay(5000);

    servo1.write(60);   servo2.write(70);  servo3.write(70);
    delay(5000);


    for (int i = posI2; i <= posF2; i += incremento2) {
      servo4.write(i);
      delay(10);
    }


    miColor(250, -200);

    
    for (int i = posF2; i >= posI2; i -= incremento2) {
      servo4.write(i);
      delay(10);
    }
    
    servo1.write(0);   servo2.write(70);  servo3.write(70);
    delay(5000);

 for (int i = posI1; i <= posF1; i += incremento1) {
      servo1.write(i);
      delay(100);
 }
    
    delay(50);
 
     servo1.write(90);   servo2.write(120);  servo3.write(120);
    delay(1000);

   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo1.write(i);  servo2.write(i);  servo3.write(i);
      delay(50);
  
  }

  
    
 for (int i = posI1; i <= posF1; i += incremento1) {
      servo2.write(i);  servo3.write(i);
      delay(100);
    }   

    delay(50);

    servo2.write(140); servo3.write(140);
 
   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo1.write(30);  servo2.write(i);  servo3.write(i);
      delay(70);
    }

    delay(100);

    for (int i = posI2; i <= posF2; i += incremento2) {
      servo4.write(i);
      delay(10);
    }

    miColor(-200, 255);
    
    for (int i = posF2; i >= posI2; i -= incremento2) {
      servo4.write(i);
      delay(10);
    }

    miColor(-200, 255);
    delay(1000);
    miColor(250, -200);
    delay(100);
    miColor(-200, 255);
    delay(100);
    miColor(250, -200);
    delay(100);
    miColor(-200, 255);
    delay(1000);


    servo1.write(90);  servo2.write(80);   servo3.write(80);  
    delay(2000); 

    servo1.write(0);   servo2.write(70);  servo3.write(70);
    delay(5000);
    

    for (int i = posF1; i >= posI1; i -= incremento1) {
    servo1.write(i);  servo2.write(i + 40);  servo3.write(i + 40);
    delay(50);
    }

    servo1.write(0);   servo2.write(70);  servo3.write(70);
    delay(5000);
    

    for (int i = posF1; i >= posI1; i -= incremento1) {
    servo2.write(i);  servo3.write(i);
    delay(70);
    }



 for (int i = posI1; i <= posF1; i += incremento1) {
      servo1.write(i + 20);
      delay(100);
 }
    
    delay(50);

    servo1.write(40);   servo2.write(30);  servo3.write(30);
    delay(5000);

    servo1.write(75);   servo2.write(80);  servo3.write(80);
    delay(5000);
 
   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo1.write(i - 20);  servo2.write(i + 60);  servo3.write(i + 60);
      delay(20);
  

    delay(100);

  }

  
    
 for (int i = posI1; i <= posF1; i += incremento1) {
      servo2.write(i - 50);  servo3.write(i - 50);
      delay(100);
    }   

    delay(50);
 
   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo2.write(i + 30);  servo3.write(i + 30);
      delay(70);
    }

    delay(100);


    servo1.write(30);   servo2.write(70);  servo3.write(70);
    delay(5000);

    servo1.write(60);   servo2.write(70);  servo3.write(70);
    delay(5000);


    for (int i = posI2; i <= posF2; i += incremento2) {
      servo4.write(i);
      delay(10);
    }


    miColor(250, -200);

    
    for (int i = posF2; i >= posI2; i -= incremento2) {
      servo4.write(i);
      delay(10);
    }
    
    servo1.write(0);   servo2.write(70);  servo3.write(70);
    delay(5000);

 for (int i = posI1; i <= posF1; i += incremento1) {
      servo1.write(i - 60);
      delay(100);
 }
    
    delay(50);
 
     servo1.write(90);   servo2.write(120);  servo3.write(120);
    delay(1000);

   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo1.write(i);  servo2.write(i);  servo3.write(i);
      delay(50);
  
  }

  
    
 for (int i = posI1; i <= posF1; i += incremento1) {
      servo2.write(i);  servo3.write(i);
      delay(100);
    }   

    delay(50);

    servo2.write(140); servo3.write(140);
 
   for (int i = posF1; i >= posI1; i -= incremento1) {
      servo1.write(30);  servo2.write(i);  servo3.write(i);
      delay(70);
    }

    delay(100);

    for (int i = posI2; i <= posF2; i += incremento2) {
      servo4.write(i);
      delay(10);
    }

    miColor(-200, 255);
    
    for (int i = posF2; i >= posI2; i -= incremento2) {
      servo4.write(i);
      delay(10);
    }

    servo1.write(90);  servo2.write(160);   servo3.write(160);  
    delay(2000); 

    miColor(-200, 255);
    delay(1000);
    miColor(250, -200);
    delay(100);
    miColor(-200, 255);
    delay(100);
    miColor(250, -200);
    delay(100);
    miColor(-200, 255);
    delay(1000);


    servo1.write(90);  servo2.write(80);   servo3.write(80);  
    delay(2000); 

    servo1.write(0);   servo2.write(70);  servo3.write(70);
    delay(5000);
    

    for (int i = posF1; i >= posI1; i -= incremento1) {
    servo1.write(i+60);  servo2.write(i + 10);  servo3.write(i + 10);
    delay(50);
    }

    servo1.write(0);   servo2.write(70);  servo3.write(70);
    delay(5000);
    

    for (int i = posF1; i >= posI1; i -= incremento1) {
    servo2.write(i+100);  servo3.write(i+100);
    delay(70);
    }
    

}
  
void miColor(int rojo, int azul) {
  analogWrite(LEDAZUL, azul);
  analogWrite(LEDROJO, rojo);
}