#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "service.h"
#include "repo.h"
#include "domain.h"
#include "list.h"

// Test functions for domain
void testCreeazaOferta() {
    oferta* o = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
    assert(strcmp(o->tip, "apartament") == 0);
    assert(o->suprafata == 75);
    assert(strcmp(o->adresa, "Strada Unirii 10") == 0);
    assert(o->pret == 120000.50);
    distruge(o);
}

void testValideazaOferta() {
    oferta* valid = CreeazaOferta(1, "casa", 150, "Bulevardul Independentei 5", 250000.0);
    oferta* invalid = CreeazaOferta(2, "", -10, "", -50000.0);
	oferta* invalid2 = CreeazaOferta(-2, "apartament", 100, "iris", 100000.0);
	oferta* invalid3 = CreeazaOferta(3, "apartament", -100, "strada", -100000.0);
	oferta* invalid4 = CreeazaOferta(4, "apartament", 100, "", -100000.0);
	oferta* invalid5 = CreeazaOferta(5, "apartament", 100, "strada", -100000.0);
    assert(valideaza(valid) == 1);
	assert(valideaza(invalid) == 0);
    assert(valideaza(invalid2) == 0);
    assert(valideaza(invalid3) == 0);
    assert(valideaza(invalid4) == 0);
    assert(valideaza(invalid5) == 0);
    distruge(valid);
    distruge(invalid);
    distruge(invalid2);
    distruge(invalid3);
    distruge(invalid4);
    distruge(invalid5);
}

void testgetId() {
	oferta* o = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
	assert(getId(o) == 1);
	distruge(o);
	assert(getId(NULL) == -1);
}
void testgetPret() {
	oferta* o = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
	assert(getPret(o) == 120000.50);
	distruge(o);

    assert(getPret(NULL) == -1);
}

void testsetId() {
	oferta* o = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
	setId(o, 2);
	assert(getId(o) == 2);
	distruge(o);
}

void testsetPret() {
	oferta* o = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
	setPret(o, 150000.50);
	assert(getPret(o) == 150000.50);
	distruge(o);
}

void testCopyOferta() {
	oferta* o = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
	oferta* copie = copyOferta(o);
	assert(strcmp(o->tip, copie->tip) == 0);
	assert(o->suprafata == copie->suprafata);
	assert(strcmp(o->adresa, copie->adresa) == 0);
	assert(o->pret == copie->pret);
	distruge(o);
	distruge(copie);
}

// Test functions for repository
void testCreeazaOferte() {
    Offer* lista = creeazaOferte();
    assert(lista != NULL);
    assert(lista->dimensiune == 0);
    assert(lista->capacitate == 2);
    distrugeOferte(lista);

    
}

void testAddEntitate() {
    Service list = createService();

    addEnt(&list, 1, "teren", 28, "paris1", 15);
    addEnt(&list, 2, "teren", 28, "paris2", 15);
    addEnt(&list, 3, "teren", 28, "paris3", 15);
    oferta* p = get(list.lista, 0);

    assert(1 == p->id);
    assert(15 == p->pret);

    assert(addEnt(&list, 4, "casa", 28, "paris1", 15) == 1);

    destroyAll(&list);
}

void testDeleteEntitate() {
    Service list = createService();

    addEnt(&list, 1, "teren", 100, "strada1", 1000);
    addEnt(&list, 2, "casa", 200, "strada2", 2000);
    addEnt(&list, 3, "apartament", 300, "strada3", 3000);
    assert(list.lista->dimensiune == 3);

    deleteEnt(&list, 1);
    assert(list.lista->dimensiune == 2);

    deleteEnt(&list, 2);
    assert(list.lista->dimensiune == 1);

    deleteEnt(&list, 3);
    assert(list.lista->dimensiune == 0);

    destroyAll(&list);
}

void testUpdateEntitate() {
    Service list = createService();

    addEnt(&list, 1, "teren", 100, "strada1", 1000);
    addEnt(&list, 2, "casa", 200, "strada2", 2000);
    assert(list.lista->dimensiune == 2);

    updateEnt(&list, 1, "apartament", 150, "strada4", 2500);
    oferta* p = get(list.lista, 0);
    assert(strcmp(p->tip, "apartament") == 0);
    assert(p->suprafata == 150);
    assert(strcmp(p->adresa, "strada4") == 0);
    assert(p->pret == 2500);

    destroyAll(&list);
}

