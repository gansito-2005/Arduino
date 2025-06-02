const int pin1 = 13;
const int pin2 = 12;

const int led1 = 11;
const int led2 = 10;
const int led3 = 9;
const int led4 = 8;

int value1 = 0;
int value2 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  // Apagar todos los LEDs inicialmente
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
}

void loop() {
  value1 = digitalRead(pin1);
  value2 = digitalRead(pin2);

  if (value1 == HIGH && value2 == HIGH) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } 
  else if (value1 == LOW && value2 == LOW) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  } 
  else if (value1 == HIGH && value2 == LOW) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  } 
  else if (value1 == LOW && value2 == HIGH) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  }

  delay(100);
}
