#include "Strategijos.h"
#include <algorithm>

void skirstyti1List(const std::list<Studentas>& studentai, std::list<Studentas>& vargsai, std::list<Studentas>& kietiakiai) {
    for (const auto& s : studentai) {
        if (s.getRezVid() < 5.0) vargsai.push_back(s);
        else kietiakiai.push_back(s);
    }
}

void skirstyti2List(std::list<Studentas>& studentai, std::list<Studentas>& vargsai, std::list<Studentas>& kietiakiai) {
    auto it = studentai.begin();
    while (it != studentai.end()) {
        if (it->getRezVid() < 5.0) {
            vargsai.push_back(std::move(*it));
            it = studentai.erase(it);
        } else {
            ++it;
        }
    }
    kietiakiai = std::move(studentai);
}

void skirstyti3List(std::list<Studentas>& studentai, std::list<Studentas>& vargsai, std::list<Studentas>& kietiakiai) {
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) {
        return s.getRezVid() < 5.0;
    });
    vargsai.splice(vargsai.end(), studentai, studentai.begin(), it);
    kietiakiai.splice(kietiakiai.end(), studentai);
}
