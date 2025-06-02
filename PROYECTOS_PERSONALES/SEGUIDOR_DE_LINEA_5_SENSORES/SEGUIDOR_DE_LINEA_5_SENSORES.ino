// Pines de los sensores
const int SENSOR_IZQUIERDO_EXTREMO = 12;
const int SENSOR_IZQUIERDO = 11;
const int SENSOR_CENTRAL = 10;
const int SENSOR_DERECHO = 9;
const int SENSOR_DERECHO_EXTREMO = 8;

// Constantes para estados de los sensores   LOW=LINEA BLANCA
const bool LINEA_DETECTADA = LOW;

// Pines para el motor A
int AIN1 = 7;
int AIN2 = 6;
int PWMA = 5;

// Pines para el motor B
int BIN1 = 2;
int BIN2 = 4;
int PWMB = 3;

// Pines de STBY
const int STBY = 13;

// Constantes PID
float kp = 180;
float ki = 0.00020;
float kd = 20;

float error = 0;
float errorPrevio = 0;
float integral = 0;
float derivada = 0;

int velocidadBase = 180;
int velocidadAjuste = 0;

void configurarMotores() {
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(STBY, OUTPUT);
  digitalWrite(STBY, HIGH);
}

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

void setup() {
  pinMode(SENSOR_IZQUIERDO_EXTREMO, INPUT);
  pinMode(SENSOR_IZQUIERDO, INPUT);
  pinMode(SENSOR_CENTRAL, INPUT);
  pinMode(SENSOR_DERECHO, INPUT);
  pinMode(SENSOR_DERECHO_EXTREMO, INPUT);
  configurarMotores();
  
  // Motores avanzando al inicio a velocidad 100 por 100ms
  controlMotor('A', 150, true);
  controlMotor('B', 150, true);
  delay(50);
  
  // Detener motores o continuar con el programa
}

void loop() {
  bool estadoIzquierdoExtremo = digitalRead(SENSOR_IZQUIERDO_EXTREMO);
  bool estadoIzquierdo = digitalRead(SENSOR_IZQUIERDO);
  bool estadoCentral = digitalRead(SENSOR_CENTRAL);
  bool estadoDerecho = digitalRead(SENSOR_DERECHO);
  bool estadoDerechoExtremo = digitalRead(SENSOR_DERECHO_EXTREMO);

  if (estadoCentral == LINEA_DETECTADA) {
    error = 0;
  } else if (estadoIzquierdo == LINEA_DETECTADA) {
    error = -1;
  } else if (estadoIzquierdoExtremo == LINEA_DETECTADA) {
    error = -2;
  } else if (estadoDerecho == LINEA_DETECTADA) {
    error = 1;
  } else if (estadoDerechoExtremo == LINEA_DETECTADA) {
    error = 2;
  }

  integral += error;
  derivada = error - errorPrevio;
  velocidadAjuste = kp * error + ki * integral + kd * derivada;
  errorPrevio = error;

  int velocidadIzquierda = constrain(velocidadBase - velocidadAjuste, 0, 255);
  int velocidadDerecha = constrain(velocidadBase + velocidadAjuste, 0, 255);

  controlMotor('A', velocidadIzquierda, true);
  controlMotor('B', velocidadDerecha, true);
}