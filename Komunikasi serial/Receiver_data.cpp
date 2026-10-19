
#include <Arduino.h>
#include <SoftwareSerial.h>

// ==================== Konfigurasi ====================

namespace Config {
  constexpr uint8_t SOFTWARE_SERIAL_RX_PIN = 10;
  constexpr uint8_t SOFTWARE_SERIAL_TX_PIN = 11;

  constexpr uint32_t SERIAL_BAUD_RATE = 9600;
  constexpr uint32_t SOFTWARE_SERIAL_BAUD_RATE = 9600;

  constexpr char MESSAGE_RECEIVER_READY[] = "RECEIVER READY";
}

// ==================== Objek Serial ====================

SoftwareSerial mySerial(
  Config::SOFTWARE_SERIAL_RX_PIN,
  Config::SOFTWARE_SERIAL_TX_PIN
);

// ==================== Deklarasi Fungsi ====================

void initializeSerial();
void receiveData();

// ==================== Setup ====================

void setup() {
  initializeSerial();
}

// ==================== Loop ====================

void loop() {
  receiveData();
}

// ==================== Implementasi Fungsi ====================

void initializeSerial() {
  Serial.begin(Config::SERIAL_BAUD_RATE);
  mySerial.begin(Config::SOFTWARE_SERIAL_BAUD_RATE);

  Serial.println(Config::MESSAGE_RECEIVER_READY);
}

void receiveData() {
  while (mySerial.available() > 0) {
    const int receivedByte = mySerial.read();

    if (receivedByte != -1) {
      Serial.write(static_cast<uint8_t>(receivedByte));
    }
  }
}
