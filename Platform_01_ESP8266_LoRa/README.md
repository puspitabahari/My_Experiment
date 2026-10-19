# Schematic Design and PCB Footprint Development — KiCad

## Deskripsi

Proyek ini berfokus pada perancangan schematic rangkaian elektronik menggunakan KiCad sebagai tahap awal pengembangan PCB. Platform ini merupakan pengembangan dari rancangan sebelumnya dengan menambahkan modul **LoRa untuk komunikasi nirkabel** dan menghilangkan penggunaan LCD I2C.

Schematic mencakup koneksi antar-komponen, jalur komunikasi, catu daya, serta antarmuka input dan output.

## Komponen pada Schematic

Komponen yang digunakan dalam rancangan meliputi:

- **WEMOS D1 Mini** — mikrokontroler utama.
- **LoRa** — komunikasi nirkabel.
- **Level Converter** — penyesuaian level tegangan logika.
- **RTC (Real-Time Clock)** — pengelolaan waktu.
- **W25QXX** — memori flash.
- **Push Button** — input pengguna.
- **LED** — indikator status.
- **Power Supply** — penyedia tegangan untuk rangkaian.

## Pembuatan Footprint

Footprint dikembangkan menggunakan KiCad untuk mendukung penempatan komponen pada desain PCB. Pembuatan footprint memperhatikan susunan pin, jarak antar-pin (*pitch*), dimensi komponen, dan kebutuhan pemasangan.

Daftar footprint yang dikembangkan:

1. **Level Converter**  
   [Lihat Footprint Level Converter](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/Level%20converter.pretty/level_converter.kicad_mod)

2. **LoRa**  
   [Lihat Footprint LoRa](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/LoRa_Footprint.pretty/LoRa.kicad_mod)

3. **RTC DS3231**  
   [Lihat Footprint RTC](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/RTC_Footprint.pretty/RTC_DS3231_Module.kicad_mod)

4. **W25QXX**  
   [Lihat Footprint W25QXX](https://github.com/puspitabahari/My_Experiment/blob/main/Percobaan%20membuat%20PCB/Freerouting/freerouting/W25QXX_Footprint.pretty/Untitled.kicad_mod)

## Tahapan Pengerjaan

1. Membuat schematic dan menentukan komponen yang digunakan.
2. Menghubungkan pin berdasarkan fungsi dan kebutuhan komunikasi.
3. Menentukan jalur catu daya dan ground.
4. Menambahkan modul LoRa pada rancangan dan menyesuaikan koneksinya.
5. Membuat serta menyesuaikan footprint untuk komponen yang digunakan.
6. Menyiapkan rancangan untuk tahap PCB layout dan fabrikasi.

## Tujuan

- Mengembangkan platform elektronik dengan dukungan komunikasi LoRa.
- Mendokumentasikan koneksi antar-komponen secara terstruktur.
- Mengembangkan footprint khusus sesuai kebutuhan desain.
- Mempersiapkan rancangan untuk proses PCB layout dan fabrikasi.

## Software

- [KiCad](https://www.kicad.org/) — perangkat lunak *Electronic Design Automation* (EDA).
