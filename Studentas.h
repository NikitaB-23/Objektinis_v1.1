#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iostream>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> pazymiai;
    int egzaminas;

    double vidurkis;
    double mediana;
    double rezVid;
    double rezMed;

    void skaiciuotiRezultatus();

public:
    Studentas();
    Studentas(const std::string& v, const std::string& p, const std::vector<int>& paz, int egz);
    Studentas(const Studentas& kitas);
    Studentas(Studentas&& kitas) noexcept;
    ~Studentas();

    std::string getVardas() const { return vardas; }
    std::string getPavarde() const { return pavarde; }
    int getEgzaminas() const { return egzaminas; }
    double getRezVid() const { return rezVid; }
    double getRezMed() const { return rezMed; }
    double getVidurkis() const { return vidurkis; }
    double getMediana() const { return mediana; }
    const std::vector<int>& getPazymiai() const { return pazymiai; }

    void setVardas(const std::string& v) { vardas = v; }
    void setPavarde(const std::string& p) { pavarde = p; }
    void setPazymiai(const std::vector<int>& p) { pazymiai = p; skaiciuotiRezultatus(); }
    void setEgzaminas(int e) { egzaminas = e; skaiciuotiRezultatus(); }

    Studentas& operator=(const Studentas& kitas) = default;
    Studentas& operator=(Studentas&& kitas) = default;

    friend std::istream& operator>>(std::istream& is, Studentas& s);
    friend std::ostream& operator<<(std::ostream& os, const Studentas& s);

    bool operator<(const Studentas& kitas) const { return rezVid < kitas.rezVid; }
};

int randPaz();

typedef std::vector<Studentas> StudentuKon;
enum class Tvarka { Didejimo, Mazejimo };

#endif
