#define TRIG A0  // Pin TRIG del sensor ultrasónico
#define ECHO A1  // Pin ECHO del sensor ultrasónico
#define IR_SENSOR 7  // Pin del sensor infrarrojo

// Pines de los motores
#define MOTOR_IZQ_A 12
#define MOTOR_IZQ_B 13
#define MOTOR_DER_A 10
#define MOTOR_DER_B 11

const bool LINEA_DETECTADA = LOW;  // LOW para línea negra, HIGH para línea blanca

void setup() {
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(IR_SENSOR, INPUT);
    
    pinMode(MOTOR_IZQ_A, OUTPUT);
    pinMode(MOTOR_IZQ_B, OUTPUT);
    pinMode(MOTOR_DER_A, OUTPUT);
    pinMode(MOTOR_DER_B, OUTPUT);
    
    Serial.begin(9600);

    delay(5000);
}

long medirDistancia() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    
    long duration = pulseIn(ECHO, HIGH);
    return duration * 0.034 / 2; // Convierte a cm
}

void moverAdelante() {
    digitalWrite(MOTOR_IZQ_A, HIGH);
    digitalWrite(MOTOR_IZQ_B, LOW);
    digitalWrite(MOTOR_DER_A, HIGH);
    digitalWrite(MOTOR_DER_B, LOW);
}

void moverAtras() {
    digitalWrite(MOTOR_IZQ_A, LOW);
    digitalWrite(MOTOR_IZQ_B, HIGH);
    digitalWrite(MOTOR_DER_A, LOW);
    digitalWrite(MOTOR_DER_B, HIGH);
}

void girarIzquierda() {
    digitalWrite(MOTOR_IZQ_A, LOW);
    digitalWrite(MOTOR_IZQ_B, HIGH);
    digitalWrite(MOTOR_DER_A, HIGH);
    digitalWrite(MOTOR_DER_B, LOW);
}

void girarDerecha() {
    digitalWrite(MOTOR_IZQ_A, HIGH);
    digitalWrite(MOTOR_IZQ_B, LOW);
    digitalWrite(MOTOR_DER_A, LOW);
    digitalWrite(MOTOR_DER_B, HIGH);
}

void detener() {
    digitalWrite(MOTOR_IZQ_A, LOW);
    digitalWrite(MOTOR_IZQ_B, LOW);
    digitalWrite(MOTOR_DER_A, LOW);
    digitalWrite(MOTOR_DER_B, LOW);
}

void loop() {
    long distancia = medirDistancia();
    bool fueraRing = (digitalRead(IR_SENSOR) == LINEA_DETECTADA);

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.print(" cm | Sensor IR: ");
    Serial.println(fueraRing ? "Fuera" : "Dentro");

    if (fueraRing) {
        moverAtras();
        delay(500);
        girarDerecha();
        delay(500);
    } else if (distancia >= 0 && distancia <= 30) {
        moverAdelante();
    } else {
        girarIzquierda();
        delay(100);
        detener();
        delay(300);

    }
}
