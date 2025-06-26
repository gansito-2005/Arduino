#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int sensorPhPin = A0;
float pHValue = 0.0;

// LCD I2C: Dirección 0x27, 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Valores de calibración
const float pH4Voltage = 3.10;
const float pH7Voltage = 2.61;
const float pH10Voltage = 2.11;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(sensorPhPin, INPUT);

  lcd.print("Leyendo pH...");
  delay(2000);
  lcd.clear();
}

void loop() {
  medirPH();
  mostrarPH();
  delay(500);
}

void medirPH() {
  float voltage = analogRead(sensorPhPin) * (5.0 / 1023.0);
  pHValue = calibrarPHtramos(voltage);

  // Limitar entre 0 y 14 por seguridad
  if (pHValue < 0.0) pHValue = 0.0;
  if (pHValue > 14.0) pHValue = 14.0;
}

float calibrarPHtramos(float voltage) {
  if (voltage >= pH7Voltage) {
    // Entre pH 4 y pH 7
    float pendiente = (7.0 - 4.0) / (pH7Voltage - pH4Voltage);
    return 7.0 - (voltage - pH7Voltage) * pendiente;
  } else {
    // Entre pH 7 y pH 10
    float pendiente = (10.0 - 7.0) / (pH10Voltage - pH7Voltage);
    return 7.0 - (voltage - pH7Voltage) * pendiente;
  }
}

void mostrarPH() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("pH: ");
  lcd.print(pHValue, 2);
}
s