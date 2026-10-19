# Implementasi Protokol Komunikasi SPI pada Modul Flash Memory W25Qxx sebagai Media Penyimpanan Data Logger Sinyal Analog

Proyek ini mendemonstrasikan implementasi sistem **Data Logger** berbasis mikrokontroler (Arduino Uno) menggunakan **Flash Memory W25Qxx** berteknologi **NOR Flash** dengan antarmuka komunikasi **SPI (Serial Peripheral Interface)**. Sistem ini mencatat data sinyal analog (bacaan potensiometer) berupa *timestamp*, nilai mentah ADC, dan konversi tegangan secara non-volatile.

---

## 📑 Daftar Isi
- [Teori & Arsitektur Memori](#teori--arsitektur-memori)
- [Aturan Erase-Before-Write](#aturan-erase-before-write)
- [Skema Pinout & Rangkaian](#skema-pinout--rangkaian)
- [Prasyarat & Dependensi](#prasyarat--dependensi)
- [Kode Program](#kode-program)
- [Penjelasan Alur Kerja](#penjelasan-alur-kerja)
- [Hasil Output Serial Terminal](#hasil-output-serial-terminal)

---

## 🧠 Teori & Arsitektur Memori

### 1. Karakteristik W25Qxx NOR Flash
Modul **Winbond W25Qxx** adalah sirkuit terintegrasi memori *non-volatile* berjenis NOR Flash yang dirancang untuk penyimpanan data berkapasitas besar dan berkecepatan tinggi.

* **Kapasitas Seri Modul:**
  * W25Q16: 16 Mbit (2 MB)
  * W25Q32: 32 Mbit (4 MB)
  * W25Q64: 64 Mbit (8 MB)
  * W25Q128: 128 Mbit (16 MB)

* **Pengorganisasian Hirarki Memori:**
  * **Page (256 Byte):** Unit terkecil penulisan data (batas maksimum satu instruksi *Page Program*).
  * **Sector (4 KB / 4.096 Byte):** Terdiri dari 16 Page. Unit terkecil untuk proses penghapusan (*Sector Erase*).
  * **Block (64 KB):** Terdiri dari 16 Sector.

---

## 🔄 Aturan Erase-Before-Write

Karakteristik dasar teknologi NOR Flash pada W25Qxx adalah aturan **Erase-Before-Write** (penghapusan sebelum penulisan):
* Dalam kondisi terhapus (*erased state*), seluruh bit berada pada logika `1` (nilai byte default `0xFF` / `11111111`).
* Operasi penulisan (*programming*) hanya bisa mengubah bit dari `1` menjadi `0`.
* Untuk mengembalikan bit `0` menjadi `1`, sistem harus melakukan penghapusan (*erase*) minimal setingkat **Sector (4 KB)**.
* Ketahanan siklus hapus-tulis (*endurance*) memori ini mencapai sekitar **100.000 kali per sektor**.

---

## 🔌 Skema Pinout & Rangkaian

> ⚠️ **PERHATIAN TEGANGAN:** Tegangan kerja modul W25Qxx adalah **3.3V**. Hubungkan VCC ke pin **3.3V Arduino**. **Jangan ke 5V** agar IC memori tidak rusak!

| Pin Modul W25Qxx | Pin Arduino Uno | Keterangan |
| :--- | :--- | :--- |
| **VCC** | **3.3V** | Catu daya utama (Jangan hubungkan ke 5V) |
| **GND** | **GND** | Ground bersama (*Common Ground*) |
| **CS** | **Pin 10** | *Chip Select* (Active-Low) |
| **CLK / SCK** | **Pin 13** | *Serial Clock* |
| **DO / MISO** | **Pin 12** | *Master In Slave Out* |
| **DI / MOSI** | **Pin 11** | *Master Out Slave In* |
| **Analog In** | **Pin A0** | Terhubung ke kaki tengah Potensiometer |

> **Fitur Proteksi Hardware:** Pin `/WP` (Write Protect) berfungsi mengunci Status Register, dan pin `/HOLD` berfungsi menunda komunikasi SPI. Pada modul praktis, kedua pin ini umumnya sudah terhubung ke 3.3V.

---

## 🛠️ Prasyarat & Dependensi

* **IDE:** PlatformIO IDE / Arduino IDE
* **Pustaka (Library):** `SPIMemory` oleh Marzogh
* **Baud Rate Serial:** 115200 bps

---

## 💻 Kode Program

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
