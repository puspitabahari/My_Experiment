# Schematic Design and PCB Footprint Development — KiCad

## Deskripsi
Proyek ini berfokus pada pembuatan **schematic rangkaian elektronik menggunakan KiCad** sebagai tahap awal perancangan PCB. Schematic mencakup koneksi antar-komponen, jalur komunikasi, catu daya, serta antarmuka input dan output.

Selain merancang schematic, proyek ini juga mencakup pembuatan beberapa footprint komponen yang akan digunakan pada tahap layout PCB.

## Komponen pada Schematic
Beberapa komponen dan antarmuka yang terdapat dalam rancangan meliputi:

- **WEMOS D1 Mini** sebagai mikrokontroler.
- **LCD I2C** sebagai antarmuka tampilan.
- **Level Converter** untuk penyesuaian level tegangan logika.
- **LoRa** untuk kebutuhan komunikasi nirkabel.
- **RTC (Real-Time Clock)** untuk pengelolaan waktu.
- **W25QXX** sebagai memori flash.
- **Push Button** sebagai input pengguna.
- **LED** sebagai indikator.
- **Power Supply** untuk menyediakan tegangan yang dibutuhkan rangkaian.

## Pembuatan Footprint
Footprint dibuat secara khusus menggunakan KiCad untuk mendukung penempatan komponen pada desain PCB berikutnya.

Footprint yang dikembangkan meliputi:

- LCD I2C
- Level Converter
- LoRa
- RTC
- W25QXX

Pembuatan footprint dilakukan dengan memperhatikan susunan pin, jarak antar-pin (*pitch*), dimensi komponen, dan kebutuhan pemasangan pada PCB.

## Tahapan Pengerjaan
1. Membuat schematic dan menentukan komponen yang digunakan.
2. Menghubungkan pin berdasarkan fungsi dan kebutuhan komunikasi.
3. Menentukan jalur catu daya dan ground.
4. Membuat footprint khusus untuk komponen yang diperlukan.
5. Menyiapkan schematic dan footprint untuk tahap layout PCB.

## Tujuan
- Mendokumentasikan hubungan antar-komponen secara terstruktur.
- Mengembangkan footprint khusus sesuai kebutuhan desain.
- Mempersiapkan rancangan untuk proses PCB layout dan fabrikasi.

## Software
- [KiCad](https://www.kicad.org/) — Electronic Design Automation (EDA).
