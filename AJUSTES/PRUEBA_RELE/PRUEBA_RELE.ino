int pinRelevador = 2;

void setup() {
  pinMode(pinRelevador, OUTPUT);
  digitalWrite(pinRelevador,HIGH); // Por defecto dejaremos el
                                   // relevador desactivado.
}

void loop() {
  delay(300000);
  digitalWrite(pinRelevador,LOW);
  delay(9000000);
  digitalWrite(pinRelevador,HIGH);
}
