#include "Tyrimai.h"
#include "Failai.h"
#include "Rikiavimas.h"
#include "Strategijos.h"
#include <iostream>
#include <iomanip>
#include <chrono>
#include <string>

using std::cin;
using std::cout;
using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<double>;

void testuotiStrategijasVector(const std::string& failoVardas, int rikiavimas, Tvarka tvarka, int isvedimas, int kartai) {
    cout << "\n=== [VECTOR] Failas " << failoVardas << " ===\n";
    double sumNus = 0, sumRus = 0, sumD1 = 0, sumD2 = 0, sumD3 = 0, sumIsvV = 0, sumIsvK = 0;
    std::string kriterijus = (rikiavimas == 1) ? "vardas" : (rikiavimas == 2 ? "pavarde" : "galutinis");

    for (int k = 0; k < kartai; ++k) {
        auto t1 = Clock::now();
        std::vector<Studentas> studentai = nuskaitytiIsFailo_vector(failoVardas);
        auto t2 = Clock::now(); sumNus += Seconds(t2 - t1).count();

        auto t3 = Clock::now();
        rikiuotiStudentus(studentai, kriterijus, tvarka);
        auto t4 = Clock::now(); sumRus += Seconds(t4 - t3).count();

        std::vector<Studentas> v1, k1;
        auto t5 = Clock::now();
        skirstyti1Vector(studentai, v1, k1);
        auto t6 = Clock::now(); sumD1 += Seconds(t6 - t5).count();

        std::vector<Studentas> studentai2 = nuskaitytiIsFailo_vector(failoVardas);
        std::vector<Studentas> v2, k2;
        auto t7 = Clock::now();
        skirstyti2Vector(studentai2, v2, k2);
        auto t8 = Clock::now(); sumD2 += Seconds(t8 - t7).count();

        std::vector<Studentas> studentai3 = nuskaitytiIsFailo_vector(failoVardas);
        std::vector<Studentas> v3, k3;
        auto t9 = Clock::now();
        skirstyti3Vector(studentai3, v3, k3);
        auto t10 = Clock::now(); sumD3 += Seconds(t10 - t9).count();

        rikiuotiStudentus(v3, kriterijus, tvarka);
        rikiuotiStudentus(k3, kriterijus, tvarka);

        auto t11 = Clock::now();
        isvestiIFaila("vargsai_v_" + failoVardas, v3, isvedimas);
        auto t12 = Clock::now(); sumIsvV += Seconds(t12 - t11).count();

        auto t13 = Clock::now();
        isvestiIFaila("kietiakiai_v_" + failoVardas, k3, isvedimas);
        auto t14 = Clock::now(); sumIsvK += Seconds(t14 - t13).count();
    }

    double vidNus = sumNus/kartai;
    double vidRus = sumRus/kartai;
    double vidD1 = sumD1/kartai;
    double vidD2 = sumD2/kartai;
    double vidD3 = sumD3/kartai;
    double vidIsvV = sumIsvV/kartai;
    double vidIsvK = sumIsvK/kartai;
    double bendraSuma = vidNus + vidRus + vidD3 + vidIsvV + vidIsvK;

    cout << std::fixed << std::setprecision(3);
    cout << "Nuskaitymas: " << vidNus << " s\n";
    cout << "Rusiavimas:  " << vidRus << " s\n";
    cout << "Dalijimas (1 str.): " << vidD1 << " s\n";
    cout << "Dalijimas (2 str.): " << vidD2 << " s\n";
    cout << "Dalijimas (3 str.): " << vidD3 << " s\n";
    cout << "Vargsai isvedimas: " << vidIsvV << " s\n";
    cout << "Kietiakiai isvedimas: " << vidIsvK << " s\n";
    cout << "-----------------------------------\n";
    cout << "BENDRAS LAIKAS: " << bendraSuma << " s\n";
}

