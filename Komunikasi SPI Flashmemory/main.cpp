#include <Arduino.h>
#include <SPIMemory.h>

SPIFlash flash(10); // Pin CS ke pin 10

// 1. Definisikan Struktur Data (Paket data logger)
struct DataLog {
  uint32_t timestamp; // Waktu dalam milidetik (millis)
  int adcValue;       // Nilai mentah ADC (0 - 1023)
  float voltage;      // Hasil konversi ke tegangan (Volt)
};

const uint32_t START_ADDRESS = 0x00; // Alamat awal penyimpanan
const int TOTAL_SAMPLES = 5;          // Jumlah sampel yang ingin dicatat

void setup() {
  Serial.begin(115200);
  delay(2000);

  if (!flash.begin()) {
    Serial.println("Gagal mendeteksi Flash Memory!");
    while (1);
  }

  Serial.println("=== MULAI DATA LOGGING ===");
  
  // 2. Erase Sektor sebelum menulis data baru
  Serial.println("Menghapus sektor memori...");
  flash.eraseSector(START_ADDRESS);

  uint32_t currentAddress = START_ADDRESS;

  // 3. PROSES PENULISAN (LOGGING)
  for (int i = 1; i <= TOTAL_SAMPLES; i++) {
    DataLog dataInput;
    
    // Ambil data sensor
    dataInput.timestamp = millis();
    dataInput.adcValue = analogRead(A0); 
    dataInput.voltage = (dataInput.adcValue / 1023.0) * 5.0;

    // Simpan struct ke dalam memori
    if (flash.writeAnything(currentAddress, dataInput)) {
      Serial.print("[WRITE] Sampel #"); Serial.print(i);
      Serial.print(" tersimpan di Alamat: 0x"); Serial.println(currentAddress, HEX);
    } else {
      Serial.println("[ERROR] Gagal menyimpan data.");
    }

    // Geser alamat memori sejauh ukuran struct (dalam bytes)
    currentAddress += sizeof(DataLog);

    delay(1000); // Jeda 1 detik antar pencatatan
  }

  Serial.println("\n=== BACA KEMBALI DATA DARI MEMORI ===");
  
  // 4. PROSES PEMBACAAN (READING)
  currentAddress = START_ADDRESS; // Reset alamat ke posisi awal

  for (int i = 1; i <= TOTAL_SAMPLES; i++) {
    DataLog dataOutput;

    // Baca struct dari memori
    if (flash.readAnything(currentAddress, dataOutput)) {
      Serial.print("Data #"); Serial.print(i);
      Serial.print(" | Time: "); Serial.print(dataOutput.timestamp);
      Serial.print(" ms | ADC: "); Serial.print(dataOutput.adcValue);
      Serial.print(" | Tegangan: "); Serial.print(dataOutput.voltage, 2);
      Serial.println(" V");
    }

    // Geser alamat memori sejauh ukuran struct
    currentAddress += sizeof(DataLog);
  }
}

void loop() {
  // Kosong
}