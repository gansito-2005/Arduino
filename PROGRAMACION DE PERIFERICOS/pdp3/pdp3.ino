const int pin1 = 13;
const int pin2 = 12;
const int pin3 = 11;
const int pin4 = 10;

const int led1 = 9;
const int led2 = 8;
const int led3 = 7;
const int led4 = 6;

int value1 = 0;
int value2 = 0;
int value3 = 0;
int value4 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(pin4, INPUT);
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
  value3 = digitalRead(pin3);
  value4 = digitalRead(pin4);

  if (value1 == LOW && value2 == LOW && value3 == LOW && value4 == LOW) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } 

  else if (value1 == LOW && value2 == HIGH && value3 == LOW && value4 == LOW) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } 

  else if (value1 == HIGH && value2 == LOW && value3 == LOW && value4 == LOW) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } 

  else if (value1 == HIGH && value2 == HIGH && value3 == LOW && value4 == LOW) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  }

  else if (value1 == HIGH && value2 == HIGH && value3 == HIGH && value4 == HIGH) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } 

  else if (value3 == LOW && value4 == HIGH) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
  } 

  else if (value3 == HIGH && value4 == LOW) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
  } 

  else if (value1 == LOW && value2 == LOW && value3 == HIGH && value4 == HIGH) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
  }

  delay(100);
}
