// Pin donde está conectado el LED infrarrojo
const int pinIR = 3;

void setup() {
  pinMode(pinIR, OUTPUT);

  // Configurar Timer2 para generar PWM a 38 kHz en el pin 3
  // Esta configuración es específica para placas como Arduino UNO
  TCCR2A = _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20); // Sin preescaler
  OCR2A = 210;  // Valor para 38 kHz
  OCR2B = 105;  // 50% de ciclo de trabajo
}

void loop() {
  // Enviar señal IR a 38kHz por 500 ms
  TCCR2A |= _BV(COM2B1); // Activar salida PWM en pin 3
  delay(500);            // Duración de la señal

  // Detener la señal
  TCCR2A &= ~_BV(COM2B1); // Desactivar salida PWM
  delay(5000);            // Esperar 5 segundos antes de volver a enviar
}
