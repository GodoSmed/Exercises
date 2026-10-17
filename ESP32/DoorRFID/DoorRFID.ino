// cSpell:disable (Ignorar)
#include <SPI.h>
#include <MFRC522.h>
#include <ESP32Servo.h>
#include <EEPROM.h>

//Memoria
#define MAX_TARJETAS 100      
#define LONGITUD_UID 9        
#define DIRECCION_INICIAL 0
#define TAMANO_EEPROM (MAX_TARJETAS * LONGITUD_UID) // 900 bytes

//Pines
#define RST_PIN 22 
#define SS_PIN  5
#define servo_PIN 4
#define LED1_PIN 16
#define LED2_PIN 17
#define trigger_PIN 25
#define echo_PIN 26
#define buzzer_PIN 0

//Variables
String uid_actual = "";
String tarjeta_maestra = "BB68B155";
String opcion = "";
Servo servo;
MFRC522 mfrc522(SS_PIN, RST_PIN); 

void setup() {
  Serial.begin(115200);  
  delay(10000);

  //Inicializar RC522
  SPI.begin();          
  mfrc522.PCD_Init();   
  delay(1000);

  byte version = mfrc522.PCD_ReadRegister(mfrc522.VersionReg);

  if (version == 0x00 || version == 0xFF) {
    Serial.println(F("Error de conexion con RC522"));
    while (true) {
      delay(1000); 
    }
  }

  if (!EEPROM.begin(TAMANO_EEPROM)) {
    Serial.println(F("Error al inicializar la EEPROM"));
    while (true) {
      delay(1000); 
    }
  }

  //Leds
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  //SR04
  pinMode(trigger_PIN, OUTPUT); 
  pinMode(echo_PIN, INPUT);  
  digitalWrite(trigger_PIN, LOW);

  //Servo
  servo.attach(servo_PIN, 500, 2400);
}

void loop() {
  Serial.println(F("Acerca una tarjeta o llavero RFID al lector..."));
  
  while (!check_RFID()) {
    delay(15);
  }

  if(uid_actual == tarjeta_maestra){ //Tarjeta Mestra
    while(!menuAdmin()){
      delay(1000);
    }
  } else if (tarjeta_existente()){ //Tarjeta Usuario
    Serial.println(F("Tarjeta registrada"));
    Serial.println(F("Abriendo ..."));
    led_verde();
    abrir();
  } 
  else { // Tarjeta no registrada
    Serial.println(F("Tarjeta NO registrada"));
    led_rojo();
  }
  
  delay(5000); 
}

bool check_RFID( void ){
  // No hay tarjeta en el lector 
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

  // Fallo la lectura
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  uid_actual = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uid_actual += "0";
    }
    uid_actual += String(mfrc522.uid.uidByte[i], HEX);
  }
  uid_actual.toUpperCase();

  Serial.print(F("UID leido: "));
  Serial.println(uid_actual);

  // Detener la comunicación con la tarjeta
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();

  return true;
}

