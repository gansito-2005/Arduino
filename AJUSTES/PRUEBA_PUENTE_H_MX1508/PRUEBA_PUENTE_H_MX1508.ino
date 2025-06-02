// Pines de conexión
 int input1 = 10;  // Dirección 1
 int input2 = 11;  // Dirección 2

void setup() {
  // Configurar pines como salida
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
}

void loop() {
  // Girar en una dirección
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);

  delay(1000);


}
