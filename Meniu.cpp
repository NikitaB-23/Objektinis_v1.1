#include "Meniu.h"
#include <iostream>
#include <iomanip>
#include <limits>

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
