void setup() {
  // Configurar pines 2 a 5 como salida
  for (int i = 2; i <= 5; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // Encender y apagar sucesivamente los pines del 2 al 5
  for (int i = 2; i <= 5; i++) {
    digitalWrite(i, HIGH); // Encender pin
    delay(500); // Esperar 1 segundo
    digitalWrite(i, LOW);  // Apagar pin
    delay(100); // Esperar medio segundo antes de encender el siguiente
  }

  // Encender y apagar sucesivamente los pines del 5 al 2
  for (int i = 5; i >= 2; i--) {
    digitalWrite(i, HIGH); // Encender pin
    delay(500); // Esperar 1 segundo
    digitalWrite(i, LOW);  // Apagar pin
    delay(100); // Esperar medio segundo antes de encender el siguiente
  }
}
