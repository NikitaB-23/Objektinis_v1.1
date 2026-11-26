# Studentų apdorojimo programa (v1.2)

## Aprašymas
Ši programa skirta studentų duomenų apdorojimui ir spartos analizei. Ji nuskaito studentus iš failo (arba juos sugeneruoja), apskaičiuoja galutinį balą (0.4 × vidurkis + 0.6 × egzaminas), suskirsto studentus į dvi grupes (vargšiukus < 5.0 ir kietakius ≥ 5.0) ir išveda rezultatus į atskirus failus. Programoje realizuotos trys skirtingos skirstymo strategijos, leidžiančios palyginti jų spartą su `std::vector` ir `std::list` konteineriais. 

Nuo **v1.1** versijos programoje vietoj `struct` naudojama pilnavertė `class Studentas` su inkapsuliuotais duomenimis (private), getteriais, seteriais, konstruktoriais ir destruktoriumi. Nuo **v1.2** versijos klasė pilnai realizuoja **Rule of Three** taisyklę ir turi perdengtus įvesties/išvesties operatorius.

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

### v1.2
- **Rule of Three:** Realizuotas rankinis kopijavimo konstruktorius (`Studentas(const Studentas&)`), kopijavimo priskyrimo operatorius (`operator=`) su self-assignment apsauga ir destruktorius (`~Studentas()`).
- **I/O operatoriai:** Perdengti `operator>>` ir `operator<<`, leidžiantys patogiai skaityti ir rašyti studentų duomenis iš/į bet kokį srautą (`cin`, `cout`, failus).
- **Demonstracija:** Pridėtas naujas meniu punktas `8`, kuris žingsnis po žingsnio parodo Rule of Three ir I/O operatorių veikimą, taip pat statinius metodų iškvietimų skaitliukus.

## Programos struktūra
- `Studentas.h` / `Studentas.cpp` – studento klasė su pilnu Rule of Three (copy ctor, copy assignment, destruktorius) ir I/O operatoriais.
- `Strategijos.h` / `StrategijosVector.cpp` / `StrategijosList.cpp` – 3 skirstymo strategijos.
- `CMakeLists.txt` – instaliatorius.
- `main.cpp` – pagrindinis meniu.
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

# Studentų apdorojimo programa (v1.2)

Šioje versijoje pagrindinis dėmesys skirtas `class Studentas` tobulinimui, siekiant užtikrinti saugų resursų valdymą ir lankstų duomenų įvedimą/išvedimą. Realizuoti šie reikalavimai:

1. **Rule of Three taisyklė:** Kadangi klasė turi savo destruktorių, buvo rankiniu būdu realizuoti kopijavimo konstruktorius ir kopijavimo priskyrimo operatorius. Tai užtikrina, kad kopijuojant studento objektą, visi duomenys (įskaitant `std::vector` su pažymiais) būtų nukopijuoti saugiai, be dvigubo atminties atlaisvinimo klaidų.
2. **Perdengti įvesties/išvesties operatoriai:** Sukurti `operator>>` ir `operator<<`, kurie leidžia studento duomenis nuskaityti ir išvesti per bet kokį srautą. Tai reiškia, kad ta pati klasė gali būti naudojama tiek įvedant duomenis ranka per klaviatūrą (`std::cin`), tiek skaitant iš failo (`std::ifstream`), tiek išvedant į ekraną (`std::cout`) ar į failą (`std::ofstream`).
3. **Demonstracija ir statistika:** Pridėtas naujas meniu punktas (8) ir skaitliukai, kurie gyvai parodo, kaip dažnai ir kada yra kviečiami šie specialieji metodai programos veikimo metu.

### Demonstracijos veikimo principas

