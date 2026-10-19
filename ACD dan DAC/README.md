# Eksperimen Akuisisi Sinyal ADC & DAC - PlatformIO

Dokumentasi dan kode program untuk eksperimen pembacaan sinyal analog (**ADC**) serta konversi sinyal (**DAC**) menggunakan mikrokontroler Arduino Uno pada lingkungan pengembangan **PlatformIO IDE**.

---

## 📌 Deskripsi Proyek
Eksperimen ini bertujuan untuk mempelajari konsep dasar konversi sinyal analog ke digital dan sebaliknya. Sistem membaca nilai analog dari potensiometer, mengonversinya menjadi besaran tegangan fisik, serta memantau hasilnya secara *real-time* melalui Serial Monitor.

## 🛠️ Spesifikasi Hardware & Pinout

### Komponen Utama
* **Mikrokontroler:** Arduino Uno (ATmega328P)
* **Input Analog:** Potensiometer 10k Ohm
* **Koneksi:** Breadboard dan Kabel Jumper

### Skema Pengkabelan (Wiring ADC)

| Komponen | Pin Potensiometer | Pin Arduino Uno |
| :--- | :--- | :--- |
| **VCC** | Pin Sisi Kiri / Kanan | **5V** |
| **Output (Wiper)** | Pin Tengah | **A0** |
| **GND** | Pin Sisi Sisa | **GND** |

---

## 💻 Konfigurasi `platformio.ini`
*catatan*: kode program tertera di main.cpp
```ini
[env:uno]
platform = atmelavr
board = uno
framework = arduino
monitor_speed = 115200
