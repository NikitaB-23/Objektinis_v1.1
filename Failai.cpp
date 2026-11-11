#include "Failai.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using std::cout;
using Clock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::duration<double>;

double generuotiFaila(const std::string& fn, int n) {
    auto start = Clock::now();
    std::ofstream out(fn);
    if (!out.is_open()) return 0.0;

    out << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n";
    std::string buffer;
    buffer.reserve(1024 * 1024);

    for (int i = 1; i <= n; ++i) {
        buffer += "Vardas" + std::to_string(i) + " Pavarde" + std::to_string(i);
        for (int j = 0; j < 5; ++j) buffer += " " + std::to_string(std::rand() % 10 + 1);
        buffer += " " + std::to_string(std::rand() % 10 + 1) + "\n";
        if (buffer.size() >= 1024 * 1024) {
            out << buffer;
            buffer.clear();
        }
    }
    if (!buffer.empty()) out << buffer;
    return Seconds(Clock::now() - start).count();
}

std::vector<Studentas> nuskaitytiIsFailo_vector(const std::string& fn) {
    std::vector<Studentas> studentai;
    std::ifstream in(fn);
    if (!in.is_open()) return studentai;
    studentai.reserve(10000000);
    std::string eilute;
    std::getline(in, eilute);
    while (std::getline(in, eilute)) {
        if (eilute.empty()) continue;
        std::istringstream ss(eilute);
        std::string v, p;
        if (ss >> v >> p) {
            std::vector<int> paz;
            int pazymys;
            while (ss >> pazymys) paz.push_back(pazymys);
            if (!paz.empty()) {
                int egz = paz.back();
                paz.pop_back();
                studentai.emplace_back(v, p, paz, egz);
            }
        }
    }
    return studentai;
}

std::list<Studentas> nuskaitytiIsFailo_list(const std::string& fn) {
    std::list<Studentas> studentai;
    std::ifstream in(fn);
    if (!in.is_open()) return studentai;
    std::string eilute;
    std::getline(in, eilute);
    while (std::getline(in, eilute)) {
        if (eilute.empty()) continue;
        std::istringstream ss(eilute);
        std::string v, p;
        if (ss >> v >> p) {
            std::vector<int> paz;
            int pazymys;
            while (ss >> pazymys) paz.push_back(pazymys);
            if (!paz.empty()) {
                int egz = paz.back();
                paz.pop_back();
                studentai.emplace_back(v, p, paz, egz);
            }
        }
    }
    return studentai;
}

void isvestiIFaila(const std::string& fn, std::vector<Studentas> studentai, int pas) {
    std::ofstream out(fn);
    if (!out.is_open()) return;
    std::sort(studentai.begin(), studentai.end(), [](const Studentas& a, const Studentas& b) {
        return a.getRezVid() < b.getRezVid();
    });
    out << std::left << std::setw(15) << "Vardas" << std::left << std::setw(20) << "Pavarde";
    out << std::right << std::setw(15) << "Galutinis";
    if (pas == 1) out << std::right << std::setw(15) << "Vidurkis";
    else if (pas == 2) out << std::right << std::setw(15) << "Mediana";
    out << "\n" << std::fixed << std::setprecision(2);
    for (const auto& s : studentai) {
        out << std::left << std::setw(15) << s.getVardas() << std::left << std::setw(20) << s.getPavarde();
        out << std::right << std::setw(15) << s.getRezVid();
        if (pas == 1) out << std::right << std::setw(15) << s.getVidurkis();
        else if (pas == 2) out << std::right << std::setw(15) << s.getMediana();
        out << "\n";
    }
}

void isvestiIFaila(const std::string& fn, std::list<Studentas> studentai, int pas) {
    std::ofstream out(fn);
    if (!out.is_open()) return;
    studentai.sort([](const Studentas& a, const Studentas& b) {
        return a.getRezVid() < b.getRezVid();
    });
    out << std::left << std::setw(15) << "Vardas" << std::left << std::setw(20) << "Pavarde";
    out << std::right << std::setw(15) << "Galutinis";
    if (pas == 1) out << std::right << std::setw(15) << "Vidurkis";
    else if (pas == 2) out << std::right << std::setw(15) << "Mediana";
    out << "\n" << std::fixed << std::setprecision(2);
    for (const auto& s : studentai) {
        out << std::left << std::setw(15) << s.getVardas() << std::left << std::setw(20) << s.getPavarde();
        out << std::right << std::setw(15) << s.getRezVid();
        if (pas == 1) out << std::right << std::setw(15) << s.getVidurkis();
        else if (pas == 2) out << std::right << std::setw(15) << s.getMediana();
        out << "\n";
    }
}
