#include "Strategijos.h"
#include <algorithm>

void skirstyti1Vector(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& kietiakiai) {
    for (const auto& s : studentai) {
        if (s.getRezVid() < 5.0) vargsai.push_back(s);
        else kietiakiai.push_back(s);
    }
}

void skirstyti2Vector(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& kietiakiai) {
    vargsai.reserve(studentai.size() / 2);
    auto it = std::remove_if(studentai.begin(), studentai.end(), [](const Studentas& s) {
        return s.getRezVid() < 5.0;
    });
    vargsai.assign(std::make_move_iterator(studentai.begin()), std::make_move_iterator(it));
    kietiakiai.assign(std::make_move_iterator(it), std::make_move_iterator(studentai.end()));
    studentai.erase(it, studentai.end());
}

void skirstyti3Vector(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& kietiakiai) {
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) {
        return s.getRezVid() < 5.0;
    });
    vargsai.reserve(std::distance(studentai.begin(), it));
    kietiakiai.reserve(std::distance(it, studentai.end()));
    vargsai.assign(std::make_move_iterator(studentai.begin()), std::make_move_iterator(it));
    kietiakiai.assign(std::make_move_iterator(it), std::make_move_iterator(studentai.end()));
    studentai.clear();
}
