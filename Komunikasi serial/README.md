
# Komunikasi Serial (Transmitter dan Receiver)

## Deskripsi

Komunikasi serial adalah metode pengiriman data secara berurutan, bit demi bit, melalui jalur transmisi. Pada percobaan ini, komunikasi serial dilakukan menggunakan dua Arduino Uno, yaitu **Transmitter (TX)** sebagai pengirim data dan **Receiver (RX)** sebagai penerima data.

Transmitter menggunakan push button untuk mengubah status LED dan menghitung jumlah penekanan tombol. Status LED dan jumlah penekanan dikirimkan ke Receiver melalui komunikasi serial. Receiver kemudian membaca data yang diterima dan menampilkannya melalui Serial Monitor.

Keberhasilan komunikasi bergantung pada konfigurasi komunikasi yang sesuai, termasuk penggunaan baud rate yang sama pada kedua perangkat.

## Tujuan

- Memahami prinsip komunikasi serial TX dan RX.
- Mengirim data dari Arduino Transmitter ke Arduino Receiver.
- Menggunakan push button untuk mengubah status LED.
- Menghitung jumlah penekanan push button.
- Mengirim status LED dan jumlah penekanan melalui komunikasi serial.
- Memahami penggunaan `SoftwareSerial` pada Arduino.

## Alat dan Komponen

| No. | Komponen | Jumlah |
| --- | --- | --- |
| 1 | Laptop | 1 |
| 2 | Kabel USB | 1 |
| 3 | Arduino Uno | 2 |
| 4 | Kabel jumper | Secukupnya |
| 5 | Breadboard | 1 |
| 6 | PlatformIO IDE | 1 |
| 7 | Resistor 220 ohm | 2 |
| 8 | Push button | 1 |
| 9 | LED | 1 |
| 10 | LCD I2C | 1 |

## Konfigurasi Pin

### Transmitter

| Komponen | Pin Arduino |
| --- | --- |
| Push button | D2 |
| LED | D8 |
| LCD I2C SDA | SDA |
| LCD I2C SCL | SCL |
| Serial TX | Pin TX perangkat |

### Receiver

| Komponen | Pin Arduino |
| --- | --- |
| SoftwareSerial RX | D10 |
| SoftwareSerial TX | D11 |

**Catatan:** Pada Receiver, `SoftwareSerial mySerial(10, 11)` berarti pin D10 digunakan sebagai RX dan pin D11 sebagai TX. Hubungkan TX Transmitter ke RX Receiver (D10), serta hubungkan GND kedua Arduino. Jika menggunakan pin RX/TX perangkat keras Arduino, perhatikan bahwa pemetaan pin berbeda dengan `SoftwareSerial`.

## Cara Kerja Sistem

1. Transmitter menginisialisasi push button, LED, LCD I2C, dan komunikasi serial dengan baud rate 9600.
2. Push button dibaca untuk mendeteksi penekanan tombol.
3. Ketika tombol ditekan, status LED berubah dari ON menjadi OFF atau sebaliknya.
4. Sistem menambahkan nilai penghitung setiap kali penekanan tombol terdeteksi.
5. LCD menampilkan status LED dan jumlah penekanan tombol.
6. Transmitter mengirimkan data dalam format `ledState,pressCount`.
7. Receiver membaca data yang masuk melalui pin RX D10 menggunakan `SoftwareSerial`.
8. Data yang diterima diteruskan ke Serial Monitor melalui komunikasi serial USB.

## Format Data

Data dikirim dalam format CSV sederhana:

```text
ledState,pressCount
```

Contoh data:

```text
1,1
0,2
1,3
0,4
```

Keterangan:
- `ledState`: status LED, dengan `1` berarti ON dan `0` berarti OFF.
- `pressCount`: jumlah penekanan push button yang telah terdeteksi.

## Konfigurasi Komunikasi Serial

| Parameter | Nilai |
| --- | --- |
| Baud rate | 9600 bps |
| Metode pengiriman | Serial |
| Perangkat pengirim | Arduino Uno Transmitter |
| Perangkat penerima | Arduino Uno Receiver |
| Format data | `ledState,pressCount` |

## Library yang Digunakan

- `Arduino.h`: fungsi dasar Arduino.
- `Wire.h`: komunikasi I2C.
- `LiquidCrystal_I2C.h`: pengoperasian LCD I2C.
- `SoftwareSerial.h`: komunikasi serial melalui pin digital.

## Hasil yang Diharapkan

- LED berubah status setiap kali push button ditekan.
- LCD menampilkan status LED dan jumlah penekanan tombol.
- Transmitter mengirimkan status LED dan jumlah penekanan ke Receiver.
- Receiver menerima karakter yang dikirim dan menampilkannya melalui Serial Monitor.

## Repository

Source code percobaan tersedia pada repository GitHub berikut:

[My_Experiment - Komunikasi Serial](https://github.com/puspitabahari/My_Experiment/tree/main/Komunikasi%20serial)
