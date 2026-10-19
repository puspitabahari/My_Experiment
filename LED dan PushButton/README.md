# LED dan Push Button

## Deskripsi
Percobaan ini bertujuan untuk mengendalikan LED menggunakan push button dengan Arduino. Setiap tombol ditekan, status LED akan berubah antara menyala dan mati, serta jumlah tekanan tombol dihitung dan ditampilkan melalui Serial Monitor.

## Komponen
- Arduino
- LED
- Push button
- Resistor
- Kabel jumper
- Breadboard

## Konfigurasi Pin

| Komponen | Pin Arduino |
|---|---|
| Push Button | Digital Pin 2 |
| LED | Digital Pin 8 |

Push button menggunakan konfigurasi `INPUT_PULLUP`, sehingga kondisi tombol bernilai `LOW` ketika ditekan.

## Cara Kerja
1. Arduino menginisialisasi pin tombol dan LED.
2. Push button dibaca menggunakan `digitalRead()`.
3. Debouncing diterapkan menggunakan `millis()` dengan interval 50 ms untuk mengurangi pembacaan tombol ganda.
4. Setiap tombol ditekan, status LED berubah (*toggle*).
5. Jumlah tekanan tombol bertambah dan informasi status LED ditampilkan pada Serial Monitor.
6. Tegangan output digital diukur ketika tombol dan LED berada dalam kondisi ON dan OFF.

## Hasil Percobaan
- LED dapat dinyalakan dan dimatikan menggunakan push button.
- Jumlah tekanan tombol ditampilkan melalui Serial Monitor.
- Pengukuran dilakukan untuk mengamati tegangan digital pada kondisi ON dan OFF.

## Repository
[GitHub - LED dan Push Button](https://github.com/puspitabahari/My_Experiment/blob/main/LED%20dan%20PushButton/LED%20and%20PushButton.cpp)
