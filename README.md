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

<img width="460" height="470" alt="Screenshot 2026-11-12 125709" src="https://github.com/user-attachments/assets/89968149-8adf-4312-8ef7-512ad72c9f16" />
<img width="436" height="476" alt="Screenshot 2026-11-12 125718" src="https://github.com/user-attachments/assets/e489f2ca-811c-4602-ab00-cc65a4b2f708" />
<img width="450" height="466" alt="Screenshot 2026-11-11 213550" src="https://github.com/user-attachments/assets/82f7a68d-2895-4c44-bdcf-73268a5e8c7e" />
<img width="478" height="459" alt="Screenshot 2026-11-11 213619" src="https://github.com/user-attachments/assets/af2ea5d1-8ae6-42a3-8735-9b172286aa45" />



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

<img width="470" height="473" alt="Screenshot 2026-11-11 231204" src="https://github.com/user-attachments/assets/092d0ccc-c7c7-4dcb-880f-90daf957e312" />
<img width="454" height="470" alt="Screenshot 2026-11-11 231510" src="https://github.com/user-attachments/assets/e3adb5ce-7a9b-4fc9-89e1-46c3e7f3b77f" />
<img width="443" height="476" alt="Screenshot 2026-11-11 231735" src="https://github.com/user-attachments/assets/518d527f-7e54-49e0-8d82-7b35d621af0f" />
<img width="467" height="459" alt="Screenshot 2026-11-11 214216" src="https://github.com/user-attachments/assets/9d7acd30-ff16-4374-8579-16b6bdd2faa4" />
<img width="476" height="473" alt="Screenshot 2026-11-11 215112" src="https://github.com/user-attachments/assets/6c281bde-03f3-4c88-af21-9d0a50b936e9" />
<img width="453" height="468" alt="Screenshot 2026-11-11 215441" src="https://github.com/user-attachments/assets/6eb71dfe-5783-496b-ba39-7bb9a1c73b2c" />





### 3. Skirtingų dalijimo strategijų spartos palyginimas (Class versija)

Siekiant įrodyti, kuri strategija yra optimaliausia, buvo palyginti visų trijų strategijų dalijimo laikai naudojant `class` versiją su skirtingais optimizavimo flag'ais.

**Su -O1 flag'u:**
| Studentų skaičius | 1 strategija (kopijavimas) | 2 strategija (trynimas) | 3 strategija (optimizuota) |
| :--- | :--- | :--- | :--- |
| **100 000** | 0.028 s | 0.008 s | **0.007 s** |
| **1 000 000** | 0.593 s | 0.170 s | **0.144 s** |

**Su -O2 flag'u:**
| Studentų skaičius | 1 strategija (kopijavimas) | 2 strategija (trynimas) | 3 strategija (optimizuota) |
| :--- | :--- | :--- | :--- |
| **100 000** | 0.027 s | 0.008 s | **0.007 s** |
| **1 000 000** | 0.609 s | 0.190 s | **0.150 s** |

**Su -O3 flag'u:**
| Studentų skaičius | 1 strategija (kopijavimas) | 2 strategija (trynimas) | 3 strategija (optimizuota) |
| :--- | :--- | :--- | :--- |
| **100 000** | 0.030 s | 0.008 s | **0.006 s** |
| **1 000 000** | 0.637 s | 0.173 s | **0.139 s** |

**Išvados:** 
Nepaisant pasirinkto optimizavimo lygio (`-O1`, `-O2` ar `-O3`) ir studentų skaičiaus, **3 strategija** visais atvejais išlieka greičiausia. Tai patvirtina, kad `std::partition` ir `std::move` semantikos naudojimas yra pats efektyviausias būdas skirstyti studentus į dvi grupes. 1 strategija yra lėčiausia dėl dvigubo duomenų kopijavimo, o 2 strategija atsilieka dėl vektoriaus elementų trynimo (`erase`) sąnaudų.



## 1. Įdiegimo (Instaliavimo) instrukcija

Projektas naudoja CMake ir reikalauja C++17 kompiliatoriaus.

Sukompiliuoti ir paleisti programą Windows sistemoje galite šiomis komandomis:

```cmd
cd Desktop\Objektinis\main
set PATH=%PATH%;C:\Program Files\CodeBlocks\MinGW\bin
set PATH=%PATH%;C:\Program Files\CMake\bin
cmake -B build -G "MinGW Makefiles"
cmake --build build
build\programa.exe
```
## 2. Naudojimosi instrukcija

Paleidus programą, ekrane pasirodys pagrindinis meniu. Pagrindinės funkcijos:

* **Duomenų įvedimas (1 ir 2 punktai):** Galite rankiniu būdu įvesti vieną ar daugiau studentų. Programa paprašys vardo, pavardės, pažymių ir egzamino balo.
* **Studentų generavimas (3 punktas):** Programa automatiškai sugeneruos nurodytą skaičių studentų su atsitiktiniais pažymiais.
* **Rezultatų peržiūra (4 punktas):** Išrikiuoja įvestus studentus pagal pasirinktą kriterijų ir išveda lentelę į ekraną.
* **Failų generavimas (5 punktas):** Sugeneruoja penkis testavimo failus (studentai1000.txt, studentai10000.txt ir t.t.) spartos tyrimams.
* **Spartos tyrimai (6 ir 7 punktai):** 
  * **6** – sugeneruoja naujus failus ir iš karto atlieka tyrimą.
  * **7** – atlieka tyrimą su jau esamais failais.
  * Tyrimo metu pasirenkamas konteineris (1 - Vector, 2 - List), rikiavimo kriterijus ir rodymo būdas. Rezultatai išvedami į ekraną, o išskirstyti studentai išsaugomi naujuose .txt failuose.
