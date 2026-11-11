#ifndef STRATEGIJOS_H_INCLUDED
#define STRATEGIJOS_H_INCLUDED

#include "Studentas.h"
#include <vector>
#include <list>

void skirstyti1Vector(const std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& kietiakiai);
void skirstyti1List(const std::list<Studentas>& studentai, std::list<Studentas>& vargsai, std::list<Studentas>& kietiakiai);

void skirstyti2Vector(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& kietiakiai);
void skirstyti2List(std::list<Studentas>& studentai, std::list<Studentas>& vargsai, std::list<Studentas>& kietiakiai);

void skirstyti3Vector(std::vector<Studentas>& studentai, std::vector<Studentas>& vargsai, std::vector<Studentas>& kietiakiai);
void skirstyti3List(std::list<Studentas>& studentai, std::list<Studentas>& vargsai, std::list<Studentas>& kietiakiai);

#endif
