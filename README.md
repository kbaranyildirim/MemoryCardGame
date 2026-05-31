<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=auto&height=200&section=header&text=Memory%20Card%20Game&fontSize=70&animation=fadeIn" width="100%"/>

  <h1>🧠 Allegro5 ile Kart Eşleştirme Oyunu</h1>

  <p><b>Kocaeli Üniversitesi Yazılım Mühendisliği - Programlama II Dersi Dönem Projesi</b></p>

  <p>
    <img src="https://img.shields.io/badge/Language-C-blue.svg?style=for-the-badge&logo=c" alt="Language C">
    <img src="https://img.shields.io/badge/Framework-Allegro5-red.svg?style=for-the-badge" alt="Allegro5">
    <img src="https://img.shields.io/badge/Build-CMake-orange.svg?style=for-the-badge&logo=cmake" alt="CMake">
    <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20Linux-green.svg?style=for-the-badge" alt="Platform">
  </p>

  <h4>
    <a href="#-proje-hakkında">Proje Hakkında</a> •
    <a href="#-özellikler">Özellikler</a> •
    <a href="#-kullanılan-teknolojiler">Teknolojiler</a> •
    <a href="#-kurulum-ve-çalıştırma">Kurulum</a> •
    <a href="#-proje-yapısı">Proje Yapısı</a>
  </h4>
</div>

---

## 📝 Proje Hakkında

Bu proje, **Kocaeli Üniversitesi Yazılım Mühendisliği Bölümü Programlama II** dersi kapsamında geliştirilmiştir. Klasik mantık oyunlarından biri olan **Memory Card (Kart Eşleştirme)** oyununun, C programlama dili ve donanım hızlandırmalı **Allegro5** grafik kütüphanesi kullanılarak modern bir grafiksel kullanıcı arayüzüne (GUI) uyarlanmış halidir.

Projede bellek yönetimi, olay güdümlü programlama (event-driven programming), Fisher-Yates karıştırma algoritması ve dosya işlemleri (File I/O) aktif olarak kullanılmıştır.

---

## ✨ Özellikler

* 🎲 **Rastgele Dağıtım (RNG):** Kart çiftleri, her oyun başında **Fisher-Yates Shuffle** algoritması kullanılarak tamamen rastgele karıştırılır.
* ⏱️ **Dinamik Süre ve Hamle Takibi:** Oyun esnasında harcanan süre (saniye) ve toplam hamle sayısı anlık olarak ekranda güncellenir.
* 💾 **Kalıcı Skor Sistemi (File I/O):** Oyun kazanıldığında yapılan hamle sayısı `best_score.txt` dosyasındaki rekorla kıyaslanır ve en iyi skor kalıcı olarak kaydedilir.
* ⚡ **Gelişmiş Grafik ve Performans:** 60 FPS zamanlayıcı (timer) kontrolü ve ekran kartını yormayan akıllı çizim tetikleme (redraw flag) mimarisi.
* 🖱️ **Koordinat Dönüşümü:** Kullanıcının fare piksellerini, oyun matrisindeki satır ve sütun indekslerine kusursuzca dönüştüren matematiksel altyapı.

---

## 🛠️ Kullanılan Teknolojiler

<table align="center">
  <tr>
    <td align="center" width="150">
      <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg" alt="C" width="40" height="40" />
      <br /><b>C Dili</b>
    </td>
    <td align="center" width="150">
      <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cmake/cmake-original.svg" alt="CMake" width="40" height="40" />
      <br /><b>CMake Build</b>
    </td>
    <td align="center" width="150">
      <p align="center" style="font-size: 24px; margin: 0;">🕹️</p>
      <b>Allegro 5</b>
    </td>
    <td align="center" width="150">
      <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/github/github-original.svg" alt="Git" width="40" height="40" />
      <br /><b>Git / GitHub</b>
    </td>
  </tr>
</table>

---


## 🚀 Kurulum ve Çalıştırma

### Sistem Gereksinimleri
* C99 destekli bir C Derleyicisi (GCC, Clang veya MSVC)
* CMake (Minimum v3.10)
* **Allegro 5** kütüphanesi (ve `primitives`, `font`, `ttf` eklentileri)

### Derleme Adımları

Projenin kurulu olduğu dizinde terminali açarak aşağıdaki komutları sırasıyla çalıştırın:

```bash
# 1. Derleme klasörü oluşturun ve içine girin
mkdir build
cd build

# 2. CMake yapılandırmasını çalıştırın
cmake ..

# 3. Projeyi derleyin
cmake --build .
````

Kadir Baran Yıldırım -Kocaeli üniversitesi 
