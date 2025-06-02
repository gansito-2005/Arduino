// Pines de los modos
const int MODO_SUMO = 12;
const int MODO_LINEA = 13;

// Pines de los sensores
const int SENSOR_IZQUIERDO = 4;
const int SENSOR_CENTRAL = 3;
const int SENSOR_DERECHO = 2;

// Pines del sensor ultrasónico
const int TRIG = A1;
const int ECHO = A0;
const long DISTANCIA_MAXIMA = 30; // en centímetros

// Pines de los motores
const int MOTOR_IZQ_ADELANTE = 11;
const int MOTOR_IZQ_ATRAS = 10;
const int MOTOR_DER_ADELANTE = 8;
const int MOTOR_DER_ATRAS = 9;

// Constantes para estados de los sensores
const bool LINEA_DETECTADA = HIGH;
const bool SIN_LINEA = LOW;

void setup() {
  pinMode(MODO_SUMO, INPUT);
  pinMode(MODO_LINEA, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Configuración de los pines de los sensores como entrada
  pinMode(SENSOR_IZQUIERDO, INPUT);
  pinMode(SENSOR_CENTRAL, INPUT);
  pinMode(SENSOR_DERECHO, INPUT);

  // Configuración de los pines de los motores como salida
  pinMode(MOTOR_IZQ_ADELANTE, OUTPUT);
  pinMode(MOTOR_IZQ_ATRAS, OUTPUT);
  pinMode(MOTOR_DER_ADELANTE, OUTPUT);
  pinMode(MOTOR_DER_ATRAS, OUTPUT);

  detener();
}

// Función para medir la distancia con un sensor ultrasónico
long medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duracion = pulseIn(echoPin, HIGH, 30000); // Timeout de 30ms
  if (duracion == 0) return DISTANCIA_MAXIMA + 1; // Fuera de rango

  long distancia = duracion * 0.034 / 2; // Convertir a cm
  return distancia;
}

void loop() {
  bool modoSumo = digitalRead(MODO_SUMO);
  bool modoLinea = digitalRead(MODO_LINEA);

  // Leer los estados de los sensores
  bool estadoIzquierdo = digitalRead(SENSOR_IZQUIERDO);
  bool estadoCentral = digitalRead(SENSOR_CENTRAL);
  bool estadoDerecho = digitalRead(SENSOR_DERECHO);

  long distanciaDelantera = medirDistancia(TRIG, ECHO);


  if (modoSumo == HIGH) {
     if (estadoIzquierdo == LINEA_DETECTADA || estadoDerecho == LINEA_DETECTADA  ) {
     retroceder(); // Evitar salirse del ring
     }
     else if (distanciaDelantera <= DISTANCIA_MAXIMA) {
     configurarMotores(HIGH, LOW, HIGH, LOW);     }
     else {
  configurarMotores(HIGH, LOW, LOW, LOW); // Detiene motor derecho
    delay(5);
  configurarMotores(LOW, LOW, LOW, LOW); // Detiene motor derecho
    delay(25);

     }

  }  else if (modoLinea == HIGH) {
  // Lógica de control del seguidor de línea
  if (estadoCentral == LINEA_DETECTADA) {
    avanzar(); // La línea está en el centro
  } else if (estadoIzquierdo == LINEA_DETECTADA) {
    girarIzquierda(); // La línea está hacia la izquierda
  } else if (estadoDerecho == LINEA_DETECTADA) {
    girarDerecha(); // La línea está hacia la derecha
  } else {
    busacrlinea(); // Ningún sensor detecta la línea
  }
  
  } else {
      detener();
  }
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
  delay(15);
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(15);
}

// Función para retroceder recto
void retroceder() {
  configurarMotores(LOW, HIGH, LOW, HIGH);
  delay(15);
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(15);
}

// Función para girar a la izquierda
void girarIzquierda() {
  configurarMotores(LOW, LOW, HIGH, LOW); // Detiene motor izquierdo
  delay(15);
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(15);
}

// Función para girar a la derecha
void girarDerecha() {
  configurarMotores(HIGH, LOW, LOW, LOW); // Detiene motor derecho
  delay(15);
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(15);
}

// Función para busacrlinea el robot
void busacrlinea() {
  configurarMotores(HIGH, LOW, HIGH, LOW);
  delay(15);
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(15);
}

// Función para detener el robot
void detener() {
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(15);
  configurarMotores(LOW, LOW, LOW, LOW);
  delay(15);
}
