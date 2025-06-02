int ledrojo = 13;
int ledamarillo = 12;
int ledverde = 5;
int ledazul = 6;


void setup() {

pinMode(ledrojo, OUTPUT);
pinMode(ledamarillo, OUTPUT);
pinMode(ledverde, OUTPUT);
pinMode(ledazul, OUTPUT);

}

void loop() {

digitalWrite (ledverde, LOW);
delay(1000);

}