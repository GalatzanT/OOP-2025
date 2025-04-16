#include "Service.h"
#include "Validation.h"
#include<assert.h>
#include<algorithm>

const MyVector<Medicament>& Service::getAllMeds() {
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
    return repo.findById(id);
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

    for (size_t i = 0; i < all.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < all.size(); ++j) {
            if (all[j].getPret() < all[minIndex].getPret()) {
                minIndex = j;
            }
        }
        // Swap the elements
        if (minIndex != i) {
            std::swap(all[i], all[minIndex]);
        }
    }
}


void Service::sort_by_substanta_activa() {
    auto& all = repo.getAll();  // Get the reference to the vector of Medicaments

    bool swapped;
    for (size_t i = 0; i < all.size() - 1; ++i) {
        swapped = false;
        for (size_t j = 0; j < all.size() - i - 1; ++j) {
            if (all[j].getSubstantaActiva() > all[j + 1].getSubstantaActiva()) {
                // Swap the elements
                std::swap(all[j], all[j + 1]);
                swapped = true;
            }
        }
        // If no elements were swapped in the inner loop, the array is already sorted
        if (!swapped) break;
    }
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
