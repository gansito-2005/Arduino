// Pines asignados al puente H TB6612FNG
int STBY = 13;

int AN1 = 4;
int AN2 = 2;
int PWMA = 3;

int AN3 = 6;
int AN4 = 7;
int PWMB = 5;

void setup() {
  // Configurar los pines como salida
  pinMode(STBY, OUTPUT);
  pinMode(AN1, OUTPUT);
  pinMode(AN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(AN3, OUTPUT);
  pinMode(AN4, OUTPUT);
  pinMode(PWMB, OUTPUT);

  // Quitar standby
  digitalWrite(STBY, HIGH);
}

// Función para mover el motor hacia adelante
void moverAdelante(int velocidad) {
  digitalWrite(AN1, HIGH);
  digitalWrite(AN2, LOW);
  analogWrite(PWMA, velocidad);

  digitalWrite(AN3, HIGH);
  digitalWrite(AN4, LOW);
  analogWrite(PWMB, velocidad);
}

// Función para mover el motor hacia atrás
void moverAtras(int velocidad) {
  digitalWrite(AN1, LOW);
  digitalWrite(AN2, HIGH);
  analogWrite(PWMA, velocidad);
}

// Función para detener el motor
void detenerMotor() {
  digitalWrite(AN1, LOW);
  digitalWrite(AN2, LOW);
  analogWrite(PWMA, 0);
}

void loop() {
  // Mover hacia adelante lento
  moverAdelante(255); // Velocidad baja

}