// Test functions for service
void testFilterPret() {
    Service list = createService();

    addEnt(&list, 1, "teren", 28, "paris", 15);
    addEnt(&list, 2, "teren", 28, "paris", 160);
    addEnt(&list, 3, "teren", 28, "paris", 20);
    addEnt(&list, 4, "teren", 28, "paris", 140);
    addEnt(&list, 5, "teren", 28, "paris", 30);

    Offer* f1 = filterPret(&list, 100);

    assert(f1->dimensiune == 3);
	oferta* p = get(f1, 0);
    assert(p->pret == 15);
	p = get(f1, 1);
    assert(p->pret == 20);
	p = get(f1, 2);
    assert(p->pret == 30);

    distrugeOferte(f1);
    destroyAll(&list);
}

void testFilterTip() {
    Service list = createService();

    addEnt(&list, 1, "teren", 100, "strada1", 1000);
    addEnt(&list, 2, "casa", 200, "strada2", 2000);
    addEnt(&list, 3, "apartament", 300, "strada3", 3000);
    addEnt(&list, 4, "casa", 400, "strada4", 4000);
    addEnt(&list, 5, "teren", 500, "strada5", 5000);

    Offer* f1 = filterTip(&list, 'c');

    assert(f1->dimensiune == 2);
	oferta* p = get(f1, 0);
    assert(p->id == 2);
	p = get(f1, 1);
    assert(p->id == 4);

    distrugeOferte(f1);
    destroyAll(&list);
}

void testSortPret() {
    Service list = createService();

    addEnt(&list, 1, "teren", 100, "strada1", 3000);
    addEnt(&list, 2, "casa", 200, "strada2", 2000);
    addEnt(&list, 3, "apartament", 300, "strada3", 1000);
    addEnt(&list, 4, "teren", 400, "strada4", 4000);
    addEnt(&list, 5, "casa", 500, "strada5", 5000);

    sortPret(&list);

    assert(list.lista->dimensiune == 5);
	oferta* p = get(list.lista, 0);
    assert(p->pret == 1000);
	p = get(list.lista, 1);
    assert(p->pret == 2000);
	p = get(list.lista, 2);
    assert(p->pret == 3000);
	p = get(list.lista, 3);
    assert(p->pret == 4000);
	p = get(list.lista, 4);
    assert(p->pret == 5000);
    destroyAll(&list);
}

void testSortTip() {
    Service list = createService();

    addEnt(&list, 1, "teren", 100, "strada1", 3000);
    addEnt(&list, 2, "casa", 200, "strada2", 2000);
    addEnt(&list, 3, "apartament", 300, "strada3", 1000);
    addEnt(&list, 4, "teren", 400, "strada4", 4000);
    addEnt(&list, 5, "casa", 500, "strada5", 5000);

    sortTip(&list);

    assert(list.lista->dimensiune == 5);
	oferta* p = get(list.lista, 0);
    assert(strcmp(p->tip, "apartament") == 0);
	p = get(list.lista, 1);
    assert(strcmp(p->tip, "casa") == 0);
	p = get(list.lista, 2);
    assert(strcmp(p->tip, "casa") == 0);
	p = get(list.lista, 3);
    assert(strcmp(p->tip, "teren") == 0);
	p = get(list.lista, 4);
    assert(strcmp(p->tip, "teren") == 0);
    
    destroyAll(&list);
}

void testAddEnt() {
    Service list = createService();

    addEnt(&list, 1, "teren", 28, "paris1", 15);
    addEnt(&list, 2, "teren", 28, "paris2", 15);
    addEnt(&list, 3, "teren", 28, "paris3", 15);
    oferta* p = get(list.lista, 0);

    assert(1 == p->id);
    assert(15 == p->pret);

    assert(addEnt(&list, 4, "apartament", 28, "paris1", 15) == 1);
    assert(addEnt(&list, 4, "iris", 28, "paris1", 15) == 0);

    destroyAll(&list);
}

void testDeleteEnt() {
    Service list = createService();

    addEnt(&list, 1, "teren", 100, "strada1", 1000);
    addEnt(&list, 2, "casa", 200, "strada2", 2000);
    addEnt(&list, 3, "apartament", 300, "strada3", 3000);
    assert(list.lista->dimensiune == 3);

    deleteEnt(&list, 1);
    assert(list.lista->dimensiune == 2);

    deleteEnt(&list, 2);
    assert(list.lista->dimensiune == 1);

    deleteEnt(&list, 3);
    assert(list.lista->dimensiune == 0);

	assert(deleteEnt(&list, 4) == 0);

    destroyAll(&list);
}