void testuotiStrategijasList(const std::string& failoVardas, int rikiavimas, Tvarka tvarka, int isvedimas, int kartai) {
    cout << "\n=== [LIST] Failas " << failoVardas << " ===\n";
    double sumNus = 0, sumRus = 0, sumD1 = 0, sumD2 = 0, sumD3 = 0, sumIsvV = 0, sumIsvK = 0;
    std::string kriterijus = (rikiavimas == 1) ? "vardas" : (rikiavimas == 2 ? "pavarde" : "galutinis");

    for (int k = 0; k < kartai; ++k) {
        auto t1 = Clock::now();
        std::list<Studentas> studentai = nuskaitytiIsFailo_list(failoVardas);
        auto t2 = Clock::now(); sumNus += Seconds(t2 - t1).count();

        auto t3 = Clock::now();
        rikiuotiStudentus(studentai, kriterijus, tvarka);
        auto t4 = Clock::now(); sumRus += Seconds(t4 - t3).count();

        std::list<Studentas> v1, k1;
        auto t5 = Clock::now();
        skirstyti1List(studentai, v1, k1);
        auto t6 = Clock::now(); sumD1 += Seconds(t6 - t5).count();

        std::list<Studentas> studentai2 = nuskaitytiIsFailo_list(failoVardas);
        std::list<Studentas> v2, k2;
        auto t7 = Clock::now();
        skirstyti2List(studentai2, v2, k2);
        auto t8 = Clock::now(); sumD2 += Seconds(t8 - t7).count();

        std::list<Studentas> studentai3 = nuskaitytiIsFailo_list(failoVardas);
        std::list<Studentas> v3, k3;
        auto t9 = Clock::now();
        skirstyti3List(studentai3, v3, k3);
        auto t10 = Clock::now(); sumD3 += Seconds(t10 - t9).count();

        rikiuotiStudentus(v3, kriterijus, tvarka);
        rikiuotiStudentus(k3, kriterijus, tvarka);

        auto t11 = Clock::now();
        isvestiIFaila("vargsai_l_" + failoVardas, v3, isvedimas);
        auto t12 = Clock::now(); sumIsvV += Seconds(t12 - t11).count();

        auto t13 = Clock::now();
        isvestiIFaila("kietiakiai_l_" + failoVardas, k3, isvedimas);
        auto t14 = Clock::now(); sumIsvK += Seconds(t14 - t13).count();
    }

    double vidNus = sumNus/kartai;
    double vidRus = sumRus/kartai;
    double vidD1 = sumD1/kartai;
    double vidD2 = sumD2/kartai;
    double vidD3 = sumD3/kartai;
    double vidIsvV = sumIsvV/kartai;
    double vidIsvK = sumIsvK/kartai;
    double bendraSuma = vidNus + vidRus + vidD3 + vidIsvV + vidIsvK;

    cout << std::fixed << std::setprecision(3);
    cout << "Nuskaitymas: " << vidNus << " s\n";
    cout << "Rusiavimas:  " << vidRus << " s\n";
    cout << "Dalijimas (1 str.): " << vidD1 << " s\n";
    cout << "Dalijimas (2 str.): " << vidD2 << " s\n";
    cout << "Dalijimas (3 str.): " << vidD3 << " s\n";
    cout << "Vargsai isvedimas: " << vidIsvV << " s\n";
    cout << "Kietiakiai isvedimas: " << vidIsvK << " s\n";
    cout << "-----------------------------------\n";
    cout << "BENDRAS LAIKAS: " << bendraSuma << " s\n";
}

void paleistiTyrima(bool generuotiFailus) {
    int konteineris;
    cout << "\nKuri konteineri naudoti tyrimui?\n1 - Vector\n2 - List\nPasirinkimas: ";
    while (!(cin >> konteineris) || (konteineris != 1 && konteineris != 2)) {
        cin.clear(); cin.ignore(10000, '\n'); cout << "Klaida: ";
    }

    cout << "\n=== STRATEGIJU TYRIMAS ===\n";
    cout << "Rikiuoti pagal: 1 - Varda, 2 - Pavarde, 3 - Galutini bala: ";
    int rikiavimas;
    while (!(cin >> rikiavimas) || (rikiavimas < 1 || rikiavimas > 3)) {
        cin.clear(); cin.ignore(10000, '\n'); cout << "Klaida: ";
    }
    cout << "Kokia tvarka: 1 - Didejimo, 2 - Mazejimo: ";
    int tv;
    while (!(cin >> tv) || (tv != 1 && tv != 2)) {
        cin.clear(); cin.ignore(10000, '\n'); cout << "Klaida: ";
    }
    Tvarka tvarka = (tv == 1) ? Tvarka::Didejimo : Tvarka::Mazejimo;
    cout << "Rodyti: 1 - Vidurki, 2 - Mediana: ";
    int isvedimas;
    while (!(cin >> isvedimas) || (isvedimas != 1 && isvedimas != 2)) {
        cin.clear(); cin.ignore(10000, '\n'); cout << "Klaida: ";
    }

    if (generuotiFailus) {
        generuotiFaila("studentai1000.txt", 1000);
        generuotiFaila("studentai10000.txt", 10000);
        generuotiFaila("studentai100000.txt", 100000);
        generuotiFaila("studentai1000000.txt", 1000000);
        generuotiFaila("studentai10000000.txt", 10000000);

        if (konteineris == 1) {
            testuotiStrategijasVector("studentai1000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasVector("studentai10000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasVector("studentai100000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasVector("studentai1000000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasVector("studentai10000000.txt", rikiavimas, tvarka, isvedimas, 1);
        } else {
            testuotiStrategijasList("studentai1000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasList("studentai10000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasList("studentai100000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasList("studentai1000000.txt", rikiavimas, tvarka, isvedimas, 3);
            testuotiStrategijasList("studentai10000000.txt", rikiavimas, tvarka, isvedimas, 1);
        }
    } else {
        cout << "\nIveskite failo pavadinima: ";
        std::string failoVardas;
        cin >> failoVardas;

        if (konteineris == 1) {
            testuotiStrategijasVector(failoVardas, rikiavimas, tvarka, isvedimas, 3);
        } else {
            testuotiStrategijasList(failoVardas, rikiavimas, tvarka, isvedimas, 3);
        }
    }
}
