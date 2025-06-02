#include <Servo.h> 

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int LEDROJO = 9;
int LEDVERDE = 10;
int LEDAZUL = 11;

int pirPin = 12;  // PIR conectado al pin 12
bool pirState = false;  // Estado del PIR

int estado = 0;
int potenciometro = 0;
int angulo = 0;

void setup() {
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);

  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);
  pinMode(pirPin, INPUT);  // Configura el pin del PIR como entrada
  
  Serial.begin(9600);
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
     potenciometro = 1;     //stop
  }

  else if (estado == '1'){
     potenciometro = 2;     //color 1
  }

  else if (estado == '2'){
     potenciometro = 3;     //color 2
  }

  else if (estado == '3'){
     potenciometro = 4;     //color 3
  }

  else if (estado == '4'){
     potenciometro = 5;     //color 4
  }

  else if (estado == '5'){
     potenciometro = 6;     //color 5
  }

  else if (estado == '6'){
     potenciometro = 7;     //arriba 
  }

  else if (estado == '7'){
     potenciometro = 8;     //abajo 
  }

  else if (estado == '8'){
     potenciometro = 9;     //izquierda 
  }

  else if (estado == '9'){
     potenciometro = 10;     //derecha 
  }

  else if (estado == 'E'){
     potenciometro = 11;     //centro 
  }

    else if (estado == 'A'){
     potenciometro = 12;     //boca 
  }

    else if (estado == 'C'){
     potenciometro = 13;     //parpadeo 
  }

    else if (estado == 'B'){
     potenciometro = 14;     //auto 
  }

  


    switch (potenciometro){

      case 1:                //stop
      color(0, 0, 0);
      servo1.write(90);
      servo2.write(90);
      servo3.write(76);
      servo4.write(90);
      servo5.write(90);
      servo6.write(90);
      break;

      case 2:                //color 1
      color(255, 0, 0);
      break;
 
      case 3:                //color 2
      color(0, 255, 0);
      break;

      case 4:                //color 3
      color(0, 255, 255);
      break;

      case 5:                //color 4
      color(0, 110, 255);
      break;

      case 6:                //color 5
      color(0, 0, 0);
      break;

      case 7:                //arriba
      servo4.write(80);    servo3.write(100);
      break;

      case 8:                //abajo
      servo4.write(100);     servo3.write(60);
      break;

      case 9:                //izquierda
      if (angulo >= 85) {  
      angulo -= 1;
      servo2.write(angulo);
      servo5.write(angulo); 
      delay(15);             
      }       
      break;

      case 10:                //derecha
      if (angulo <= 95) {  
      angulo += 1;
      servo2.write(angulo);
      servo5.write(angulo); 
      delay(15);             
      }    
      break;

      case 11:                //centro
      servo1.write(90);
      servo2.write(90);
      servo3.write(76);
      servo4.write(90);
      servo5.write(90);
      servo6.write(90);
      break;

      case 12:                //boca
    servo1.write(0);
    delay(1000);
    servo1.write(90);
      break;

      case 13:                //parpadeo
      break;

      case 14:                //auto
  pirState = digitalRead(pirPin);  // Lee el estado del PIR

  if (pirState) {  // Si el PIR detecta movimiento
    Serial.println("Movimiento detectado");
    color(0, 255, 0);
    servo1.write(90);
    servo2.write(90);
    servo3.write(76);
    servo4.write(90);
    servo5.write(90);
    servo6.write(90);
    delay(1000);

    servo5.write(80);     servo2.write(80);
    delay(1000);
    servo5.write(100);    servo2.write(100);
    delay(1000);
    servo5.write(90);     servo2.write(90);
    delay(1000);

    servo4.write(100);     servo3.write(60);
    delay(1000);
    servo4.write(80);    servo3.write(100);
    delay(1000);
    servo4.write(90);     servo3.write(76);
    delay(1000);

    color(0, 255, 255);
    delay(100);
    color(0, 255, 0);
    delay(100);
    color(0, 255, 255);
    delay(100);
    color(0, 255, 0);

    servo1.write(0);
    delay(1000);
    servo1.write(90);
    delay(1000);
  } 
  
  else {
    Serial.println("Sin movimiento");
    color(255, 0, 0);  // Cambia el color a rojo o cualquier otro para indicar que está inactivo
    servo1.write(90);
    servo2.write(90);
    servo3.write(76);
    servo4.write(90);
    servo5.write(90);
    servo6.write(90);
  }
  break;

}
}
