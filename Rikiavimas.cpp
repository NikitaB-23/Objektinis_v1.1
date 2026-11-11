#include "Rikiavimas.h"
#include <algorithm>

void rikiuotiStudentus(std::vector<Studentas>& studentai, const std::string& kriterijus, Tvarka tvarka) {
    auto cmp = [kriterijus, tvarka](const Studentas& a, const Studentas& b) {
        if (kriterijus == "vardas")
            return tvarka == Tvarka::Didejimo ? a.getVardas() < b.getVardas() : a.getVardas() > b.getVardas();
        if (kriterijus == "pavarde")
            return tvarka == Tvarka::Didejimo ? a.getPavarde() < b.getPavarde() : a.getPavarde() > b.getPavarde();

        return tvarka == Tvarka::Didejimo ? a.getRezVid() < b.getRezVid() : a.getRezVid() > b.getRezVid();
    };
    std::sort(studentai.begin(), studentai.end(), cmp);
}

void rikiuotiStudentus(std::list<Studentas>& studentai, const std::string& kriterijus, Tvarka tvarka) {
    auto cmp = [kriterijus, tvarka](const Studentas& a, const Studentas& b) {
        if (kriterijus == "vardas")
            return tvarka == Tvarka::Didejimo ? a.getVardas() < b.getVardas() : a.getVardas() > b.getVardas();
        if (kriterijus == "pavarde")
            return tvarka == Tvarka::Didejimo ? a.getPavarde() < b.getPavarde() : a.getPavarde() > b.getPavarde();

        return tvarka == Tvarka::Didejimo ? a.getRezVid() < b.getRezVid() : a.getRezVid() > b.getRezVid();
    };
    studentai.sort(cmp);
}
