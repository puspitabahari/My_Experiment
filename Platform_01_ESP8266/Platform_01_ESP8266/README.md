# Schematic Design and PCB Footprint Development — KiCad

## Deskripsi

Proyek ini berfokus pada pembuatan **schematic rangkaian elektronik menggunakan KiCad** sebagai tahap awal perancangan PCB. Schematic mencakup koneksi antar-komponen, jalur komunikasi, catu daya, serta antarmuka input dan output.

Selain merancang schematic, proyek ini juga mencakup pembuatan footprint khusus untuk beberapa komponen yang akan digunakan pada tahap PCB layout.

## Komponen pada Schematic

Komponen dan antarmuka yang digunakan dalam rancangan meliputi:

- **WEMOS D1 Mini** — mikrokontroler utama.
- **LCD I2C** — antarmuka tampilan.
- **Level Converter** — penyesuaian level tegangan logika.
- **LoRa** — komunikasi nirkabel.
- **RTC (Real-Time Clock)** — pengelolaan waktu.
- **W25QXX** — memori flash.
- **Push Button** — input pengguna.
- **LED** — indikator status.
- **Power Supply** — penyedia tegangan untuk rangkaian.

## Pembuatan Footprint

Footprint dibuat menggunakan KiCad untuk menyesuaikan kebutuhan penempatan komponen pada PCB. Pengembangan footprint memperhatikan susunan pin, jarak antar-pin (*pitch*), dimensi komponen, dan kebutuhan pemasangan.

Daftar footprint yang dikembangkan:

1. **LCD I2C**  
   [Lihat Footprint LCD I2C](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/LCDI2C_Footprint.pretty/LCDI2C_Module.kicad_mod)

2. **Level Converter**  
   [Lihat Footprint Level Converter](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/Level%20converter.pretty/level_converter.kicad_mod)

3. **LoRa**  
   [Lihat Footprint LoRa](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/LoRa_Footprint.pretty/LoRa.kicad_mod)

4. **RTC DS3231**  
   [Lihat Footprint RTC](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/RTC_Footprint.pretty/RTC_DS3231_Module.kicad_mod)

5. **W25QXX**  
   [Lihat Footprint W25QXX](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/W25QXX_Footprint.pretty/Untitled.kicad_mod)

## Tahapan Pengerjaan

1. Membuat schematic dan menentukan komponen yang digunakan.
2. Menghubungkan pin berdasarkan fungsi dan kebutuhan komunikasi.
3. Menentukan jalur catu daya dan ground.
4. Membuat footprint khusus untuk komponen yang diperlukan.
5. Menyiapkan schematic dan footprint untuk tahap PCB layout.

## Tujuan

- Mendokumentasikan koneksi antar-komponen secara terstruktur.
- Mengembangkan footprint khusus sesuai kebutuhan desain.
- Mempersiapkan rancangan untuk proses PCB layout dan fabrikasi.

## Software

- [KiCad](https://www.kicad.org/) — perangkat lunak *Electronic Design Automation* (EDA).