void testUpdateEnt() {
    Service list = createService();

    addEnt(&list, 1, "teren", 100, "strada1", 1000);
    addEnt(&list, 2, "casa", 200, "strada2", 2000);
    assert(list.lista->dimensiune == 2);

    updateEnt(&list, 1, "apartament", 150, "strada4", 2500);
    oferta* p = get(list.lista, 0);
    assert(strcmp(p->tip, "apartament") == 0);
    assert(p->suprafata == 150);
    assert(strcmp(p->adresa, "strada4") == 0);
    assert(p->pret == 2500);

	assert(updateEnt(&list, 3, "apartament", 150, "strada4", 2500) == -1);
    
    destroyAll(&list);
}

void testcmpPret() {
	oferta* o1 = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
	oferta* o2 = CreeazaOferta(2, "apartament", 75, "Strada Unirii 10", 120000.50);
	assert(cmpPret(o1, o2) == 0);
	distruge(o1);
	distruge(o2);
}

void testcmpPretDesc() {
    oferta* o1 = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
    oferta* o2 = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
    assert(cmpPretDesc(o1, o2) == 0);
    oferta* o3 = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 130000.50);
    assert(cmpPretDesc(o1, o3) == 1);
    assert(cmpPretDesc(o3, o1) == -1);
	distruge(o1);
	distruge(o2);
	distruge(o3);
}

void testcmpTipDest() {
    oferta* o1 = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
    oferta* o2 = CreeazaOferta(1, "apartament", 75, "Strada Unirii 10", 120000.50);
    assert(cmpTipDest(o1, o2) == 0);
	distruge(o1);
	distruge(o2);
}

void testsortPretDesc() {
	Service list = createService();
	addEnt(&list, 1, "teren", 100, "strada1", 3000);
	addEnt(&list, 2, "casa", 200, "strada2", 2000);
	addEnt(&list, 3, "apartament", 300, "strada3", 1000);
	addEnt(&list, 4, "teren", 400, "strada4", 4000);
	addEnt(&list, 5, "casa", 500, "strada5", 5000);
	sortPretDesc(&list);
	assert(list.lista->dimensiune == 5);
	oferta* p = get(list.lista, 0);
	assert(p->pret == 5000);
	p = get(list.lista, 1);
	assert(p->pret == 4000);
	p = get(list.lista, 2);
	assert(p->pret == 3000);
	p = get(list.lista, 3);
	assert(p->pret == 2000);
	p = get(list.lista, 4);
	assert(p->pret == 1000);
	destroyAll(&list);

}

void testsortTipDest() {
	Service list = createService();
	addEnt(&list, 1, "teren", 100, "strada1", 3000);
	addEnt(&list, 2, "casa", 200, "strada2", 2000);
	addEnt(&list, 3, "apartament", 300, "strada3", 1000);
	addEnt(&list, 4, "teren", 400, "strada4", 4000);
	addEnt(&list, 5, "casa", 500, "strada5", 5000);
	sortTipDest(&list);
	assert(list.lista->dimensiune == 5);
	oferta* p = get(list.lista, 0);
	assert(strcmp(p->tip, "teren") == 0);
	p = get(list.lista, 1);
	assert(strcmp(p->tip, "teren") == 0);
	p = get(list.lista, 2);
	assert(strcmp(p->tip, "casa") == 0);
	p = get(list.lista, 3);
	assert(strcmp(p->tip, "casa") == 0);
	p = get(list.lista, 4);
	assert(strcmp(p->tip, "apartament") == 0);
	destroyAll(&list);
}

void run_all_tests() {
    testCreeazaOferta();
    testValideazaOferta();
	testgetId();
    testgetPret();
	testsetId();
	testsetPret();
	testCopyOferta();
    testCreeazaOferte();
    testAddEntitate();
    testDeleteEntitate();
    testUpdateEntitate();
    testFilterPret();
    testFilterTip();
    testSortPret();
    testSortTip();
    testAddEnt();
    testDeleteEnt();
    testUpdateEnt();
    testcmpPret();
    testcmpPretDesc();
    testcmpTipDest();
    testsortPretDesc();
	testsortTipDest();
	
    //noi
    testList();
	testUndoFiltratePret2();
    printf("All tests passed!\n");
}

