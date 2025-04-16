#pragma once
#include<vector>
#include "Medicament.h"
using std::vector;

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
	vector<Medicament> medicamente;
public:
	Repo() = default;
	Repo(const Repo& r) = delete;
	void add(const Medicament& medicament);
	void remove(int id);
	void update(int id, const Medicament& medicament);
	vector<Medicament>& getAll();
	Medicament findById(int id) const;

};

void testRepo();
