
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ==================== Konfigurasi ====================

namespace Config {
  constexpr uint8_t LCD_I2C_ADDRESS = 0x27;
  constexpr uint8_t LCD_COLUMNS = 16;
  constexpr uint8_t LCD_ROWS = 2;

  constexpr uint8_t BUTTON_PIN = 2;
  constexpr uint8_t LED_PIN = 8;

  constexpr uint32_t SERIAL_BAUD_RATE = 9600;
  constexpr uint32_t DEBOUNCE_INTERVAL_MS = 50;

  constexpr uint8_t LCD_STATUS_ROW = 0;
  constexpr uint8_t LCD_COUNTER_ROW = 1;
  constexpr uint8_t LCD_START_COLUMN = 0;

  constexpr uint8_t BUTTON_PRESSED = LOW;
  constexpr uint8_t LED_ON = HIGH;
  constexpr uint8_t LED_OFF = LOW;

  constexpr char MESSAGE_LED_ON[] = "TURN ON THE LAMP";
  constexpr char MESSAGE_LED_OFF[] = "TURN OFF THE LAMP";
  constexpr char MESSAGE_COUNTER[] = "Press Count: ";
  constexpr char DATA_SEPARATOR = ',';
}

// ==================== Objek LCD ====================

LiquidCrystal_I2C lcd(
  Config::LCD_I2C_ADDRESS,
  Config::LCD_COLUMNS,
  Config::LCD_ROWS
);

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
void updateLcd();
void transmitData();

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

  lcd.init();
  lcd.backlight();
  lcd.clear();

  updateLcd();
}

void updateButton() {
  const uint32_t currentTime = millis();
  const uint8_t currentReading = digitalRead(Config::BUTTON_PIN);

  if (currentReading != lastButtonReading) {
    lastDebounceTime = currentTime;
  }

  if (currentTime - lastDebounceTime >= Config::DEBOUNCE_INTERVAL_MS) {
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

  updateLcd();
  transmitData();
}

void updateLcd() {
  lcd.clear();

  lcd.setCursor(
    Config::LCD_START_COLUMN,
    Config::LCD_STATUS_ROW
  );

  lcd.print(
    ledState
      ? Config::MESSAGE_LED_ON
      : Config::MESSAGE_LED_OFF
  );

  lcd.setCursor(
    Config::LCD_START_COLUMN,
    Config::LCD_COUNTER_ROW
  );

  lcd.print(Config::MESSAGE_COUNTER);
  lcd.print(pressCount);
}

void transmitData() {
  Serial.print(ledState ? Config::LED_ON : Config::LED_OFF);
  Serial.print(Config::DATA_SEPARATOR);
  Serial.println(pressCount);
}
