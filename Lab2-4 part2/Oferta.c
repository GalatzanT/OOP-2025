#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Oferta.h"

Oferta creeazaOferta(int id, const char* tip, int suprafata, const char* adresa, int pret) {
    Oferta of;
    of.id = id;
    of.suprafata = suprafata;
    of.pret = pret;

    // Handle NULL strings safely
    const char* empty = "";
    if (tip == NULL) tip = empty;
    if (adresa == NULL) adresa = empty;

    size_t tipSize = strlen(tip) + 1;
    of.tip = malloc(tipSize);
    if (of.tip) {
        strcpy_s(of.tip, tipSize, tip);
    }

    size_t adresaSize = strlen(adresa) + 1;
    of.adresa = malloc(adresaSize);
    if (of.adresa) {
        strcpy_s(of.adresa, adresaSize, adresa);
    }

    return of;
}

void updateOferta(Oferta* of, const char* tip, int suprafata, const char* adresa, int pret) {
    if (of == NULL) return;

    // Handle NULL strings safely
    const char* empty = "";
    if (tip == NULL) tip = empty;
    if (adresa == NULL) adresa = empty;

    // Free existing memory
    free(of->tip);
    free(of->adresa);

    // Allocate new memory
    size_t tipSize = strlen(tip) + 1;
    of->tip = malloc(tipSize);
    if (of->tip) {
        strcpy_s(of->tip, tipSize, tip);
    }

    size_t adresaSize = strlen(adresa) + 1;
    of->adresa = malloc(adresaSize);
    if (of->adresa) {
        strcpy_s(of->adresa, adresaSize, adresa);
    }

    of->suprafata = suprafata;
    of->pret = pret;
}

Oferta copyOferta(Oferta* of) {
    if (of == NULL) {
        return creeazaOferta(-1, "", 0, "", 0);
    }
    return creeazaOferta(of->id, of->tip, of->suprafata, of->adresa, of->pret);
}

void destroyOferta(Oferta* of) {
    
        if (of == NULL) return;

        free(of->tip);
        of->tip = NULL;
        free(of->adresa);
        of->adresa = NULL;
        of->id = -1;
        of->suprafata = -1;
        of->pret = -1;
    
}

void testOferta() {
    Oferta of = creeazaOferta(1, "casa", 100, "strada", 1000);
    assert(of.id == 1);
    assert(strcmp(of.tip, "casa") == 0);
    assert(of.suprafata == 100);
    assert(strcmp(of.adresa, "strada") == 0);
    assert(of.pret == 1000);

    // Test creation with empty strings
    Oferta ofEmpty = creeazaOferta(2, "", 0, "", 0);
    assert(ofEmpty.id == 2);
    assert(strcmp(ofEmpty.tip, "") == 0);
    assert(ofEmpty.suprafata == 0);
    assert(strcmp(ofEmpty.adresa, "") == 0);
    assert(ofEmpty.pret == 0);
    destroyOferta(&ofEmpty);

    // Test creation with NULL strings (should handle gracefully)
    Oferta ofNull = creeazaOferta(3, NULL, 0, NULL, 0);
    assert(ofNull.id == 3);
    assert(strcmp(ofNull.tip, "") == 0);
    assert(strcmp(ofNull.adresa, "") == 0);
    destroyOferta(&ofNull);

    // Test update functionality
    updateOferta(&of, "apartament", 200, "strada2", 2000);
    assert(of.id == 1);
    assert(strcmp(of.tip, "apartament") == 0);
    assert(of.suprafata == 200);
    assert(strcmp(of.adresa, "strada2") == 0);
    assert(of.pret == 2000);

    // Test copy functionality
    Oferta copy = copyOferta(&of);
    assert(copy.id == of.id);
    assert(strcmp(copy.tip, of.tip) == 0);
    assert(copy.suprafata == of.suprafata);
    assert(strcmp(copy.adresa, of.adresa) == 0);
    assert(copy.pret == of.pret);

    // Verify deep copy
    strcpy_s(of.tip, strlen("modified") + 1, "modified");
    assert(strcmp(copy.tip, "apartament") == 0);  // Copy unchanged

    // Test destroy functionality
    destroyOferta(&of);
    assert(of.id == -1);
    assert(of.suprafata == -1);
    assert(of.pret == -1);
    assert(of.tip == NULL);
    assert(of.adresa == NULL);

    // Test copy of NULL (should handle gracefully)
    Oferta nullCopy = copyOferta(NULL);
    assert(nullCopy.id == -1);
    destroyOferta(&nullCopy);

    destroyOferta(&copy);

}