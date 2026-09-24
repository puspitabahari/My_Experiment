#include <Arduino.h>
const int potPin = A0; // Pin analog untuk membaca potensiometer

void setup() {
  // Inisialisasi komunikasi Serial dengan kecepatan 9600 bps
  Serial.begin(9600); 
}

void loop() {
  // Read nilai mentah ADC (0 - 1023)
  int adcValue = analogRead(potPin);
  
  // Konversi nilai ADC ke satuan Volt
  float voltage = (adcValue / 1023.0) * 5.0;

  // Tampilkan hasil di Serial Monitor
  Serial.print("Nilai ADC: ");
  Serial.print(adcValue);
  Serial.print(" \t| Tegangan: ");
  Serial.print(voltage, 2); // 2 angka di belakang koma
  Serial.println(" V");

  delay(200); // Jeda pembacaan
}