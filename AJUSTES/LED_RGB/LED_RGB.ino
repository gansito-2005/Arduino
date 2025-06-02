int LEDROJO = 5;
int LEDVERDE = 6;
int LEDAZUL = 7;


void setup() {

  pinMode(LEDROJO, OUTPUT);
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAZUL, OUTPUT);
  
  Serial.begin(9600);
}

void color(int rojo, int verde, int azul) {
  analogWrite(LEDROJO, rojo);  // Ajusta el valor del pin rojo
  analogWrite(LEDVERDE, verde); // Ajusta el valor del pin verde
  analogWrite(LEDAZUL, azul);  // Ajusta el valor del pin azul
}

void loop() {
  color(255, 255, 0);
  delay(1000);
  color(255, 0, 255);
  delay(1000);
  color(0, 255, 255);
  delay(1000);
  }