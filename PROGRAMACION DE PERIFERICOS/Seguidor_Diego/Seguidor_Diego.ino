int pin2 = 5;
int pin1 = 4;

// Pines de los sensores
const int SENSOR_IZQUIERDO = 3;
const int SENSOR_DERECHO = 2;

// Pin analógico usado como digital
const int DELANTERO_TRIG = A0;
const int DELANTERO_ECHO = A1;

// Pines de los motores
const int MOTOR_IZQ_ADELANTE = 9;
const int MOTOR_IZQ_ATRAS = 10;
const int MOTOR_DER_ADELANTE = 7;
const int MOTOR_DER_ATRAS = 6;

// Constantes para estados de TODOS los sensores

const bool LINEA_DETECTADA = HIGH ;
const bool SIN_LINEA =  LOW;

const long DISTANCIA_MAXIMA = 15; // en centímetros

int value1 = 0;
int value2 = 0;

void setup() {
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);

  pinMode(DELANTERO_TRIG, OUTPUT);
  pinMode(DELANTERO_ECHO, INPUT);

  // Configuración de los pines de los sensores como entrada
  pinMode(SENSOR_IZQUIERDO, INPUT);
  pinMode(SENSOR_DERECHO, INPUT);
  
  // Configuración de los pines de los motores como salida
  pinMode(MOTOR_IZQ_ADELANTE, OUTPUT);
  pinMode(MOTOR_IZQ_ATRAS, OUTPUT);
  pinMode(MOTOR_DER_ADELANTE, OUTPUT);
  pinMode(MOTOR_DER_ATRAS, OUTPUT);
  

}

void loop() {
  value1 = digitalRead(pin1);
  value2 = digitalRead(pin2);

  // Leer los estados de los sensores
  bool estadoIzquierdo = digitalRead(SENSOR_IZQUIERDO);
  bool estadoDerecho = digitalRead(SENSOR_DERECHO);
  
  long distanciaDelantera = medirDistancia(DELANTERO_TRIG, DELANTERO_ECHO);


  if(value1 == HIGH){
      // Lógica de control del seguidor de línea
      if (estadoIzquierdo == LINEA_DETECTADA) { 
      girarIzquierda(); // La línea está hacia la izquierda
      } 
      else if (estadoDerecho == LINEA_DETECTADA) { 
      girarDerecha(); // La línea está hacia la derecha
      }   
      else { 
      avanzar(); // La línea está en el centro
      }
  }

  else if(value2 == HIGH){
     if (estadoIzquierdo == LINEA_DETECTADA || estadoDerecho == LINEA_DETECTADA  ) {
     retroceder(); // Evitar salirse del ring
     }
     else if (distanciaDelantera <= DISTANCIA_MAXIMA) {
     configurarMotores(HIGH, LOW, HIGH, LOW);     }
     else {
     buscarAdversario(); // Si no se detecta nada, buscar al adversario
     }
  }

  else{
  configurarMotores(LOW, LOW, LOW, LOW);
  }
}

// Función para medir la distancia con un sensor ultrasónico
long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH);
  long distancia = duracion * 0.034 / 2; // Convertir a cm
  return distancia;
}

// Función genérica para controlar los motores
void configurarMotores(bool izqAdelante, bool izqAtras, bool derAdelante, bool derAtras) {
  digitalWrite(MOTOR_IZQ_ADELANTE, izqAdelante);
  digitalWrite(MOTOR_IZQ_ATRAS, izqAtras);
  digitalWrite(MOTOR_DER_ADELANTE, derAdelante);
  digitalWrite(MOTOR_DER_ATRAS, derAtras);
}

// Función para avanzar recto
void avanzar() {
  configurarMotores(HIGH, LOW, HIGH, LOW);
}

// Función para girar a la izquierda
void girarIzquierda() {
  configurarMotores(LOW, LOW, HIGH, LOW);

}

// Función para girar a la derecha
void girarDerecha() {
  configurarMotores(HIGH, LOW, LOW, LOW);

}

// Función para retroceder
void retroceder() {
  configurarMotores(LOW, HIGH, LOW, HIGH);
  delay(150);
}

// Funcion para buscaroponente
void buscarAdversario() {
  configurarMotores(LOW, LOW, HIGH, LOW);
  delay(20);
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(20);
}
