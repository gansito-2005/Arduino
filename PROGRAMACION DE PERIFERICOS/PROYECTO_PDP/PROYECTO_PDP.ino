// Pines de los modos
const int MODO_SUMO = 12;
const int MODO_LINEA = 13;

// Pines de los sensores
const int SENSOR_IZQUIERDO = 2;
const int SENSOR_CENTRAL = 3;
const int SENSOR_DERECHO = 4;

// Constantes para estados de los sensores
const bool LINEA_DETECTADA = LOW;
const bool SIN_LINEA = HIGH;

// Pines del sensor ultrasónico
const int TRIG = A0;
const int ECHO = A1;
const long DISTANCIA_MAXIMA = 30; // en centímetros

// Pines para el motor A
const int AIN1 = 6; // Dirección 1 del motor A
const int AIN2 = 5; // Dirección 2 del motor A
const int PWMA = 9; // Velocidad del motor A

// Pines para el motor B
const int BIN1 = 8; // Dirección 1 del motor B
const int BIN2 = 7; // Dirección 2 del motor B
const int PWMB = 10; // Velocidad del motor B

// Pines de STBY (Standby)
const int STBY = 11; // Habilita el puente H

// Constantes para direcciones del motor
const bool FORWARD = true;
const bool BACKWARD = false;

// Constantes para movimiento
const int VELOCIDAD_MAXIMA = 255;
const int VELOCIDAD_BUSQUEDA = 70;
const int TIEMPO_RETROCESO = 150; // en ms

// Variables PID
float kp = 72; // Constante proporcional
float ki = 0.0098; // Constante integral
float kd = 0.0049; // Constante derivativa

float error = 0;
float errorPrevio = 0;
float integral = 0;
float derivada = 0;

int velocidadBase = 145; // Velocidad base de los motores
int velocidadAjuste = 0;

// Funciones para configurar los motores
void configurarMotores() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH); // Activar el TB6612FNG

  detener(); // Inicializar con motores apagados
}

// Configuración inicial
void setup() {
  pinMode(MODO_SUMO, INPUT);
  pinMode(MODO_LINEA, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Configuración de los pines de los sensores como entrada
  pinMode(SENSOR_IZQUIERDO, INPUT);
  pinMode(SENSOR_CENTRAL, INPUT);
  pinMode(SENSOR_DERECHO, INPUT);

  // Configurar motores
  configurarMotores();
}

// Función para controlar un motor
void controlMotor(char motor, int velocidad, bool direccion) {
  if (motor == 'A') {
    digitalWrite(AIN1, direccion);
    digitalWrite(AIN2, !direccion);
    analogWrite(PWMA, velocidad);
  } else if (motor == 'B') {
    digitalWrite(BIN1, direccion);
    digitalWrite(BIN2, !direccion);
    analogWrite(PWMB, velocidad);
  }
}

// Función para detener un motor
void stopMotor(char motor) {
  if (motor == 'A') {
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    analogWrite(PWMA, 0);
  } else if (motor == 'B') {
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    analogWrite(PWMB, 0);
  }
}

// Función para detener el robot
void detener() {
  stopMotor('A');
  stopMotor('B');
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

// Función para retroceder
void retroceder(int velocidad = VELOCIDAD_MAXIMA, int tiempo = TIEMPO_RETROCESO) {
  controlMotor('A', velocidad, BACKWARD);
  controlMotor('B', velocidad, BACKWARD);
  delay(tiempo);
}

// Función para avanzar recto
void avanzar() {
  controlMotor('A', VELOCIDAD_MAXIMA, FORWARD);
  controlMotor('B', VELOCIDAD_MAXIMA, FORWARD);
}

// Función para buscar adversario
void buscarAdversario() {
  controlMotor('A', VELOCIDAD_BUSQUEDA, FORWARD);
  controlMotor('B', VELOCIDAD_BUSQUEDA, BACKWARD);
}

// Bucle principal
void loop() {
  bool modoSumo = digitalRead(MODO_SUMO);
  bool modoLinea = digitalRead(MODO_LINEA);

  bool estadoIzquierdo = digitalRead(SENSOR_IZQUIERDO);
  bool estadoCentral = digitalRead(SENSOR_CENTRAL);
  bool estadoDerecho = digitalRead(SENSOR_DERECHO);

  long distanciaDelantera = medirDistancia(TRIG, ECHO);

  if (modoSumo == HIGH) {
    if (estadoIzquierdo == LINEA_DETECTADA || estadoDerecho == LINEA_DETECTADA) {
      retroceder();
    } else if (distanciaDelantera <= DISTANCIA_MAXIMA) {
      avanzar();
    } else {
      buscarAdversario();
    }
    
  } else if (modoLinea == HIGH) {
    if (estadoCentral == LINEA_DETECTADA) {
      error = 0; // Línea centrada
    } else if (estadoIzquierdo == LINEA_DETECTADA) {
      error = -1; // Línea a la izquierda
    } else if (estadoDerecho == LINEA_DETECTADA) {
      error = 1; // Línea a la derecha
    } else {
      buscarAdversario();
    }

    // Calcular PID
    integral += error;
    derivada = error - errorPrevio;
    velocidadAjuste = kp * error + ki * integral + kd * derivada;
    errorPrevio = error;

    // Ajustar velocidades de los motores
    int velocidadIzquierda = constrain(velocidadBase - velocidadAjuste, 0, VELOCIDAD_MAXIMA);
    int velocidadDerecha = constrain(velocidadBase + velocidadAjuste, 0, VELOCIDAD_MAXIMA);

    controlMotor('A', velocidadIzquierda, FORWARD);
    controlMotor('B', velocidadDerecha, FORWARD);
  } else {
    detener();
  }
}
