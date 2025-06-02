#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configuración de Hardware
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines del LED RGB (Anodo Común)
const int LedR = 7;  // Rojo
const int LedG = 5;  // Verde
const int LedB = 6;  // Azul

// Pines de sensores y actuadores   
const int sensorPin = A0;      // Sensor de pH
const int pinDatosDQ = 4;      // Sensor de temperatura DS18B20
const int MotorPWM = 3;        // Control de velocidad del motor
const int Bomba = 2;           // Bomba de control de temperatura
const int potenciometroPin2 = A1; // Potenciómetro para temperatura deseada
const int potenciometroPin3 = A2; // Potenciómetro para control PWM

// Configuración de Sensores
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

// Variables Globales
float gradosCelsius = 0.0;
float pHValue = 0.0;
int valorPWM = 0;
int Porcentaje = 0;

void setup() {
    Serial.begin(9600);
    sensorDS18B20.begin();
    lcd.init();
    lcd.backlight();

    // Configuración de pines
    pinMode(sensorPin, INPUT);
    pinMode(LedR, OUTPUT);
    pinMode(LedG, OUTPUT);
    pinMode(LedB, OUTPUT);
    pinMode(MotorPWM, OUTPUT);
    pinMode(Bomba, OUTPUT);
    pinMode(potenciometroPin2, INPUT);
    pinMode(potenciometroPin3, INPUT);

    // Apagar el LED RGB (Anodo Común)
    digitalWrite(LedR, HIGH);
    digitalWrite(LedG, HIGH);
    digitalWrite(LedB, HIGH);

    lcd.print("Hola soy tu");
    lcd.setCursor(0, 1);
    lcd.print("bioreactor");
    delay(2000);
    lcd.clear();
}

void loop() {
    sensorDS18B20.requestTemperatures();
    float tempActual = sensorDS18B20.getTempCByIndex(0);

    int lecturaPot2 = analogRead(potenciometroPin2);
    gradosCelsius = map(lecturaPot2, 0, 1023, 20, 53);

    medirPH();
    controlTemperatura(tempActual);
    motorPWMControl();

    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(tempActual, 1);
    lcd.setCursor(0, 1);
    lcd.print("T dsa:");
    lcd.print(gradosCelsius, 1);
    delay(1000);
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Ph:");
    lcd.print(pHValue, 2);
    lcd.setCursor(0, 1);
    lcd.print("PWM:");
    lcd.print(Porcentaje);
    delay(1000);
}

void medirPH() {
    float voltage = analogRead(sensorPin) * (5.0 / 1023.0);
    pHValue = calibratePH(voltage);
}

float calibratePH(float voltage) {
    const float pH10Voltage = 2.11;
    const float pH7Voltage = 2.61;
    const float pH4Voltage = 3.10;

    const float pH10Value = 10.0;
    const float pH7Value = 7.0;
    const float pH4Value = 4.0;

    float slope = (pH10Value - pH4Value) / (pH10Voltage - pH4Voltage);
    float intercept = pH7Value - slope * pH7Voltage;
    return slope * voltage + intercept;
}

void controlTemperatura(float tempActual) {
    if (tempActual < gradosCelsius) {
        digitalWrite(LedB, LOW);  // Azul encendido
        digitalWrite(LedG, HIGH);
        digitalWrite(LedR, HIGH);
        digitalWrite(Bomba, HIGH);
    } else if (tempActual >= gradosCelsius && tempActual <= gradosCelsius + 2) {
        digitalWrite(LedB, HIGH);
        digitalWrite(LedG, LOW);  // Verde encendido
        digitalWrite(LedR, HIGH);
        digitalWrite(Bomba, LOW);
    } else {
        digitalWrite(LedB, HIGH);
        digitalWrite(LedG, HIGH);
        digitalWrite(LedR, LOW);  // Rojo encendido
        digitalWrite(Bomba, LOW);
    }
}

void motorPWMControl() {
    int valorPOT = analogRead(potenciometroPin3);
    valorPWM = map(valorPOT, 0, 1023, 0, 255);
    Porcentaje = map(valorPWM, 0, 255, 0, 100);
    analogWrite(MotorPWM, valorPWM);

    Serial.print("Valor Potenciometro: ");
    Serial.print(valorPOT);
    Serial.print(" - Valor PWM: ");
    Serial.println(Porcentaje);
}
