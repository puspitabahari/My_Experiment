
#include <Arduino.h>

// Pin configuration
constexpr uint8_t POTENTIOMETER_PIN = A0;

// ADC configuration
constexpr uint16_t ADC_MAX_VALUE = 1023;
constexpr float ADC_REFERENCE_VOLTAGE = 5.0F;

// Serial communication configuration
constexpr unsigned long SERIAL_BAUD_RATE = 9600;

// Sampling configuration
constexpr unsigned long SAMPLING_INTERVAL_MS = 200;

// Output configuration
constexpr uint8_t VOLTAGE_DECIMAL_PLACES = 2;

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
}

void loop() {
    // Read raw ADC value
    const int adcValue = analogRead(POTENTIOMETER_PIN);

    // Convert ADC value to voltage
    const float voltage =
        (static_cast<float>(adcValue) / ADC_MAX_VALUE)
        * ADC_REFERENCE_VOLTAGE;

    // Display measurement results
    Serial.print("ADC Value: ");
    Serial.print(adcValue);
    Serial.print("\t| Voltage: ");
    Serial.print(voltage, VOLTAGE_DECIMAL_PLACES);
    Serial.println(" V");

    delay(SAMPLING_INTERVAL_MS);
}
