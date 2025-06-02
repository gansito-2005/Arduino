int led  = 5;
int foc1 = 3;
int foc2 = 4;
int boton = 2;

volatile int estado = 0; // variable para almacenar el estado de los focos

void setup() {
       Serial.begin(9600);

  pinMode(foc1, OUTPUT);
  pinMode(foc2, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT_PULLUP); // Configuramos el botón con resistencia interna de pull-up

  attachInterrupt(digitalPinToInterrupt(boton), cambiarEstado, FALLING); // Interrupción al presionar el botón
}

void loop() {
  // Ciclo de parpadeo del LED cada 1000 ms
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}

void cambiarEstado() {
  estado++; // Cambiamos al siguiente estado
  if (estado > 2) {
    estado = 0; // Regresamos al estado inicial después de apagar los focos
  }

  // Controlamos los focos según el estado
  switch (estado) {
    case 0:
      digitalWrite(foc1, LOW);
      digitalWrite(foc2, LOW);
      Serial.println("APAGADO");
      break;
    case 1:
      digitalWrite(foc1, HIGH);
      digitalWrite(foc2, LOW);
      Serial.println("ENCENDIDO FOCO VERDE");
      break;
    case 2:
      digitalWrite(foc1, LOW);
      digitalWrite(foc2, HIGH);
      Serial.println("ENCENDIDO FOCO blanco");
      break;
  }
}
