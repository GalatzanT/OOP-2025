#pragma once

#include "Medicament.h"
#include "DinamicVector.h"


class RepoException {
private:
	string message;
public:
	RepoException(string message) : message(message) {}
	string getMessage() const {
		return this->message;
	};
};

class Repo {
private:
	//vector<Medicament> medicamente;
	MyVector<Medicament> medicamente;
public:
	Repo() = default;
	Repo(const Repo& r) = delete;
	void add(const Medicament& medicament);
	void remove(int id);
	void update(int id, const Medicament& medicament);
	MyVector<Medicament>& getAll();
	Medicament findById(int id) const;

};

void testRepo();

