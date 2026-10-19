
#include <Arduino.h>
#include <SPIMemory.h>

// ==================== HARDWARE CONFIGURATION ====================
constexpr uint8_t FLASH_CS_PIN = 10;
constexpr uint8_t POTENTIOMETER_PIN = A0;

// ==================== SERIAL CONFIGURATION ====================
constexpr unsigned long SERIAL_BAUD_RATE = 115200;
constexpr unsigned long SERIAL_INITIALIZATION_DELAY_MS = 2000;

// ==================== ADC CONFIGURATION ====================
constexpr uint16_t ADC_MAX_VALUE = 1023;
constexpr float ADC_REFERENCE_VOLTAGE = 5.0F;
constexpr uint8_t VOLTAGE_DECIMAL_PLACES = 2;

// ==================== DATA LOGGING CONFIGURATION ====================
constexpr uint32_t FLASH_START_ADDRESS = 0x00;
constexpr uint16_t TOTAL_SAMPLES = 5;
constexpr unsigned long SAMPLING_INTERVAL_MS = 1000;

// ==================== FLASH MEMORY OBJECT ====================
SPIFlash flash(FLASH_CS_PIN);

// ==================== DATA STRUCTURE ====================
struct DataLog {
    uint32_t timestamp;
    int adcValue;
    float voltage;
};

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    delay(SERIAL_INITIALIZATION_DELAY_MS);

    // Initialize Flash Memory
    if (!flash.begin()) {
        Serial.println("ERROR: Flash Memory initialization failed!");

        while (true) {
            // Stop execution if Flash Memory is unavailable
        }
    }

    Serial.println("=== DATA LOGGING STARTED ===");

    // Erase the sector before writing new data
    Serial.println("Erasing Flash Memory sector...");

    if (!flash.eraseSector(FLASH_START_ADDRESS)) {
        Serial.println("ERROR: Failed to erase Flash Memory sector!");
        return;
    }

    uint32_t currentAddress = FLASH_START_ADDRESS;

    // ==================== DATA WRITING ====================
    for (uint16_t sampleIndex = 1;
         sampleIndex <= TOTAL_SAMPLES;
         ++sampleIndex) {

        DataLog dataInput{};

        // Acquire analog sensor data
        dataInput.timestamp = millis();
        dataInput.adcValue = analogRead(POTENTIOMETER_PIN);

        dataInput.voltage =
            (static_cast<float>(dataInput.adcValue) / ADC_MAX_VALUE)
            * ADC_REFERENCE_VOLTAGE;

        // Write data to Flash Memory
        if (flash.writeAnything(currentAddress, dataInput)) {
            Serial.print("[WRITE] Sample #");
            Serial.print(sampleIndex);
            Serial.print(" stored at address: 0x");
            Serial.println(currentAddress, HEX);
        } else {
            Serial.println("[ERROR] Failed to write data.");
        }

        // Advance to the next record
        currentAddress += sizeof(DataLog);

        if (sampleIndex < TOTAL_SAMPLES) {
            delay(SAMPLING_INTERVAL_MS);
        }
    }

    Serial.println();
    Serial.println("=== READING DATA FROM FLASH MEMORY ===");

    // ==================== DATA READING ====================
    currentAddress = FLASH_START_ADDRESS;

    for (uint16_t sampleIndex = 1;
         sampleIndex <= TOTAL_SAMPLES;
         ++sampleIndex) {

        DataLog dataOutput{};

        // Read data from Flash Memory
        if (flash.readAnything(currentAddress, dataOutput)) {
            Serial.print("Sample #");
            Serial.print(sampleIndex);

            Serial.print(" | Timestamp: ");
            Serial.print(dataOutput.timestamp);
            Serial.print(" ms");

            Serial.print(" | ADC: ");
            Serial.print(dataOutput.adcValue);

            Serial.print(" | Voltage: ");
            Serial.print(
                dataOutput.voltage,
                VOLTAGE_DECIMAL_PLACES
            );

            Serial.println(" V");
        } else {
            Serial.print("[ERROR] Failed to read sample #");
            Serial.println(sampleIndex);
        }

        // Advance to the next record
        currentAddress += sizeof(DataLog);
    }

    Serial.println();
    Serial.println("=== DATA LOGGING COMPLETED ===");
}

void loop() {
    // No continuous processing is required.
}
