#include "Service.h"
#include "Validation.h"
#include<assert.h>
#include<algorithm>
#include<random>
#include <fstream>  
#include <iostream> 


const vector<Medicament>& Service::getAllMeds() {
    return this->repo.getAll();

}

void Service::addMedicament(int id, string denumire, double pret, string producator, string substantaActiva) {
    Medicament m{ id, denumire, pret, producator, substantaActiva };
    validator.validate(m);
    repo.add(m);
};

void Service::deleteMedicamt(int id) {
    repo.remove(id);
}

void Service::updateMedicament(int id, string denumire, double pret, string producator, string substantaActiva) {
    Medicament m{ id, denumire, pret, producator, substantaActiva };
    validator.validate(m);
    repo.update(id, m);
}

Medicament Service::findMedicamentById(int id) {
    Medicament m = repo.findById(id);
    return m;
}

void Service::filter_price(double pretMin, double pretMax) {
    vector<int> idsToDelete; // Store IDs to be deleted

    // Collect IDs of the items to be deleted
    for (const auto& medicament : repo.getAll()) {
        if (medicament.getPret() < pretMin || medicament.getPret() > pretMax) {
            idsToDelete.push_back(medicament.getId());
        }
    }

    // Delete items by ID after filtering
    for (int id : idsToDelete) {
        deleteMedicamt(id);
    }
}
void Service::sort_by_price() {
    auto& all = repo.getAll();  // Get the reference to the vector of Medicaments
    sort(all.begin(), all.end(), [](const Medicament& m1, const Medicament& m2) {
        return m1.getPret() < m2.getPret();  // Sort by price
        });
}

void Service::sort_by_substanta_activa() {
    auto& all = repo.getAll();  // Get the reference to the vector of Medicaments
    sort(all.begin(), all.end(), [](const Medicament& m1, const Medicament& m2) {
        return m1.getSubstantaActiva() < m2.getSubstantaActiva();  // Sort by active substance
        });
}
void testService() {
    Repo repo;
    MedicamentValidation validator;
    Service srv{ repo, validator };

    // Test addMedicament
    assert(srv.getAllMeds().size() == 0);
    srv.addMedicament(1, "Paracetamol", 10.5, "Farmaceutica", "Paracetamol");
    srv.addMedicament(2, "Ibuprofen", 20, "Farmaceutica", "Ibuprofen");
    assert(repo.getAll().size() == 2);

    // Test findMedicamentById
    Medicament m = srv.findMedicamentById(1);
    assert(m.getDenumire() == "Paracetamol");

    // Test updateMedicament
    srv.updateMedicament(1, "Paracetamol", 15, "AltProd", "Paracetamol");
    Medicament updated = repo.findById(1);
    assert(updated.getPret() == 15);
    assert(updated.getProducator() == "AltProd");

    // Test sort_by_substanta_activa
    srv.sort_by_substanta_activa();
    auto allAfterSortBySubst = repo.getAll();
    assert(allAfterSortBySubst[0].getSubstantaActiva() <= allAfterSortBySubst[1].getSubstantaActiva());

    // Test sort_by_price
    srv.sort_by_price();
    auto allAfterSortByPrice = repo.getAll();
    assert(allAfterSortByPrice[0].getPret() <= allAfterSortByPrice[1].getPret());

    // Test filter_price - Should remove Ibuprofen, as it is outside the range [10, 15]
    srv.filter_price(10, 15);
    auto allAfterFilter = repo.getAll();
    assert(allAfterFilter.size() == 1);  // Only Paracetamol should remain
    assert(allAfterFilter[0].getDenumire() == "Paracetamol");

    // Test delete
    srv.deleteMedicamt(1);
    assert(repo.getAll().empty());  // Repo should be empty after deletion

}


void Service::genereaza_reteta(int nrMed) {
    const auto& medicamente = repo.getAll();

    if (medicamente.empty()) {
        throw RepoException("Nu exista medicamente disponibile pentru generare.");
    }

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, static_cast<int>(medicamente.size() - 1));

    /*for (int i = 0; i < nrMed; ++i) {
      reteta.push_back(&medicamente[dist(mt)]);  
    }*/
    std::generate_n(std::back_inserter(reteta), nrMed, [&]() {
        return &medicamente[dist(mt)];
        });
}

int Service::get_reteta_nr_med() {
    return static_cast<int>(reteta.size());
}
vector<const Medicament*>& Service::get_reteta_all() {
    return this->reteta;
}

void Service::goleste_reteta() {
    reteta.clear();
}

int Service::adauga_med_reteta(string den) {
    const auto& medsRepo = repo.getAll();
    auto itMed = std::find_if(medsRepo.begin(), medsRepo.end(), [den](const Medicament& m) {
        return den == m.getDenumire();
        });
    if (itMed != medsRepo.end()) {
        reteta.push_back(&(*itMed));
        return 1;
    }
    return 0;
}


void Service::salveaza_reteta_fisier(const string& numeFisier) {
    // Deschidem fișierul pentru scriere
    std::ofstream fisier(numeFisier);

    // Verificăm dacă fișierul s-a deschis corect
    if (!fisier.is_open()) {
        throw RepoException("nu s-a deschis fisierul");
    }

    // Scriem capul de tabel (header) pentru CSV
    fisier << "ID, Denumire, Pret, Producator, SubstantaActiva" << std::endl;

    // Scriem fiecare medicament din rețetă în fișier
    for (const auto* medicament : reteta) {
        fisier << medicament->getId() << ", "
            << medicament->getDenumire() << ", "
            << medicament->getPret() << ", "
            << medicament->getProducator() << ", "
            << medicament->getSubstantaActiva() << std::endl;
    }

    // Închidem fișierul
    fisier.close();

}

void test_reteta_service() {
    Repo p;
    MedicamentValidation mVal;
    Service s{ p,mVal };

    try {
        s.genereaza_reteta(100);

    }
    catch(RepoException e){
        assert(true);
    }


    s.addMedicament(1, "Paracetamol", 10.5, "Farmaceutica", "Paracetamol");
    s.addMedicament(2, "Ibuprofen", 20, "Farmaceutica", "Ibuprofen");
    s.genereaza_reteta(5);
    assert(s.get_reteta_nr_med() == 5);
    s.adauga_med_reteta("Paracetamol");
    
    assert(s.get_reteta_nr_med() == 6);

    vector<const Medicament*> vec = s.get_reteta_all();
    assert(vec.size() == 6);
    s.salveaza_reteta_fisier("teste.csv");
    std::ifstream in("teste.csv");
    assert(in.is_open());

    std::string line;
    std::getline(in, line); 
    assert(line == "ID, Denumire, Pret, Producator, SubstantaActiva");
    in.close();

    s.goleste_reteta();
    assert(s.get_reteta_nr_med() == 0);
    assert(s.adauga_med_reteta("Nimic")==0);

    try {
        s.salveaza_reteta_fisier("Z:/cale/invalida??/romania");
    }
    catch (RepoException e) {
        assert(true);
    }

}