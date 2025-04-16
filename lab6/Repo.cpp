#include "Repo.h"
#include <assert.h>

 Medicament Repo::findById( int id) const {
	for (const auto& medicament :this->medicamente) {
		if (medicament.getId() == id) {
			return medicament;
		}
	}
	throw RepoException("Medicament not found");
}

 void Repo::add(const Medicament& medicament) {
     for (const auto& m : medicamente) {
         if (m.getId() == medicament.getId()) {
             throw RepoException("Medicament already exists");
         }
     }
     medicamente.push_back(medicament);
 }

void Repo::remove(int id) {
	for (size_t i = 0; i < medicamente.size(); i++) {
		if (medicamente[i].getId() == id) {
			medicamente.erase(medicamente.begin() + i);
			return; 
		}
	}
	throw RepoException("Medicament not found");

}

void Repo::update(int id, const Medicament& newMedicament) {
	for (auto& medicament : this->medicamente) {
		if (medicament.getId() == id) {
			medicament = newMedicament;
			return;
		}
	}
	throw RepoException("Medicament not found");
}

 vector<Medicament>& Repo::getAll()  {
	return this->medicamente;
}

#include "Repo.h"
#include <assert.h>
#include <iostream>

void testRepo() {
    Repo repo;

    Medicament med1(1, "Paracetamol", 10.5, "Painkiller","fa");
    Medicament med2(2, "Ibuprofen", 15.0, "Anti-inflammatory","b");
    Medicament med3(3, "Aspirin", 12.0, "Blood thinner","c");

    // 🔹 Testăm `add`
    repo.add(med1);
    repo.add(med2);
    repo.add(med3);
    assert(repo.getAll().size() == 3);

    // 🔹 Testăm că nu putem adăuga un medicament cu ID existent
    try {
        repo.add(med1);
    }
    catch (const RepoException& e) {
        assert(e.getMessage() == "Medicament already exists");
    }

    // 🔹 Testăm `findById` pentru un medicament existent
    Medicament found = repo.findById(2);
    assert(found.getDenumire() == "Ibuprofen");

    // 🔹 Testăm `findById` pentru un medicament inexistent
    try {
        repo.findById(99);
    }
    catch (const RepoException& e) {
        assert(e.getMessage() == "Medicament not found");
    }

    // 🔹 Testăm `remove` pentru un medicament existent
    repo.remove(1);
    assert(repo.getAll().size() == 2);

    // 🔹 Testăm `remove` pentru un medicament inexistent
    try {
        repo.remove(99);
    }
    catch (const RepoException& e) {
        assert(e.getMessage() == "Medicament not found");
    }

    // 🔹 Testăm `update` pentru un medicament existent
    Medicament medUpdated(2, "Ibuprofen", 20.0, "Updated description","a");
    repo.update(2, medUpdated);
    assert(repo.findById(2).getPret() == 20.0);
    assert(repo.findById(2).getProducator() == "Updated description");

    // 🔹 Testăm `update` pentru un medicament inexistent
    try {
        repo.update(99, medUpdated);
    }
    catch (const RepoException& e) {
        assert(e.getMessage() == "Medicament not found");
    }

    // 🔹 Testăm `getAll`
    vector<Medicament> all = repo.getAll();
    assert(all.size() == 2); // Med1 a fost șters


}
