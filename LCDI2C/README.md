# Percobaan LCD I2C

## Deskripsi
Percobaan ini bertujuan untuk mengoperasikan **LCD 16x2 dengan modul I2C** menggunakan Arduino. LCD digunakan untuk menampilkan status LED dan jumlah tekanan tombol (*push button*).

## Komponen
- Arduino
- LCD 16x2 I2C
- Push button
- LED
- Kabel jumper

## Prinsip Kerja
Komunikasi LCD menggunakan protokol I2C melalui dua jalur utama:
- **SDA**: Jalur pengiriman data.
- **SCL**: Jalur sinkronisasi clock.

Alamat I2C LCD diperiksa menggunakan program I2C Scanner.

## Cara Kerja Program
1. LCD menampilkan status awal `TURN OFF THE LAMP`.
2. Ketika push button ditekan, status LED berubah antara ON dan OFF.
3. LCD menampilkan status LED pada baris pertama.
4. Baris kedua menampilkan jumlah tekanan tombol (*Press Count*).
5. Status LED dan jumlah tekanan juga ditampilkan melalui Serial Monitor.

## Library
- `Wire.h`
- `LiquidCrystal_I2C.h`
- `Arduino.h`

## Repository
[GitHub - My_Experiment/LCDI2C](https://github.com/puspitabahari/My_Experiment/blob/main/LCDI2C/LCDI2C.cpp)
