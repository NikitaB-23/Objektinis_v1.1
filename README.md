# Studentų apdorojimo programa (v1.1)

## Aprašymas
Ši programa skirta studentų duomenų apdorojimui ir spartos analizei. Ji nuskaito studentus iš failo (arba juos sugeneruoja), apskaičiuoja galutinį balą (0.4 × vidurkis + 0.6 × egzaminas), suskirsto studentus į dvi grupes (vargšiukus < 5.0 ir kietakius ≥ 5.0) ir išveda rezultatus į atskirus failus. Programoje realizuotos trys skirtingos skirstymo strategijos, leidžiančios palyginti jų spartą su `std::vector` ir `std::list` konteineriais. 

Nuo **v1.1** versijos programoje vietoj `struct` naudojama pilnavertė `class Studentas` su inkapsuliuotais duomenimis (private), getteriais, seteriais, konstruktoriais ir destruktoriumi.

## Versijų istorija (Releases)

### v.pradinė
Pirmoji versija: rankinis studentų įvedimas su namų darbų ir egzamino pažymiais, galutinio balo skaičiavimas pagal vidurkį arba medianą, įvesties validacija ir galimybė generuoti pažymius atsitiktinai.

### v0.1
Pridėtas studentų duomenų nuskaitymas iš failo (kursiokai.txt), rezultatų rūšiavimas ir išvedimas lentelėje, lietuviškų simbolių palaikymas Windows sistemoje.

### v0.2
Pridėtas testinių failų generavimas (1k–10M įrašų), studentų skirstymas į dvi grupes, laiko matavimas su std::chrono ir kelių testų vidurkis, rūšiavimas pagal naudotojo pasirinkimą. Kodas išskaidytas į atskirus .h ir .cpp failus.

### v0.3
Pridėtas std::list konteinerio palaikymas, vector ir list spartos palyginimas, rankinio įvedimo metu išvedamas objekto atminties adresas.

### v1.0
Pridėtos trys skirstymo strategijos ir jų spartos palyginimas:
1. **1 strategija (kopijavimas):** studentai kopijuojami į du naujus konteinerius, pradinis lieka nepakitęs (neefektyvu atmintiai).
2. **2 strategija (trynimas):** vargšiukai perkeliami į naują konteinerį ir ištrinami iš pradinio naudojant erase().
3. **3 strategija (optimizuota):** naudojamas std::partition – elementai sukeičiami vietomis, nekopijuojant ir netrinant duomenų (greičiausia).

Pridėtas CMakeLists.txt instaliatorius, leidžiantis sukompiliuoti programą bet kokioje OS. Taip pat pridėtas bendras laiko matavimas, apimantis visus žingsnius (nuskaitymą, rūšiavimą, dalijimą ir išvedimą).

### v1.1
- **Pereita nuo `struct` prie `class`:** Studento duomenys (vardas, pavardė, pažymiai, egzaminas) dabar yra `private`. Sukurti getteriai ir seteriai. Realizuoti numatytasis, kopijavimo ir perkėlimo (move) konstruktoriai bei destruktorius.
- **2 strategijos pataisymas:** Realizuotas taisyklingas elementų trynimas naudojant `erase()`.
- **Optimizavimas:** Naudojant `std::move` semantiką, žymiai pagreitintas studentų perkėlimas tarp konteinerių 3 strategijoje.
- Atlikti Struct vs Class bei kompiliatoriaus optimizavimo flag'ų (-O1, -O2, -O3) spartos tyrimai su vector konteineriu.

## Programos struktūra
- `Strategijos.h` / `StrategijosVector.cpp` / `StrategijosList.cpp` – 3 skirstymo strategijos.
- `CMakeLists.txt` – instaliatorius.
- `main.cpp` – pagrindinis meniu.
- `Studentas.h` / `Studentas.cpp` – studento klasė (su enkapsuliacija), skaičiavimai, konstruktoriai/destruktorius.
- `Failai.h` / `Failai.cpp` – failų generavimas, nuskaitymas ir išvedimas.
- `Rikiavimas.h` / `Rikiavimas.cpp` – rūšiavimas.
- `Tyrimai.h` / `Tyrimai.cpp` – spartos matavimas su std::chrono.
- `Meniu.h` / `Meniu.cpp` – pagalbinės meniu funkcijos.


## Testavimo sistemos parametrai
- **Procesorius (CPU):** Intel Core i5-1135G7
- **Operatyvioji atmintis (RAM):** 16 GB DDR4
- **Kietasis diskas:** SSD 256GB NVMe
- **Operacinė sistema:** Windows 11
- **Kompiliatorius:** GNU GCC Compiler (Code::Blocks)

## Tyrimų rezultatai

### 1. Struct ir Class versijų spartos palyginimas (vector)

Lyginant abi programos versijas, buvo naudojamas `std::vector` konteineris, 3-oji (optimizuota) dalijimo strategija bei 100 000 ir 1 000 000 įrašų failai. Matuojamas bendras programos veikimo laikas.

| Implementacija | Studentų skaičius | Bendras apdorojimo laikas (s) |
| :--- | :--- | :--- |
| **Struct (v1.0)** | 100 000 | 0.494 s |
| **Class (v1.1)** | 100 000 | 0.459 s |
| **Struct (v1.0)** | 1 000 000 | 5.300 s |
| **Class (v1.1)** | 1 000 000 | 5.105 s |

**Išvados:** 
Palyginus abi versijas matome, kad `class` versija yra šiek tiek greitesnė už `struct`. Su 100 000 įrašų skirtumas nedidelis(tik 0.035 s.), tačiau su 1 000 000 įrašų `class` versija laimi aiškiau (5.105s prieš 5.300s). 

### 2. Kompiliatoriaus optimizavimo flag'ų įtaka (vector)

Siekiant ištirti kompiliatoriaus optimizavimo įtaką, abi programos versijos (`struct` ir `class`) buvo sukompiliuotos su skirtingais optimizavimo flag'ais (`-O1`, `-O2`, `-O3`). Buvo matuojamas `.exe` failo dydis bei programos veikimo laikas su 100 000 ir 1 000 000 įrašų failais.

| Implementacija | Optimizavimo flag'as | `.exe` failo dydis (KB) | 100 000 įrašų laikas (s) | 1 000 000 įrašų laikas (s) |
| :--- | :--- | :--- | :--- | :--- |
| **Struct** | `-O1` | 130 KB | 0.491 s | 5.300 s |
| **Struct** | `-O2` | 130 KB | 0.488 s | 14.880 s |
| **Struct** | `-O3` | 130 KB | 0.499 s | 14.934 s |
| **Class** | `-O1` | 124 KB | 0.500 s | 15.146 s |
| **Class** | `-O2` | 124 KB | 0.521 s | 15.614 s |
| **Class** | `-O3` | 124 KB | 0.492 s | 15.599 s |

**Išvados:** 
Su 100 000 įrašų visi flag'ai veikia beveik identiškai (~0.5s). Tačiau su 1 000 000 įrašų matome didelį šuolį: su `-O1` flag'u programa užtrunka ~5s, o su `-O2` ir `-O3` – net ~15s. 
Tuo tarpu `-O1` palieka efektyviai veikiančias C++ bibliotekos funkcijas (`std::sort`), kurios su dideliais duomenimis susitvarko geriau.
