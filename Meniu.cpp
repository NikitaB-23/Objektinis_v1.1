#include "Meniu.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

void ivestiStudenta(Studentas& s) {
    string v, p;
    cout << "\nVardas: "; cin >> v;
    cout << "Pavarde: "; cin >> p;
    s.setVardas(v);
    s.setPavarde(p);
    int k, t;
    cout << "1-Ranka, 2-Generuoti: "; cin >> t;
    vector<int> paz;
    if (t == 2) {
        cout << "Kiek? "; cin >> k;
        for(int i=0; i<k; i++) paz.push_back(randPaz());
        s.setPazymiai(paz);
        s.setEgzaminas(randPaz());
    }
    else {
        int pazymys;
        cout << "Pazymiai (0-baigti):\n";
        while(cin >> pazymys && pazymys>0) paz.push_back(pazymys);
        s.setPazymiai(paz);
        cout << "Egz: "; cin >> k;
        s.setEgzaminas(k);
    }
}

void spausdintiRezultatus(const StudentuKon& g, int pas) {
    if (pas == 1) {
        cout << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << right << setw(15) << "Galutinis (Vid.)" << "\n";
        for (const auto& s : g)
            cout << left << setw(15) << s.getVardas() << setw(20) << s.getPavarde() << right << setw(15) << fixed << setprecision(2) << s.getRezVid() << "\n";
    }
    else {
        cout << left << setw(15) << "Vardas" << setw(20) << "Pavarde" << right << setw(15) << "Galutinis (Med.)" << "\n";
        for (const auto& s : g)
            cout << left << setw(15) << s.getVardas() << setw(20) << s.getPavarde() << right << setw(15) << fixed << setprecision(2) << s.getRezMed() << "\n";
    }
}

void demonstracija() {
    cout << "\n=== RULE OF THREE DEMONSTRACIJA ===\n";

    cout << "\n--- 1. Copy konstruktorius ---\n";
    Studentas a("Jonas", "Jonaitis", {5, 6, 7}, 8);
    cout << "Sukurtas a: " << a.getVardas() << " " << a.getPavarde() << " (rezVid=" << a.getRezVid() << ")\n";
    Studentas b = a;
    cout << "Nukopijuotas b = a: " << b.getVardas() << " " << b.getPavarde() << " (rezVid=" << b.getRezVid() << ")\n";
    cout << "Ar nepriklausomi? " << (&a != &b ? "Taip" : "Ne") << "\n";

    cout << "\n--- 2. Copy assignment ---\n";
    Studentas c("Petras", "Petraitis", {9, 10}, 10);
    cout << "Sukurtas c: " << c.getVardas() << " " << c.getPavarde() << " (rezVid=" << c.getRezVid() << ")\n";
    c = a;
    cout << "Po c = a: " << c.getVardas() << " " << c.getPavarde() << " (rezVid=" << c.getRezVid() << ")\n";

    cout << "\n--- 3. Self-assignment ---\n";
    c = c;
    cout << "Po c = c: " << c.getVardas() << " " << c.getPavarde() << " (rezVid=" << c.getRezVid() << ")\n";

    cout << "\n--- 4. operator>> ir operator<< ---\n";
    cout << "operator<< pavyzdys: " << a << "\n";

    cout << "\n--- 5. Destruktorius ---\n";
    cout << "Skaitliukai pries scope pabaiga:\n";
    cout << "  Copy ctor:   " << Studentas::copyCtorKiekis << "\n";
    cout << "  Copy assign: " << Studentas::copyAssignKiekis << "\n";
    cout << "  Destructor:  " << Studentas::destructorKiekis << "\n";

    {
        Studentas temp("Temp", "Tempauskas", {1, 2}, 3);
        cout << "Sukurtas temp scope viduje\n";
    }
    cout << "Po scope pabaigos:\n";
    cout << "  Copy ctor:   " << Studentas::copyCtorKiekis << "\n";
    cout << "  Copy assign: " << Studentas::copyAssignKiekis << "\n";
    cout << "  Destructor:  " << Studentas::destructorKiekis << "\n";

    cout << "\n=== DEMONSTRACIJA BAIGTA ===\n";
}
