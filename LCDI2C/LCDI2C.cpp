#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD 16x2 dengan alamat I2C 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Deklarasi Pin
const int buttonPin = 2;
const int ledPin = 8;

// Variabel untuk menyimpan status
int ledState = LOW;
int buttonState;
int lastButtonState = HIGH;  // HIGH karena memakai INPUT_PULLUP

// Variabel untuk Non-Blocking Debounce & Counter
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;    // Jeda waktu debounce 50 ms
int pressCount = 0;                  // Counter jumlah tekanan tombol

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  
  // Tampilan awal di LCD
  lcd.setCursor(0, 0);
  lcd.print("TURN OFF THE LAMP");

  // Memulai komunikasi Serial Port
  Serial.begin(9600);
  Serial.println("Sistem Siap. Silakan tekan tombol!");
}

void loop() {
  // Membaca status tombol saat ini
  int reading = digitalRead(buttonPin);

  // Jika status tombol berubah (karena ditekan atau noise/bouncing)
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset timer debounce
  }

  // Jika bacaan sudah stabil melebihi waktu debounceDelay
  if ((millis() - lastDebounceTime) > debounceDelay) {

    // Jika status tombol benar-benar berubah dari state sebelumnya
    if (reading != buttonState) {
      buttonState = reading;

      // INPUT_PULLUP berarti saat tombol ditekan, statusnya LOW
      if (buttonState == LOW) {
        ledState = !ledState; // Balikkan status LED (Toggle)
        digitalWrite(ledPin, ledState); // Nyalakan/matikan LED

        pressCount++; // Tambah nilai counter

        // Update tampilan LCD
        lcd.clear();
        lcd.setCursor(0, 0);
        if (ledState == HIGH) {
          lcd.print("TURN ON THE LAMP");
        } else {
          lcd.print("TURN OFF THE LAMP");
        }

        // Menampilkan counter pada baris kedua LCD
        lcd.setCursor(0, 1);
        lcd.print("Press Count: ");
        lcd.print(pressCount);

        // Tampilkan informasi di Serial Monitor
        Serial.print("Tombol ditekan! Total: ");
        Serial.print(pressCount);
        Serial.print(" | Status LED: ");
        Serial.println(ledState == HIGH ? "MENYALA (Silakan ukur tegangan!)" : "MATI");
      }
    }
  }

  // Simpan status bacaan untuk iterasi loop berikutnya
  lastButtonState = reading;
}