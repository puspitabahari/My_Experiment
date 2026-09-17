#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD 16x2 dengan alamat I2C 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Deklarasi Pin
const int buttonPin = 2;
const int ledPin = 8;

// Variabel status
int ledState = LOW;
int buttonState;
int lastButtonState = HIGH;

// Variabel Non-Blocking Debounce & Counter
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int pressCount = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("TURN OFF THE LAMP");

  // Inisialisasi Serial untuk transmisi TX/RX (Baud rate 9600)
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        ledState = !ledState;
        digitalWrite(ledPin, ledState);

        pressCount++;

        // Update LCD transmitter
        lcd.clear();
        lcd.setCursor(0, 0);
        if (ledState == HIGH) {
          lcd.print("TURN ON THE LAMP");
        } else {
          lcd.print("TURN OFF THE LAMP");
        }

        lcd.setCursor(0, 1);
        lcd.print("Press Count: ");
        lcd.print(pressCount);

        // Mengirim data ke Arduino Receiver via Pin TX (Format: "ledState,pressCount")
        Serial.print(ledState);
        Serial.print(",");
        Serial.println(pressCount);
      }
    }
  }

  lastButtonState = reading;
}