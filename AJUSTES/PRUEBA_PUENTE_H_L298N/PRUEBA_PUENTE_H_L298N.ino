// Pines de conexión
const int enableA = 11; // PWM para velocidad
const int input1 = 9;  // Dirección 1
const int input2 = 10;  // Dirección 2

void setup() {
  // Configurar pines como salida
  pinMode(enableA, OUTPUT);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
}

void loop() {
  // Girar en una dirección
  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  analogWrite(enableA, 255); 

  delay(10000);

  digitalWrite(input1, HIGH);
  digitalWrite(input2, LOW);
  analogWrite(enableA, 255); 

  delay(10000);

  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  analogWrite(enableA, 255); 
  
  delay(10000);

  digitalWrite(input1, LOW);
  digitalWrite(input2, HIGH);
  analogWrite(enableA, 255); 

  delay(10000);

}
