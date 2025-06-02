#define TRIG A0  // Pin TRIG del sensor ultrasónico
#define ECHO A1  // Pin ECHO del sensor ultrasónico
#define IR_IZQUIERDO 13  // Sensor infrarrojo delantero izquierdo
#define IR_DERECHO 12  // Sensor infrarrojo delantero derecho

// Pines de los motores
#define MOTOR_IZQ_A 7  
#define MOTOR_IZQ_B 6  
#define MOTOR_DER_A 5  
#define MOTOR_DER_B 4  

const bool LINEA_DETECTADA = LOW;  // LOW para línea negra, HIGH para línea blanca

void setup() {
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(IR_IZQUIERDO, INPUT);
    pinMode(IR_DERECHO, INPUT);
    
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
    bool lineaIzquierda = (digitalRead(IR_IZQUIERDO) == LINEA_DETECTADA);
    bool lineaDerecha = (digitalRead(IR_DERECHO) == LINEA_DETECTADA);

    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.print(" cm | Izq: ");
    Serial.print(lineaIzquierda ? "Detectada" : "No detectada");
    Serial.print(" | Der: ");
    Serial.println(lineaDerecha ? "Detectada" : "No detectada");

    if (lineaIzquierda) {
        moverAtras();
        delay(400);
        girarDerecha();
        delay(100);
    } else if (lineaDerecha) {
        moverAtras();
        delay(400);
        girarIzquierda();
        delay(100);
    } else if (distancia >= 0 && distancia <= 30) {
        moverAdelante();
    } else {
        girarIzquierda();
        delay(100);
        detener();
        delay(500);
    }
}

