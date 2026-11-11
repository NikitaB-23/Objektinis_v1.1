#include "Studentas.h"
#include <algorithm>
#include <iomanip>
#include <cstdlib>

Studentas::Studentas() : egzaminas(0), vidurkis(0), mediana(0), rezVid(0), rezMed(0) {}

Studentas::Studentas(const std::string& v, const std::string& p, const std::vector<int>& paz, int egz)
    : vardas(v), pavarde(p), pazymiai(paz), egzaminas(egz) {
    skaiciuotiRezultatus();
}

Studentas::Studentas(const Studentas& kitas)
    : vardas(kitas.vardas), pavarde(kitas.pavarde), pazymiai(kitas.pazymiai),
      egzaminas(kitas.egzaminas), vidurkis(kitas.vidurkis), mediana(kitas.mediana),
      rezVid(kitas.rezVid), rezMed(kitas.rezMed) {}

Studentas::Studentas(Studentas&& kitas) noexcept
    : vardas(std::move(kitas.vardas)), pavarde(std::move(kitas.pavarde)),
      pazymiai(std::move(kitas.pazymiai)), egzaminas(kitas.egzaminas),
      vidurkis(kitas.vidurkis), mediana(kitas.mediana),
      rezVid(kitas.rezVid), rezMed(kitas.rezMed) {
    kitas.egzaminas = 0;
}

Studentas::~Studentas() {}

void Studentas::skaiciuotiRezultatus() {
    if (pazymiai.empty()) {
        vidurkis = 0; mediana = 0;
    } else {
        double suma = 0;
        for (int p : pazymiai) suma += p;
        vidurkis = suma / pazymiai.size();

        std::vector<int> temp = pazymiai;
        std::sort(temp.begin(), temp.end());
        int n = temp.size();
        if (n % 2 == 0) mediana = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
        else mediana = temp[n / 2];
    }
    rezVid = 0.4 * vidurkis + 0.6 * egzaminas;
    rezMed = 0.4 * mediana + 0.6 * egzaminas;
}

std::istream& operator>>(std::istream& is, Studentas& s) {
    std::vector<int> paz;
    int p;
    is >> s.vardas >> s.pavarde;
    while (is >> p && p > 0) paz.push_back(p);
    is >> s.egzaminas;
    s.setPazymiai(paz);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Studentas& s) {
    os << std::left << std::setw(15) << s.vardas << std::setw(20) << s.pavarde
       << std::right << std::setw(15) << std::fixed << std::setprecision(2) << s.rezVid;
    return os;
}

int randPaz() { return std::rand() % 10 + 1; }
