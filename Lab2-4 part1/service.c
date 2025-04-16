#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "service.h"

int adaugaOferta(List* l, char* tip, int suprafata, char* adresa, int pret) {
	Oferta of = creeazaOferta(tip, suprafata, adresa, pret);
	int valid = valideazaOferta(of);
	if (valid == 0) {
		return -1;
	}
	add(l, of);
	return 0;
}

int stergeOferta(List* l, char* tip, int suprafata, char* adresa, int pret) {
	Oferta of = creeazaOferta(tip, suprafata, adresa, pret);
	int valid = valideazaOferta(of);
	if (valid == 0) {
		return -1;
	}
	int poz = find(l, of);
	if (poz == -1) {
		return -1;
	}
	del(l, poz);
	return 0;
}

int actualizeazaOferta(List* l, int poz, char* tip, int suprafata, char* adresa, int pret) {
	Oferta of = creeazaOferta(tip, suprafata, adresa, pret);
	int valid = valideazaOferta(of);
	if (valid == 0) {
		return -1;
	}
	setElem(l, poz, of);
	return 0;
}

void ordonareCres(List* l) {
	for (int i = 0; i < l->lungime - 1; i++) {
		for (int j = i + 1; j < l->lungime; j++) {
			if (getElem(l, i).pret > getElem(l, j).pret) {
				TElem aux = getElem(l, i);
				setElem(l, i, getElem(l, j));
				setElem(l, j, aux);
			}
		}
	}
}

void ordonareDesc(List* l) {
	for (int i = 0; i < l->lungime - 1; i++) {
		for (int j = i + 1; j < l->lungime; j++) {
			if (getElem(l, i).pret < getElem(l, j).pret) {
				TElem aux = getElem(l, i);
				setElem(l, i, getElem(l, j));
				setElem(l, j, aux);
			}
		}
	}
}

List filtrareTip(List* l, char* tip) {
	List rez = createEmpty();
	for (int i = 0; i < l->lungime; i++) {
		Oferta of = getElem(l, i);
		if (strcmp(of.tip, tip) == 0) {
			add(&rez, of);
		}
	}
	return rez;
}

void testService() {
	List l = createEmpty();
	assert(size(&l) == 0);
	adaugaOferta(&l, "casa", 100, "strada", 1000);
	assert(size(&l) == 1);
	adaugaOferta(&l, "apartament", 200, "strada2", 2000);
	assert(size(&l) == 2);
	stergeOferta(&l, "casa", 100, "strada", 1000);
	assert(size(&l) == 1);
	actualizeazaOferta(&l, 0, "apartament", 200, "strada2", 2000);
	assert(strcmp(getElem(&l, 0).tip, "apartament") == 0);
	assert(getElem(&l, 0).suprafata == 200);
	assert(strcmp(getElem(&l, 0).adresa, "strada2") == 0);
	assert(getElem(&l, 0).pret == 2000);
	ordonareCres(&l);
	assert(getElem(&l, 0).pret == 2000);
	ordonareDesc(&l);
	assert(getElem(&l, 0).pret == 2000);
	List filtrat = filtrareTip(&l, "apartament");
	assert(size(&filtrat) == 1);
	assert(strcmp(getElem(&filtrat, 0).tip, "apartament") == 0);
	assert(getElem(&filtrat, 0).suprafata == 200);
	assert(strcmp(getElem(&filtrat, 0).adresa, "strada2") == 0);
	assert(getElem(&filtrat, 0).pret == 2000);
	destroy(&l);
	destroy(&filtrat);
	///Test ordonareCres si ordonareDesc
	List l2 = createEmpty();		
	adaugaOferta(&l2, "casa", 100, "strada", 2500);
	adaugaOferta(&l2, "casa", 100, "strada", 1000);
	adaugaOferta(&l2, "apartament", 200, "strada2", 2000);
	adaugaOferta(&l2, "teren", 300, "strada3", 3000);
	ordonareCres(&l2);
	assert(getElem(&l2, 0).pret == 1000);
	assert(getElem(&l2, 1).pret == 2000);
	assert(getElem(&l2, 2).pret == 2500);
	ordonareDesc(&l2);
	assert(getElem(&l2, 0).pret == 3000);
	assert(getElem(&l2, 1).pret == 2500);
	assert(getElem(&l2, 2).pret == 2000);
	assert(adaugaOferta(&l2, "apartament", 200, "strada2", -20)==-1);
	assert(stergeOferta(&l2, "apartament", 200, "strada2", 2000) == 0);
	assert(stergeOferta(&l2, "apartament", 200, "strada1000", 2000) == -1);
	assert(stergeOferta(&l2, "apartament", -12, "strada2", 2000) == -1);
	assert(actualizeazaOferta(&l2, 0, "apartament", -200, "strada2", 2000) == -1);
}