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
public:
	Service(Repo& medicamentRepo, MedicamentValidation& val) : repo{ medicamentRepo }, validator{ val } {};
	Service(const Service& ot) = delete;
	void addMedicament(int id, string denumire, double pret, string producator, string substantaActiva);
	void deleteMedicamt(int id);
	void updateMedicament(int id, string denumire, double pret, string producator, string substantaActiva);
	const MyVector<Medicament>& getAllMeds();
	Medicament findMedicamentById(int id);

	void filter_price(double pretMin, double pretMax);

	void sort_by_price();
	void sort_by_substanta_activa();
};

void testService();
