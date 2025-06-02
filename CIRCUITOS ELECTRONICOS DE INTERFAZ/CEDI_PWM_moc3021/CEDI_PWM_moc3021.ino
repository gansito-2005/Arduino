#include <TimerOne.h>  // Biblioteca para el temporizador 1

// Pines
const int pinTriac = 3;  // Salida al triac
const int pinPot = A0;   // Potenciómetro conectado a A0
const int pinInterrupcion = 2;  // Pin para detección de cruce por cero

// Variables globales
volatile int contador = 0;       // Contador para el temporizador
volatile boolean cruceCero = false; // Bandera para el cruce por cero
int dimmer;                      // Valor de retardo calculado según el potenciómetro
int tiempoInterrupcion = 100;    // Tiempo base para el temporizador en microsegundos
unsigned long tiempoEntrada = 0; // Tiempo de detección de cruce por cero
unsigned long tiempoSalida = 0;  // Tiempo de disparo del triac

void setup() {
  pinMode(pinTriac, OUTPUT);             // Configurar el pin del triac como salida
  attachInterrupt(digitalPinToInterrupt(pinInterrupcion), deteccionCruce, RISING); // Configurar interrupción en cruce por cero
  Timer1.initialize(tiempoInterrupcion); // Inicializar el temporizador con un tiempo base
  Timer1.attachInterrupt(gestionarTriac); // Vincular la función del temporizador
  Serial.begin(9600);               // Inicializar el monitor serial
}

void loop() {
  // Leer el valor del potenciómetro
  int lecturaPot = analogRead(pinPot);     
  
  // Escalar el valor a un rango adecuado (entre 0 y 83)
  dimmer = map(lecturaPot, 0, 1023, 0, 83); 
  
  // Calcular el porcentaje de luminosidad
  float porcentajeLuminosidad = (1.0 - dimmer / 83.0) * 100.0;

  // Mostrar los datos en el monitor serial
  Serial.print("Valor Analogico: ");
  Serial.print(lecturaPot);
  Serial.print(", Porcentaje de Luminosidad: ");
  Serial.print(porcentajeLuminosidad, 2); // Mostrar con 2 decimales
  Serial.print("%, Tiempo de Entrada: ");
  Serial.print(tiempoEntrada);
  Serial.print(" us, Tiempo de Salida: ");
  Serial.print(tiempoSalida);
  Serial.println(" us");

  delay(500); // Esperar un poco para no saturar el monitor serial
}

// Función llamada por la interrupción de cruce por cero
void deteccionCruce() {
  cruceCero = true;        // Activar la bandera de cruce por cero
  contador = 0;            // Reiniciar el contador
  digitalWrite(pinTriac, LOW); // Apagar el triac
  tiempoEntrada = micros();  // Registrar el tiempo del cruce por cero
}

// Función del temporizador para gestionar el disparo del triac
void gestionarTriac() {
  if (cruceCero) {                // Si estamos en el ciclo activo
    if (contador >= dimmer) {     // Si alcanzamos el tiempo de retardo
      digitalWrite(pinTriac, HIGH); // Encender el triac
      cruceCero = false;           // Desactivar la bandera
      tiempoSalida = micros();     // Registrar el tiempo de disparo
    } else {
      contador++;                 // Incrementar el contador
    }
  }
}
