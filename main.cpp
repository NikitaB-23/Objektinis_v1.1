#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Studentas.h"
#include "Failai.h"
#include "Rikiavimas.h"
#include "Tyrimai.h"
#include "Meniu.h"

using namespace std;

int main() {
    srand(time(0));
    vector<Studentas> grupeVec;
    list<Studentas> grupeList;
    int pas;

    while (true) {
        cout << "\nMENIU:\n";
        cout << "1 - Ivesti studenta ranka (Vector)\n";
        cout << "2 - Ivesti studenta ranka (List)\n";
        cout << "3 - Generuoti studentu sarasa\n";
        cout << "4 - Rodyti rezultatus lenteleje\n";
        cout << "5 - Sugeneruoti 5 testinius failus\n";
        cout << "6 - Tyrimas su NAUJAI sugeneruotais failais\n";
        cout << "7 - Tyrimas su JAU TURIMAIS failais\n";
        cout << "0 - Baigti darba\n";
        cout << "Pasirinkite: ";

        if (!(cin >> pas)) { cin.clear(); cin.ignore(10000, '\n'); continue; }
        if (pas == 0) break;

        if (pas == 1) {
            char dar;
            do {
                Studentas s;
                ivestiStudenta(s);
                grupeVec.push_back(s);
                cout << "Studento atminties adresas: " << &grupeVec.back() << "\n";
                cout << "Ar dar viena? (t/n): "; cin >> dar;
            } while (dar == 't' || dar == 'T');
        }
        else if (pas == 2) {
            char dar;
            do {
                Studentas s;
                ivestiStudenta(s);
                grupeList.push_back(s);
                cout << "Studento atminties adresas: " << &grupeList.back() << "\n";
                cout << "Ar dar viena? (t/n): "; cin >> dar;
            } while (dar == 't' || dar == 'T');
        }
        else if (pas == 3) {
            int kiek; cout << "Kiek studentu? ";
            while (!(cin >> kiek) || kiek <= 0) { cin.clear(); cin.ignore(10000, '\n'); }
            for (int i = 0; i < kiek; i++) {
                string v = "Vardas" + to_string(i + 1);
                string p = "Pavarde" + to_string(i + 1);
                vector<int> paz;
                for (int j = 0; j < 5; j++) paz.push_back(randPaz());
                int egz = randPaz();
                grupeVec.emplace_back(v, p, paz, egz);
            }
            cout << "Sugeneruota " << kiek << " studentu.\n";
        }
        else if (pas == 4) {
            if (grupeVec.empty()) {
                cout << "Sarasas tuscias!\n";
            } else {
                int isv, r, tv;
                cout << "Rodyti: 1 - Vidurki, 2 - Mediana: ";
                while (!(cin >> isv) || (isv != 1 && isv != 2)) { cin.clear(); cin.ignore(10000, '\n'); }

                cout << "Rikiuoti pagal: 1 - Varda, 2 - Pavarde, 3 - Galutini bala: ";
                while (!(cin >> r) || r < 1 || r > 3) { cin.clear(); cin.ignore(10000, '\n'); }

                cout << "Tvarka: 1 - Didejimo, 2 - Mazejimo: ";
                while (!(cin >> tv) || (tv != 1 && tv != 2)) { cin.clear(); cin.ignore(10000, '\n'); }

                string krit = (r == 1) ? "vardas" : (r == 2 ? "pavarde" : "galutinis");
                Tvarka t = (tv == 1) ? Tvarka::Didejimo : Tvarka::Mazejimo;
                rikiuotiStudentus(grupeVec, krit, t);
                spausdintiRezultatus(grupeVec, isv);
            }
        }
        else if (pas == 5) {
            generuotiFaila("studentai1000.txt", 1000); generuotiFaila("studentai10000.txt", 10000);
            generuotiFaila("studentai100000.txt", 100000); generuotiFaila("studentai1000000.txt", 1000000); generuotiFaila("studentai10000000.txt", 10000000);
            cout << "Sugeneruota!\n";
        }
        else if (pas == 6) {
            paleistiTyrima(true);
        }
        else if (pas == 7) {
            paleistiTyrima(false);
        }
    }
    return 0;
}
