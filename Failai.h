#ifndef FAILAI_H_INCLUDED
#define FAILAI_H_INCLUDED

#include "Studentas.h"
#include <string>
#include <vector>
#include <list>

double generuotiFaila(const std::string& failoVardas, int n);
std::vector<Studentas> nuskaitytiIsFailo_vector(const std::string& failoVardas);
std::list<Studentas> nuskaitytiIsFailo_list(const std::string& failoVardas);

void isvestiIFaila(const std::string& failoVardas, std::vector<Studentas> studentai, int pasirinkimas);
void isvestiIFaila(const std::string& failoVardas, std::list<Studentas> studentai, int pasirinkimas);

#endif
