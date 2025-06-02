const int trigPin = A0; // Pin analógico usado como digital
const int echoPin = A1;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Enviar pulso de disparo
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Leer pulso de eco
  long duration = pulseIn(echoPin, HIGH);

  // Calcular distancia en cm
  long distance = duration * 0.034 / 2;

  // Mostrar la distancia
  Serial.print("Distancia: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}