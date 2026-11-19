// cSpell:disable (Ignorar)
#include "BluetoothSerial.h"

#define LED1_PIN 4
#define LED2_PIN 16
#define LED3_PIN 17
#define LED4_PIN 18
#define LED5_PIN 19
#define LED6_PIN 21
#define LED7_PIN 22
#define LED8_PIN 23

BluetoothSerial SerialBT;
String modo;

void setup() {
  Serial.begin(115200);  
  delay(10000);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
  pinMode(LED4_PIN, OUTPUT);
  pinMode(LED5_PIN, OUTPUT);
  pinMode(LED6_PIN, OUTPUT);
  pinMode(LED7_PIN, OUTPUT);
  pinMode(LED8_PIN, OUTPUT);

  while (modo != "1" && modo != "2") {
    Serial.println("Seleccione el Modo");
    Serial.println("1 -> Maestro");
    Serial.println("2 -> Esclavo");

    while (Serial.available() ==  0) {}
    modo = Serial.readStringUntil('\n');
    modo.trim();

    delay(2000);
  }

  if(modo == "1"){
    SerialBT.begin("Maestro", true);
    Serial.println("Modo: Maestro");

    while (!SerialBT.connect("Esclavo")) {
      delay(1000);
    }
    Serial.println("Conexion Exitosa");
  } else {
    SerialBT.begin("Esclavo");
    Serial.println("Modo: Esclavo");
  }
}

void loop() {
  if (modo == "1"){
    Serial.println(); 
    maestro();
  }

  if (modo == "2"){
    esclavo();
  }

  delay(1000);
}

void maestro( void ){
  String entrada;
  uint8_t val1 = 0;
  uint8_t val2 = 0;  
  int numero = 0;

  // Escribir val1
  Serial.println("Escriba un numero entre 0 y 255");
  
  while (Serial.available() ==  0) {}
  entrada = Serial.readStringUntil('\n');
  entrada.trim();

  numero = entrada.toInt();

  if (numero < 0 || numero > 255) {
    Serial.println("Numero fuera de rango");
    return;
  }

  val1 = (uint8_t)numero;

  // Enviar val1
  if (SerialBT.connected()) {
    SerialBT.write((uint8_t*)&val1, sizeof(val1));

    Serial.print("Maestro envio: ");
    Serial.println(val1);
  } else {
    Serial.println("Conexion perdida");
  }

  // Recibir val2
  if (!recibirDato(val2)) {
    return;
  }
    
  Serial.print("Maestro recibio: ");
  Serial.println(val2);
  

  // Operar valores
  operar(val1, val2);
}

void esclavo( void ) {
  String entrada;
  uint8_t val1 = 0;
  uint8_t val2 = 0;
  int numero = 0;

  // Escribir val1
  Serial.println("Escriba un numero entre 0 y 255");
  while (Serial.available() ==  0) {}
  entrada = Serial.readStringUntil('\n');
  entrada.trim();

  numero = entrada.toInt();

  if (numero < 0 || numero > 255) {
    Serial.println("Numero fuera de rango");
    return;
  }

  val1 = (uint8_t)numero;
  
  // Recibir val2
  if (!recibirDato(val2)) {
    return;
  }
  
  Serial.println("Esclavo recibio:");
  Serial.println(val2);

  // Enviar val1
  if (SerialBT.connected()) { 
    SerialBT.write((uint8_t*)&val1, sizeof(val1));

    Serial.print("Esclavo envio: ");
    Serial.println(val1);
  } else {
    Serial.println("Conexion perdida");
  }

  // Operar valores
  operar(val2, val1);

}

bool recibirDato(uint8_t &dato) {
  unsigned long inicio = millis();

  while (SerialBT.available() < sizeof(dato)) {
    if (millis() - inicio >= 10000) {
      Serial.println("Error: tiempo de espera agotado");
      return false;
    }
    delay(10);
  }

  SerialBT.readBytes((uint8_t*)&dato, sizeof(dato));
  return true;
}

void operar(int val1, int val2 ){
  String op;
  int res = 0;

  while (op != "1" && op != "2" && op != "3" && op != "4") {
    Serial.println("Seleccione el Modo");
    Serial.println("1 -> Suma");
    Serial.println("2 -> Resta");
    Serial.println("3 -> Multiplicacion");
    Serial.println("4 -> Division");

    while (Serial.available() ==  0) {}
    op = Serial.readStringUntil('\n');
    op.trim();
  }

  if (op == "1"){
    res = val1 + val2;
  } else if (op == "2"){
    res = val1 - val2;
  } else if (op == "3"){
    res = val1 * val2;
  } else {
    if (val2 != 0){
      res = val1 / val2;
    } else {
      Serial.println("Division por 0");
    }
  }

  Serial.println("Resultado:");
  Serial.println(res);

  if (res < 0 || res > 255) {
    Serial.println("Numero fuera de rango");
    return;
  }
  
  mostrarBinario((uint8_t)res);
}

void mostrarBinario(uint8_t numero) {
  int pines[] = {
    LED1_PIN, LED2_PIN, LED3_PIN, LED4_PIN,
    LED5_PIN, LED6_PIN, LED7_PIN, LED8_PIN
  };

  for (int i = 0; i < 8; i++) {
    digitalWrite(pines[i], (numero >> i) & 1);
  }
}