
#include <Arduino.h>

// ==================== Konfigurasi ====================

namespace Config {
  constexpr uint8_t BUTTON_PIN = 2;
  constexpr uint8_t LED_PIN = 8;

  constexpr uint32_t SERIAL_BAUD_RATE = 9600;
  constexpr uint32_t DEBOUNCE_INTERVAL_MS = 50;

  constexpr uint8_t BUTTON_PRESSED = LOW;
  constexpr uint8_t LED_ON = HIGH;
  constexpr uint8_t LED_OFF = LOW;

  constexpr char MESSAGE_SYSTEM_READY[] =
      "Sistem siap. Silakan tekan tombol!";
  constexpr char MESSAGE_BUTTON_PRESSED[] =
      "Tombol ditekan! Total: ";
  constexpr char MESSAGE_LED_ON[] = "MENYALA";
  constexpr char MESSAGE_LED_OFF[] = "MATI";
}

// ==================== Variabel Global ====================

bool ledState = false;

uint8_t buttonState = HIGH;
uint8_t lastButtonReading = HIGH;

uint32_t lastDebounceTime = 0;
uint32_t pressCount = 0;

// ==================== Deklarasi Fungsi ====================

void initializeSystem();
void updateButton();
void handleButtonPress();
void printStatus();

// ==================== Setup ====================

void setup() {
  initializeSystem();
}

// ==================== Loop ====================

void loop() {
  updateButton();
}

// ==================== Implementasi Fungsi ====================

void initializeSystem() {
  pinMode(Config::BUTTON_PIN, INPUT_PULLUP);
  pinMode(Config::LED_PIN, OUTPUT);

  digitalWrite(Config::LED_PIN, Config::LED_OFF);

  Serial.begin(Config::SERIAL_BAUD_RATE);
  Serial.println(Config::MESSAGE_SYSTEM_READY);
}

void updateButton() {
  const uint32_t currentTime = millis();
  const uint8_t currentReading = digitalRead(Config::BUTTON_PIN);

  if (currentReading != lastButtonReading) {
    lastDebounceTime = currentTime;
  }

  if (currentTime - lastDebounceTime >=
      Config::DEBOUNCE_INTERVAL_MS) {
    if (currentReading != buttonState) {
      buttonState = currentReading;

      if (buttonState == Config::BUTTON_PRESSED) {
        handleButtonPress();
      }
    }
  }

  lastButtonReading = currentReading;
}

void handleButtonPress() {
  ledState = !ledState;

  digitalWrite(
    Config::LED_PIN,
    ledState ? Config::LED_ON : Config::LED_OFF
  );

  ++pressCount;

  printStatus();
}

void printStatus() {
  Serial.print(Config::MESSAGE_BUTTON_PRESSED);
  Serial.print(pressCount);
  Serial.print(" | Status LED: ");

  Serial.println(
    ledState ? Config::MESSAGE_LED_ON : Config::MESSAGE_LED_OFF
  );
}
