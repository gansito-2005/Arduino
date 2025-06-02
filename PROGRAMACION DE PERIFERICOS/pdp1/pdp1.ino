int pin2 = 5;
int pin1 = 4;


const int MOTOR_IZQ_ADELANTE = 13;
const int MOTOR_IZQ_ATRAS = 12;
const int MOTOR_DER_ADELANTE = 11;
const int MOTOR_DER_ATRAS = 10;

int value1 = 0;
int value2 = 0;

void setup() {
  // put your setup code here, to run once:
     Serial.begin(9600);
     pinMode(pin1, INPUT);
     pinMode(pin2, INPUT);

  pinMode(MOTOR_IZQ_ADELANTE, OUTPUT);
  pinMode(MOTOR_IZQ_ATRAS, OUTPUT);
  pinMode(MOTOR_DER_ADELANTE, OUTPUT);
  pinMode(MOTOR_DER_ATRAS, OUTPUT);
}

void configurarMotores(bool izqAdelante, bool izqAtras, bool derAdelante, bool derAtras) {
  digitalWrite(MOTOR_IZQ_ADELANTE, izqAdelante);
  digitalWrite(MOTOR_IZQ_ATRAS, izqAtras);
  digitalWrite(MOTOR_DER_ADELANTE, derAdelante);
  digitalWrite(MOTOR_DER_ATRAS, derAtras);
}

void loop() {
  // put your main code here, to run repeatedly:
  value1 = digitalRead(pin1);
  value2 = digitalRead(pin2);

  if(value1 == HIGH){
    Serial.println("Encendido1");
    configurarMotores(HIGH, LOW, HIGH, LOW);

  }

  else if(value2 == HIGH){
  Serial.println("Encendido2");
  configurarMotores(LOW, HIGH, LOW, HIGH);

  }

  else{
  Serial.println("Apagado");
  configurarMotores(LOW, LOW, LOW, LOW);
  
  }
}