**Pasirinkus meniu punktą `3`,poto `4`:**
Vartotojui įvedus studentus (arba juos sugeneravus), pasirinkus šį punktą programa išrikiuoja studentus pagal pasirinktą kriterijų ir išveda juos į ekraną. Po lentele programa išveda trijų statinių skaitliukų reikšmes:
- `Copy ctor iskvietimu:` – kiek kartų buvo sukurtos studentų kopijos.
- `Copy assign iskvietimu:` – kiek kartų studentų duomenys buvo priskirti jau egzistuojantiems objektams.
- `Destructor iskvietimu:` – kiek studentų objektų jau buvo sunaikinti.
<img width="455" height="397" alt="Screenshot 2026-11-26 183650" src="https://github.com/user-attachments/assets/02c9e43b-5b40-4c6b-ae06-11efc63bf6bf" />
<img width="376" height="214" alt="Screenshot 2026-11-26 183701" src="https://github.com/user-attachments/assets/45dd22c6-6809-4ee4-9974-e350a175221f" />


**Pasirinkus meniu punktą `8`:**
Šis punktas skirtas tiesioginiam ir vaizdžiam Rule of Three bei I/O operatorių demonstravimui. Programa atlieka šiuos veiksmus iš eilės:
1. **Copy konstruktorius:** Sukuria studentą `a`, tada sukuria `b = a`. Parodo, kad `b` turi tuos pačius duomenis ir yra nepriklausoma atminties kopija (deep copy).
2. **Copy assignment:** Sukuria studentą `c`, tada atlieka `c = a`. Parodo, kad egzistuojantis objektas sėkmingai gauna naujus duomenis.
3. **Self-assignment:** Atlieka `c = c`. Parodo, kad programa suveikia saugiai ir nesugriauna savo pačių duomenų (dėka `if (this != &kitas)` apsaugos).
4. **I/O operatoriai:** Išveda studento duomenis naudodama perdengtą `operator<<`.
5. **Destruktorius:** Parodo skaitliukų reikšmes prieš ir po to, kai laikinas studento objektas išeina iš savo kodo bloko (`scope`). Tai aiškiai įrodo, kada ir kaip yra kviečiamas `~Studentas()`.
<img width="323" height="166" alt="Screenshot 2026-11-26 183929" src="https://github.com/user-attachments/assets/e7e5cf3e-bb26-4fb9-945d-1d0b4b85552c" />
<img width="516" height="425" alt="Screenshot 2026-11-26 183953" src="https://github.com/user-attachments/assets/f2387385-262c-4450-89fb-142f4a40e44b" />


####Įvesties ir išvesties operatoriai

**1. Įvesties operatorius (`operator>>`)**
Realizuotas `Studentas.cpp` faile. Jis leidžia nuskaityti studento duomenis iš bet kokio įvesties srauto (klaviatūros ar failo). Grąžindamas `std::istream&`, jis leidžia grandinėti skaitymą (`cin >> a >> b`).

```cpp
std::istream& operator>>(std::istream& is, Studentas& s) {
    std::vector<int> paz;
    int p;
    is >> s.vardas >> s.pavarde;
    while (is >> p && p > 0) paz.push_back(p);
    is >> s.egzaminas;
    s.setPazymiai(paz);
    return is;
}


## 1. Įdiegimo (Instaliavimo) instrukcija

Projektas naudoja CMake ir reikalauja C++17 kompiliatoriaus.

Sukompiliuoti ir paleisti programą Windows sistemoje galite šiomis komandomis:
```

## 1. Įdiegimo (Instaliavimo) instrukcija

Projektas naudoja CMake ir reikalauja C++17 kompiliatoriaus. 

### Paruošimas
1. Įsitikinkite, kad kompiuteryje yra įdiegtos šios programos:
   - **CMake** (3.16 arba naujesnė versija)
   - **C++ kompiliatorius** (pvz., MinGW per Code::Blocks, arba MSVC)
2. Atidarykite terminalą (Windows sistemoje – **Command Prompt (cmd)**  ir pereikite į savo projekto katalogą:
```cmd
cd Desktop\Objektinis\main
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
* **8 punktas (Rule of Three demonstracija):** Paleidžia žingsnis po žingsnio demonstraciją. Ji parodo, kaip veikia kopijavimo konstruktorius, priskyrimo operatorius, apsauga nuo savęs priskyrimo (self-assignment) ir kada yra iškviečiamas destruktorius. Taip pat ekrane išvedami statiniai metodų iškvietimų skaitliukai.
