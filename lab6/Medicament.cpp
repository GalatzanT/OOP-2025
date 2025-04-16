#include "Medicament.h"
#include <assert.h>
#include <iostream>

string Medicament::getDenumire() const {
	return denumire;
}
double Medicament::getPret() const {
	return pret;
}
string Medicament::getProducator() const {
	return producator;
}
string Medicament::getSubstantaActiva() const {
	return substantaActiva;
}
void Medicament::setDenumire(string Denumire) {
	this->denumire = Denumire;
}
void Medicament::setPret(double Pret) {
	this->pret = Pret;
}
void Medicament::setProducator(string Producator) {
	this->producator = Producator;
}
void Medicament::setSubstantaActiva(string SubstantaActiva) {
	this->substantaActiva = SubstantaActiva;
}
bool Medicament::operator==(const Medicament& medicament) const {
	return this->denumire == medicament.denumire && this->pret == medicament.pret && this->producator == medicament.producator && this->substantaActiva == medicament.substantaActiva;
}
bool Medicament::operator!=(const Medicament& medicament) const {
	return !(*this == medicament);
}	
ostream& operator<<(ostream& os, const Medicament& medicament) {
	os <<"Id: "<< medicament.id <<" " << medicament.denumire << " Pret: " << medicament.pret << " Producator: " << medicament.producator << " Substanta activa: " << medicament.substantaActiva;
	return os;
}
int Medicament::getId() const {
	return id;
}
void Medicament::setId(int Id) {
	this->id = Id;
}	
Medicament::Medicament(int id, string denumire, double pret, string producator, string substantaActiva) {
	this->id = id;
	this->denumire = denumire;
	this->pret = pret;
	this->producator = producator;
	this->substantaActiva = substantaActiva;
}
Medicament::~Medicament() {

}


Medicament::Medicament() {
	this->id = 0;
	this->denumire = "";
	this->pret = 0;
	this->producator = "";
	this->substantaActiva = "";
}

void testMedicament() {

	Medicament medicament;
	assert(medicament.getId() == 0);
	assert(medicament.getDenumire() == "");
	assert(medicament.getPret() == 0);
	assert(medicament.getProducator() == "");
	assert(medicament.getSubstantaActiva() == "");
	medicament.setId(1);
	assert(medicament.getId() == 1);
	assert(std::cout << medicament << std::endl); // This line is for testing the output of the operator<< function
	Medicament medicament1(1,"Paracetamol", 10.5, "Farmaceutica", "Paracetamol");
	Medicament medicament2(2,"Ibuprofen", 15.0, "Farmaceutica", "Ibuprofen");
	Medicament medicament3(3,"Paracetamol", 10.5, "Farmaceutica", "Paracetamol");
	assert(medicament1.getDenumire() == "Paracetamol");
	assert(medicament1.getPret() == 10.5);
	assert(medicament1.getProducator() == "Farmaceutica");
	assert(medicament1.getSubstantaActiva() == "Paracetamol");
	assert(medicament1 == medicament3);
	assert(medicament1 != medicament2);
	assert(medicament1.getDenumire() == medicament3.getDenumire());
	assert(medicament1.getPret() == medicament3.getPret());
	assert(medicament1.getProducator() == medicament3.getProducator());
	assert(medicament1.getSubstantaActiva() == medicament3.getSubstantaActiva());
	assert(medicament1 == medicament3);
	assert(medicament1 != medicament2);
	assert(medicament1.getDenumire() == medicament3.getDenumire());
	assert(medicament1.getPret() == medicament3.getPret());
	assert(medicament1.getProducator() == medicament3.getProducator());
	assert(medicament1.getSubstantaActiva() == medicament3.getSubstantaActiva());
	medicament1.setDenumire("aspacardin");
	assert(medicament1.getDenumire() == "aspacardin");
	medicament1.setPret(20.5);
	assert(medicament1.getPret() == 20.5);
	medicament1.setProducator("farmaceutica");
	assert(medicament1.getProducator() == "farmaceutica");
	medicament1.setSubstantaActiva("aspirina");
	assert(medicament1.getSubstantaActiva() == "aspirina");
}