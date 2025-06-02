#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configura la dirección del módulo I2C 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines de sensores y actuadores   
const int sensorPin = A2;
const int LedR = 3;
const int pinDatosDQ = 2;
const int MotorPWM = 12;
const int Bomba = 11;
const int calentador = 4;
const int potenciometroPin2 = A0;

// Parámetros de Calibración
const float pH10Voltage = 3;
const float pH7Voltage = 2;
const float pH4Voltage = 1;

const float pH10Value = 10.0;
const float pH7Value = 7.0;
const float pH4Value = 4.0;

OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

float gradosCelsius = 0.0;
float voltage = 0.0;
float pHValue = 0.0;
unsigned long startTime;

void setup() {
    Serial.begin(9600);
    sensorDS18B20.begin();
    lcd.init();
    lcd.backlight();

    pinMode(sensorPin, INPUT);
    pinMode(LedR, OUTPUT);
    pinMode(MotorPWM, OUTPUT);
    pinMode(Bomba, OUTPUT);
    pinMode(calentador, OUTPUT);
    pinMode(potenciometroPin2, INPUT);

    digitalWrite(MotorPWM, HIGH); // Mantener el motor siempre encendido

    lcd.print("Hola soy tu");
    lcd.setCursor(0, 1);
    lcd.print("bioreactor");
    delay(2000);
    lcd.clear();
    startTime = millis();
}

void loop() {
    sensorDS18B20.requestTemperatures();
    float tempActual = sensorDS18B20.getTempCByIndex(0);

    int lecturaPot2 = analogRead(potenciometroPin2);
    gradosCelsius = map(lecturaPot2, 0, 1023, 20, 53);

    medirPH();
    controlTemperatura();

    unsigned long elapsedTime = millis() - startTime;
    int hours = (elapsedTime / 3600000) % 24;
    int minutes = (elapsedTime / 60000) % 60;



    lcd.clear();
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
    lcd.print("Tiempo:");
    lcd.print(hours);
    lcd.print("h ");
    lcd.print(minutes);
    lcd.print("m");
    delay(1000);
}

void controlTemperatura() {
    float tempActual = sensorDS18B20.getTempCByIndex(0);
    if (tempActual <= gradosCelsius - 0.5) {
        digitalWrite(LedR, LOW);
        digitalWrite(calentador, LOW);
        digitalWrite(Bomba, HIGH);
    } else if (tempActual >= gradosCelsius + 0.5) {
        digitalWrite(Bomba, LOW);
        digitalWrite(calentador, HIGH);
        digitalWrite(LedR, HIGH);
    }
}

void medirPH() {
    voltage = analogRead(sensorPin) * (5.0 / 1023.0);
    pHValue = calibratePH(voltage);
}

float calibratePH(float voltage) {
    float slope = (pH10Value - pH4Value) / (pH10Voltage - pH4Voltage);
    float intercept = pH7Value - slope * pH7Voltage;
    return slope * voltage + intercept;
}
