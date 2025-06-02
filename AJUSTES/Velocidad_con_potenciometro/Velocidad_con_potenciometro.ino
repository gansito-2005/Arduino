// Pines asignados al puente H TB6612FNG
int STBY = 10;

int AN1 = 12;
int AN2 = 13;
int PWMA = 11;

int AN3 = 7;
int AN4 = 8;
int PWMB = 9;

float velocidad = 0.0;

// Pin del potenciómetro temperatura
int potenciometroPin2 = A2; // Pin analógico donde se conecta el potenciómetro


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

      pinMode(potenciometroPin2, INPUT); // Configurar el pin del potenciómetro como entrada

}

// Función para mover el motor hacia adelante
void moverAdelante(int velocidad) {
  digitalWrite(AN1, HIGH);
  digitalWrite(AN2, LOW);
  analogWrite(PWMA, velocidad);
}

void loop() {
  int lecturaPot2 = analogRead(potenciometroPin2);
    velocidad = map(lecturaPot2, 0, 1023, 20, 53);

  // Mover hacia adelante lento
  moverAdelante(velocidad); // Velocidad baja

}