#pragma once
#include "Repo.h"
#include "Validation.h"
#include <iostream>
#include <string>
#include <vector>
using std::vector;



class Service {
private:
	Repo& repo;
	MedicamentValidation& validator;
	vector<const Medicament*> reteta;
public:
	Service(Repo& medicamentRepo, MedicamentValidation& val) : repo{ medicamentRepo }, validator{ val } {};
	Service(const Service& ot) = delete;
	void addMedicament(int id, string denumire, double pret, string producator, string substantaActiva);
	void deleteMedicamt(int id);
	void updateMedicament(int id, string denumire, double pret, string producator, string substantaActiva);
	const vector<Medicament>& getAllMeds();
	Medicament findMedicamentById(int id);

	void filter_price(double pretMin, double pretMax);

	void sort_by_price();
	void sort_by_substanta_activa();

	void genereaza_reteta(int nrMed);
	
	void goleste_reteta();
	
	int get_reteta_nr_med(); 

	int adauga_med_reteta(string den);

	void salveaza_reteta_fisier(const string& numeFisier);

	vector<const Medicament*>& get_reteta_all();
};

void testService();

void test_reteta_service();