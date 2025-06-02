int sensorPin = A0; // Pin donde está conectado el sensor (To)
int analogValue;
float voltage;
float phValue;
float calibrationOffset = 1129; // Ajustar según sea necesario

void setup() {
  Serial.begin(9600); // Iniciar la comunicación serie a 9600 baudios
}

void loop() {
  // Leer el valor analógico del pin A0
  analogValue = analogRead(sensorPin);
  
  // Convertir el valor analógico a voltaje (de 0V a 5V)
  voltage = analogValue * (5.0 / 1023.0);
  
  // Convertir el voltaje a pH
  phValue = -1.5 * analogValue + calibrationOffset; // Ajusta la fórmula y offset según sea necesario

  // Mostrar los resultados en el monitor serie
  Serial.print("Valor Analógico: ");
  Serial.print(analogValue);
  Serial.print("   |   Voltaje: ");
  Serial.print(voltage);
  Serial.print(" V   |   pH: ");
  Serial.println(phValue);

  // Esperar 1 segundo antes de la siguiente lectura
  delay(1000);
}
