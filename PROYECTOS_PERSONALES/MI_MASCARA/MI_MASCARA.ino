#include <Servo.h>

int LEDROJO = 11;
int LEDVERDE = 10;
int LEDAZUL = 12;

int estado = 0;
int potenciometro = 0;
int angulo = 0;

int posI1 = 0;
int posF1 = 90;
int incremento1 = 3;

int posI2 = 25;
int posF2 = 90;
int incremento2 = 3;

Servo servo1;    // Movimiento en eje Y
Servo servo2;    // Movimiento de ojo izquierdo en eje X
Servo servo3;    // Movimiento de ojo derecho en eje de las X
Servo servo4;    // Movimiento de parpado
Servo servo5;    //Movimiento de boca



void setup() {
  Serial.begin(9600);
  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);

  servo1.attach(3);  // Movimiento en eje Y
  servo2.attach(5);  // Movimiento de ojo izquierdo en eje X
  servo3.attach(6);  // Movimiento de ojo derecho en eje de las X
  servo4.attach(9);  // Movimiento de parpado
  servo5.attach(13);  //Movimiento de boca
}


void color(int rojo, int verde, int azul) {
  analogWrite(LEDROJO, rojo);  // Ajusta el valor del pin rojo
  analogWrite(LEDVERDE, verde); // Ajusta el valor del pin verde
  analogWrite(LEDAZUL, azul);  // Ajusta el valor del pin azul
}


void loop() {

  if(Serial.available()>0){
  estado = Serial.read();
  }

  else if (estado == 'D'){
     potenciometro = 1;
  }

  else if (estado == '1'){
     potenciometro = 2;
  }

  else if (estado == '2'){
     potenciometro = 3;
  }

  else if (estado == '3'){
     potenciometro = 4;
  }

  else if (estado == '4'){
     potenciometro = 5;
  }

  else if (estado == '5'){
     potenciometro = 6;
  }

  else if (estado == '6'){
     potenciometro = 7;
  }

  else if (estado == '7'){
     potenciometro = 8;
  }

  else if (estado == '8'){
     potenciometro = 9;
  }

  else if (estado == '9'){
     potenciometro = 10;
  }

  else if (estado == 'E'){
     potenciometro = 11;
  }

    else if (estado == 'A'){
     potenciometro = 12;
  }

    else if (estado == 'C'){
     potenciometro = 13;
  }

    else if (estado == 'B'){
     potenciometro = 14;
  }

  


    switch (potenciometro){

      case 1:
      color(127, 127, 255);
      servo1.write(55);
      servo2.write(85);
      servo3.write(85);
      servo4.write(33); 
      break;
      

      case 2:
      
      color(127, 255, 0);
      
      break;
 

      case 3:
      
      color(255, 0, 0);

      
      break;


      case 4:
      
      color(0, 255, 0);
      
      break;


      case 5:

      color(100, 255, 0);

      break;


      case 6:
      
      color(0, 0, 0);
      
      break;


      case 7:
      if (angulo <= 70) {  
      angulo += 1;
      servo1.write(angulo); 
      delay(15);             
      }
      break;


      case 8:
      if (angulo >= 27) {  
      angulo -= 1;
      servo1.write(angulo); 
      delay(15);
      }
      break;


      case 9:
      if (angulo <= 130) {  
      angulo += 1;
      servo2.write(angulo);
      servo3.write(angulo); 
      delay(15);             
      }
      break;


      case 10:
      if (angulo >= 40) {  
      angulo -= 1;
      servo2.write(angulo);
      servo3.write(angulo); 
      delay(15);             
      }           
      break;


      case 11:
      servo1.write(55);
      servo2.write(85);
      servo3.write(85);
      servo4.write(33); 
      break;


      case 12:
      for (int i = posI2; i <= posF2; i += incremento2) {
      servo5.write(i);
      delay(10);
      }
      delay(10);
      for (int i = posF2; i >= posI2; i -= incremento2) {
      servo5.write(i);
      delay(10);
      }
      break;

      case 13:
      for (int i = posI2; i <= posF2; i += incremento2) {
      servo4.write(i);
      delay(10);
      }
      delay(10);
      for (int i = posF2; i >= posI2; i -= incremento2) {
      servo4.write(i);
      delay(10);
      }
      break;


      case 14:        
  color(0, 255, 0);

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
     }

  delay(100);

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

  color(255, 0, 0);
 
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

  color(0, 255, 255);
    
   for (int i = posF2; i >= posI2; i -= incremento2) {
   servo4.write(i);
   delay(10);
   }


  color(255, 0, 255);
  delay(1000);
  color(0, 255, 255);
  delay(100);
  color(255, 0, 255);
  delay(100);
  color(0, 255, 255);
  delay(100);
  color(255, 0, 255);
  delay(100);
  color(0, 255, 255);
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
     }

    break;
    

  }
}

