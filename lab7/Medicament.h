#pragma once
#include <string>
#include <iostream>
using std::string;
using std::ostream;

class Medicament {
private:
    int id;
    string denumire;
    double pret;
    string producator;
    string substantaActiva;

public:
    Medicament();
    Medicament(int id, string denumire, double pret, string producator, string substantaActiva);
    ~Medicament();
    Medicament(const Medicament& m) : id{ m.id }, denumire{ m.denumire }, pret{ m.pret }, producator{ m.producator }, substantaActiva{ m.substantaActiva } {
        std::cout << "--Copy constructor called--\n";
    };
    int getId() const;
    void setId(int id);
    string getDenumire() const;
    double getPret() const;
    string getProducator() const;
    string getSubstantaActiva() const;
    void setDenumire(string denumire);
    void setPret(double pret);
    void setProducator(string producator);
    void setSubstantaActiva(string substantaActiva);
    bool operator==(const Medicament& medicament) const;
    bool operator!=(const Medicament& medicament) const;
    friend ostream& operator<<(ostream& os, const Medicament& medicament);

    Medicament& operator=(const Medicament& m) {
        if (this == &m) {
            return *this; // Handle self-assignment
        }
        this->id = m.id;
        this->denumire = m.denumire;
        this->pret = m.pret;
        this->producator = m.producator;
        this->substantaActiva = m.substantaActiva;
        return *this;
    }
    
};


void testMedicament();