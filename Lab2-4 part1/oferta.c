#define _CRT_SECURE_NO_WARNINGS
#include <assert.h>
#include "oferta.h"

Oferta creeazaOferta(const char* tip, int suprafata, const char* adresa, int pret) {
	Oferta of;
	strcpy(of.tip, tip);
	of.suprafata = suprafata;
	strcpy(of.adresa, adresa);
	of.pret = pret;
	return of;
}

Oferta updateOferta(Oferta* of, const char* tip, int suprafata, const char* adresa, int pret) {
	strcpy(of->tip, tip);
	of->suprafata = suprafata;
	strcpy(of->adresa, adresa);
	of->pret = pret;
	return *of;
}

void destroyOferta(Oferta* of) {
	strcpy(of->tip, "");
	of->suprafata = -1;
	strcpy(of->adresa, "");
	of->pret = -1;
}

void testCreeazaUpdateDestroyOferta() {
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	assert(strcmp(of.tip, "casa") == 0);
	assert(of.suprafata == 100);
	assert(strcmp(of.adresa, "strada") == 0);
	assert(of.pret == 1000);

	Oferta of2 = updateOferta(&of, "apartament", 200, "strada2", 2000);
	assert(strcmp(of2.tip, "apartament") == 0);
	assert(of2.suprafata == 200);
	assert(strcmp(of2.adresa, "strada2") == 0);
	assert(of2.pret == 2000);

	destroyOferta(&of2);
	assert(strcmp(of2.tip, "") == 0);
	assert(of2.suprafata == -1);
	assert(strcmp(of2.adresa, "") == 0);
	assert(of2.pret == -1);
}