bool menuAdmin( void ){
  Serial.println(F("Tarjeta Maestra Detectada"));
  Serial.println(F("Menu Administrador"));
  Serial.println(F("1. Agregar Tarjeta"));
  Serial.println(F("2. Eliminar Tarjeta"));
  Serial.println(F("3. Salir del Menu"));

  while (Serial.available() ==  0) {}

  String opcion = Serial.readStringUntil('\n');
  opcion.trim();

  if(opcion == "1"){ //Agregar tarjeta
    Serial.println(F("Acerca una tarjeta o llavero RFID al lector..."));
    while (check_RFID() == 0) {
      delay(15);
    }

    if(!tarjeta_existente() && !(uid_actual == tarjeta_maestra)){
      bool guardado_exitoso = false;

      for (int i = 0; i < MAX_TARJETAS; i++) {
        int direccion = DIRECCION_INICIAL + (i * LONGITUD_UID);
        byte primer_byte = EEPROM.read(direccion);

        // Posicion vacia
        if (primer_byte == 0 || primer_byte == 255) {
          // Guardar el String uid_actual carácter por carácter
          for (int j = 0; j < LONGITUD_UID; j++) {
            if (j < uid_actual.length()) {
              EEPROM.write(direccion + j, uid_actual[j]);
            } else {
              EEPROM.write(direccion + j, 0); 
            }
          }
          EEPROM.commit(); 
          Serial.println(F("¡Tarjeta guardada con éxito!"));
          guardado_exitoso = true;
          led_verde;
          break;
        }
      }

      if (!guardado_exitoso) {
        Serial.println(F("Memoria llena. No se pueden guardar más tarjetas."));
        led_rojo();
      }
    } else {
      Serial.println(F("Tarjeta Existente o Maestra"));
      led_rojo();
    }
  } 
  else if(opcion == "2"){ //Eliminar tarjeta
    Serial.println(F("Acerca una tarjeta o llavero RFID al lector..."));
    while (check_RFID() == 0) {
      delay(15);
    }

    bool eliminado_exitoso = false;
    for (int i = 0; i < MAX_TARJETAS; i++) {
      int direccion = DIRECCION_INICIAL + (i * LONGITUD_UID);
      
      char uid_almacenado[LONGITUD_UID];
      
      // Leer el UID desde la EEPROM
      for (int j = 0; j < LONGITUD_UID; j++) {
        uid_almacenado[j] = EEPROM.read(direccion + j);
      }

      // Si coincide con el leído
      if (uid_actual.equals(String(uid_almacenado))) {
        for (int j = 0; j < LONGITUD_UID; j++) {
          EEPROM.write(direccion + j, 0x00);
        }
        EEPROM.commit(); 
        Serial.println(F("¡Tarjeta eliminada de la memoria con éxito!"));
        eliminado_exitoso = true;
        led_verde();
        break;
      }
    }

    if (!eliminado_exitoso) {
      Serial.println(F("La tarjeta no existia en memoria"));
      led_rojo();
    }
    
  } 
  else if(opcion == "3"){
    Serial.println(F("Saliendo del menu..."));
    return true;
  }

  return false;
}

bool tarjeta_existente( void ){
  for (int i = 0; i < MAX_TARJETAS; i++) {
    int direccion = DIRECCION_INICIAL + (i * LONGITUD_UID);
    
    char uid_almacenado[LONGITUD_UID];
    
    // Leer el UID desde la EEPROM
    for (int j = 0; j < LONGITUD_UID; j++) {
      uid_almacenado[j] = EEPROM.read(direccion + j);
    }

    // Si coincide con el leído
    if (uid_actual.equals(String(uid_almacenado))) {
      return true; // Encontrado
    }
  }
  return false; 
}

void led_verde ( void ){
  digitalWrite(LED1_PIN, HIGH);
  tone(buzzer_PIN, 2093);
  delay(2000);
  digitalWrite(LED1_PIN, LOW);
  noTone(buzzer_PIN); 
}

void led_rojo ( void ){
  digitalWrite(LED2_PIN, HIGH);
  tone(buzzer_PIN, 1000); 
  delay(2000);
  digitalWrite(LED2_PIN, LOW);
  noTone(buzzer_PIN); 
}

void abrir( void ){
  servo.write(180);
  delay(180);
  servo.write(94);

  delay(10000);
  while(!paso_objeto()){
    delay(1000);
  }
  delay(2000);

  servo.write(0); 
  delay(180);        
  servo.write(94);   
  Serial.println(F("Objeto Paso Exitosamente"));
}

bool paso_objeto(void) {
  digitalWrite(trigger_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(trigger_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_PIN, LOW);

  unsigned long tiempo = pulseIn(echo_PIN, HIGH);

  long distancia = tiempo / 58;

  Serial.println(F("Objeto a"));
  Serial.print(distancia);
  Serial.println();

  if (distancia >= 100 && distancia <= 200) {
    return true;
  } 

  return false;
}

