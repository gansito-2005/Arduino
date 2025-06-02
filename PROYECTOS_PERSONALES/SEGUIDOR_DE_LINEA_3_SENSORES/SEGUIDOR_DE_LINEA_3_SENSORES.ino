// Pines de los sensores
const int SENSOR_IZQUIERDO = 2;
const int SENSOR_CENTRAL = 3;
const int SENSOR_DERECHO = 4;

// Constante para estado de la línea detectada
const bool LINEA_DETECTADA = LOW;

// Pines para el motor izquierdo
const int AIN1 = 10;  // Avance motor izquierdo
const int PWMA = 9;  // Velocidad motor izquierdo

// Pines para el motor derecho
const int BIN1 = 12;   // Avance motor derecho
const int PWMB = 11;  // Velocidad motor derecho

// Constantes PID
float kp = 40;
float ki = 0.;
float kd = 30;

float error = 0;
float errorPrevio = 0;
float integral = 0;
float derivada = 0;

int velocidadBase = 85;
int velocidadAjuste = 0;

void configurarMotores() {
    pinMode(AIN1, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(PWMB, OUTPUT);
  
    // Asegurar que los motores siempre giren hacia adelante
    digitalWrite(AIN1, HIGH);
    digitalWrite(BIN1, HIGH);
}

void controlMotor(char motor, int velocidad) {
    if (motor == 'A') {
        analogWrite(PWMA, velocidad);
    } else if (motor == 'B') {
        analogWrite(PWMB, velocidad);
    }
}

void setup() {
    pinMode(SENSOR_IZQUIERDO, INPUT);
    pinMode(SENSOR_CENTRAL, INPUT);
    pinMode(SENSOR_DERECHO, INPUT);
    configurarMotores();
}

void loop() {
    bool estadoIzquierdo = (digitalRead(SENSOR_IZQUIERDO) == LINEA_DETECTADA);
    bool estadoCentral = (digitalRead(SENSOR_CENTRAL) == LINEA_DETECTADA);
    bool estadoDerecho = (digitalRead(SENSOR_DERECHO) == LINEA_DETECTADA);

    // Determinar el error según la posición de la línea
    if (estadoCentral) {
        error = 0;
    } else if (estadoIzquierdo) {
        error = -1;
    } else if (estadoDerecho) {
        error = 1;
    }

    // Calcular PID
    integral += error;
    derivada = error - errorPrevio;
    velocidadAjuste = kp * error + ki * integral + kd * derivada;
    errorPrevio = error;

    // Ajustar velocidades de los motores
    int velocidadIzquierda = constrain(velocidadBase - velocidadAjuste, 0, 255);
    int velocidadDerecha = constrain(velocidadBase + velocidadAjuste, 0, 255);

    controlMotor('A', velocidadIzquierda);
    controlMotor('B', velocidadDerecha);
}
