#include "Service.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
int adaugaOferta(VectorDinamic* l, int id, char* tip, int suprafata, char* adresa, int pret) {
	//verificam ca id-ul nu apare in lista
	for (int i = 0; i < l->lg; i++) {
		if (l->elems[i].id == id) {
			printf("Oferta cu id-ul %d exista deja!\n", id);
			return -1;
		}
	}
	Oferta o = creeazaOferta(id, tip, suprafata, adresa, pret);
	if (valideazaOferta(o) == 0) {
		printf("Oferta nu este valida!\n");
		destroyOferta(&o);
		return -1;
	}
	add(l, o);
	printf("Oferta cu id-ul %d a fost adaugata!\n", id);
	return 0;


}

int stergeOfertaService(VectorDinamic* l, int id) {

	if (stergeOferta(l, id) == -1) {
		printf("Oferta cu id-ul %d nu exista!\n", id);
		return -1;
	}
	printf("Oferta cu id-ul %d a fost stearsa!\n", id);
	return 0;
}
int actualizeazaOferta(VectorDinamic* l, int id, char* tip, int suprafata, char* adresa, int pret) {
	int index = getElemIndex(l, id);
	if (index == -1) {
		printf("Oferta cu id-ul %d nu exista!\n", id);
		return -1;
	}

	// Actualizăm oferta
	updateOferta(&l->elems[index], tip, suprafata, adresa, pret);
	printf("Oferta cu id-ul %d a fost actualizata!\n", id);
	return 0;
}

// Comparare crescătoare după preț
int comparaPretCrescator(const void* a, const void* b) {
	Oferta* ofertaA = (Oferta*)a;
	Oferta* ofertaB = (Oferta*)b;
	if (ofertaA->pret < ofertaB->pret) return -1;
	else return 1;
}

// Comparare descrescătoare după preț
int comparaPretDescrescator(const void* a, const void* b) {
	Oferta* ofertaA = (Oferta*)a;
	Oferta* ofertaB = (Oferta*)b;
	if (ofertaA->pret > ofertaB->pret) return -1;
	else return 1;

}

// Comparare crescătoare după suprafață
int comparaSuprafataCrescator(const void* a, const void* b) {
	Oferta* ofertaA = (Oferta*)a;
	Oferta* ofertaB = (Oferta*)b;
	if (ofertaA->suprafata < ofertaB->suprafata) return -1;
	else return 1;
}

// Comparare descrescătoare după suprafață
int comparaSuprafataDescrescator(const void* a, const void* b) {
	Oferta* ofertaA = (Oferta*)a;
	Oferta* ofertaB = (Oferta*)b;
	if (ofertaA->suprafata > ofertaB->suprafata) return -1;
	else return 1;
}

void ordonare(VectorDinamic* l, int (*compara)(const void*, const void*)) {
	qsort(l->elems, l->lg, sizeof(Oferta), compara);
}










void testService() {
	VectorDinamic* v = creazaVectorDinamic();

	// Test adăugare ofertă validă
	assert(adaugaOferta(v, 1, "casa", 100, "strada1", 1000) == 0);
	assert(v->lg == 1);

	// Test adăugare ofertă cu ID duplicat
	assert(adaugaOferta(v, 1, "apartament", 200, "strada2", 2000) == -1);

	// Test adăugare ofertă invalidă
	assert(adaugaOferta(v, 2, "casa", -50, "strada3", -500) == -1); // Suprafața și prețul sunt invalide

	// Test ștergere ofertă existentă
	assert(stergeOfertaService(v, 1) == 0);
	assert(v->lg == 0);

	// Test ștergere ofertă inexistentă
	assert(stergeOfertaService(v, 99) == -1);

	// Test actualizare ofertă existentă
	adaugaOferta(v, 2, "casa", 150, "strada3", 3000);
	assert(actualizeazaOferta(v, 2, "casa", 50, "strada4", 1500) == 0);
	assert(v->elems[0].suprafata == 50);
	assert(v->elems[0].pret == 1500);

	// Test actualizare ofertă inexistentă
	assert(actualizeazaOferta(v, 99, "casa", 100, "strada5", 500) == -1);

	// Test ordonare crescător după preț
	adaugaOferta(v, 3, "apartament", 100, "strada6", 2500);
	adaugaOferta(v, 4, "casa", 200, "strada7", 500);
	ordonare(v, comparaPretCrescator);
	assert(v->elems[0].pret == 500);
	assert(v->elems[1].pret == 1500);
	assert(v->elems[2].pret == 2500);

	// Test ordonare descrescător după preț
	ordonare(v, comparaPretDescrescator);
	assert(v->elems[0].pret == 2500);
	assert(v->elems[1].pret == 1500);
	assert(v->elems[2].pret == 500);

	// Test ordonare crescător după suprafață
	ordonare(v, comparaSuprafataCrescator);
	assert(v->elems[0].suprafata == 50);
	assert(v->elems[1].suprafata == 100);
	assert(v->elems[2].suprafata == 200);

	

	ordonare(v, comparaSuprafataDescrescator);
	assert(v->elems[0].suprafata == 200);
	assert(v->elems[1].suprafata == 100);
	assert(v->elems[2].suprafata == 50);

	// Test cu vectorul gol
	VectorDinamic* vGol = creazaVectorDinamic();
	assert(stergeOfertaService(vGol, 1) == -1); // Ștergere dintr-un vector gol
	assert(actualizeazaOferta(vGol, 1, "casa", 100, "strada1", 1000) == -1); // Actualizare într-un vector gol
	distruge(vGol); // Distruge vectorul gol

	// Test distrugere vector dinamic
	distruge(v); // Se curăță resursele după testare
}

