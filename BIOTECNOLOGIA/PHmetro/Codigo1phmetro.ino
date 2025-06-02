#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Configura la dirección del módulo I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C, columnas, filas
const int sensorPin = A0;

// Ajusta estos valores según los voltajes medidos en las soluciones buffer
const float pH10Voltage = 2.11; 
const float pH7Voltage = 2.61;  
const float pH4Voltage = 3.10; 

const float pH10Value = 10.0;
const float pH7Value = 7.0;
const float pH4Value = 4.0;  

// Pines para los dispositivos
int rele = 2;
int pinDatosDQ = 3;
int bombadeagua = 4;

// Pines para el control del motor
int enableA = 5;
int input1 = 6;
int input2 = 7;

// Pin del potenciómetro motor y temperatura
int potenciometroPin1 = A1;
int potenciometroPin2 = A2;

// Configuración para el sensor de temperatura DS18B20
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

// Variables globales
int velocidadMotor = 0;
int gradosCelsius = 0;
float voltage = 0;
float pHValue = 0;

void setup() {
    Serial.begin(9600);
    sensorDS18B20.begin();
    
    pinMode(bombadeagua, OUTPUT);
    pinMode(rele, OUTPUT);
    digitalWrite(rele, LOW);

    pinMode(enableA, OUTPUT);
    pinMode(input1, OUTPUT);
    pinMode(input2, OUTPUT);

    pinMode(potenciometroPin1, INPUT);
    pinMode(potenciometroPin2, INPUT);
  
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Muuuuuuy buenas");
    lcd.setCursor(0, 1);
    lcd.print("tardes");
    delay(2000);
    lcd.clear();
}

void loop() {
    int lecturaPot1 = analogRead(potenciometroPin1);
    velocidadMotor = map(lecturaPot1, 0, 1023, 0, 255);

    int lecturaPot2 = analogRead(potenciometroPin2);
    gradosCelsius = map(lecturaPot2, 0, 1023, 20, 53);

    sensorDS18B20.requestTemperatures();

    Serial.print("Temperatura deseada: ");
    Serial.print(gradosCelsius);
    Serial.print(" °C   ");
    Serial.print("Temperatura actual: ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.print(" °C   ");

    Serial.print("Velocidad del motor: ");
    Serial.print(map(velocidadMotor, 0, 255, 0, 100));
    Serial.print("%   ");

    Serial.print(" pH: ");
    Serial.println(pHValue);


    ph();
    controltemperatura();
    velocidadmotor();



    lcd.setCursor(0, 0);
    lcd.print("pH: ");
    lcd.print(pHValue,2);
    lcd.setCursor(0, 1);
    lcd.print("Velocidad: ");
    lcd.print(map(velocidadMotor, 0, 255, 0, 100), 10);
    delay(1000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("T deseada :");
    lcd.print(gradosCelsius,10);
    lcd.setCursor(0, 1);
    lcd.print("T actual :");
    lcd.print(sensorDS18B20.getTempCByIndex(0),10);
    delay(1000);
    lcd.clear();
}

void controltemperatura() {
    float temp = sensorDS18B20.getTempCByIndex(0);

    if (temp <= gradosCelsius) {
        digitalWrite(bombadeagua, HIGH);
        digitalWrite(rele, LOW);
    } else if (temp >= (gradosCelsius + 0.10)) {
        digitalWrite(bombadeagua, LOW);
        digitalWrite(rele, HIGH);
    }
}

void velocidadmotor() {
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
    analogWrite(enableA, velocidadMotor);
}

void ph() {
    voltage = analogRead(sensorPin) * (5.0 / 1023.0);
    pHValue = calibratePH(voltage);
}

float calibratePH(float voltage) {
    float slope = (pH10Value - pH7Value) / (pH10Voltage - pH7Voltage);
    float intercept = pH10Value - slope * pH10Voltage;
    return slope * voltage + intercept;
}
