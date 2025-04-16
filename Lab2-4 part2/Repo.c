#define _CRT_SECURE_NO_WARNINGS
#include "Repo.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>



VectorDinamic* creazaVectorDinamic() {
	VectorDinamic* v = malloc(sizeof(VectorDinamic));
	v->elems = malloc(INIT_CAPACITY *sizeof(Elem));
	v->capacitate = INIT_CAPACITY;
	v->lg = 0;
	return v;
}


void resize(VectorDinamic* v) {
	int nCap = 2 * v->capacitate;
	Elem* nElems = malloc(nCap * sizeof(Elem));
	//copiez din vectorul existent
	int i;
	for (i = 0; i < v->lg; i++) {
		nElems[i] = v->elems[i];
	}
	//dealocam memoria ocupata de vector
	free(v->elems);
	v->elems = nElems;
	v->capacitate = nCap;

}


void add(VectorDinamic* v, Elem el) {
	if (v->lg == v->capacitate) {
		resize(v);
	}
	v->elems[v->lg] = el;
	v->lg++;
}

void distruge(VectorDinamic* v) {
	int i;
	for (i = 0; i < v->lg; i++) {
		if (v->elems[i].adresa != NULL) {
			free(v->elems[i].adresa);
			v->elems[i].adresa = NULL;
		}
		if (v->elems[i].tip != NULL) {
			free(v->elems[i].tip);
			v->elems[i].tip = NULL;
		}
	}
	free(v->elems);
	free(v);
	v->elems = NULL;
	v->lg = 0;
	v->capacitate = 0;
}
int getElemIndex(VectorDinamic* v, int id) {
	for (int i = 0; i < v->lg; i++) {
		if (v->elems[i].id == id) {
			return i; // Return?m indexul elementului g?sit
		}
	}
	return -1; // Nu am g?sit elementul
}

int stergeOferta(VectorDinamic* v, int id) {
	int index = getElemIndex(v, id);
	if (index == -1) {
		return -1; // Oferta nu exist?
	}

	// Folosim destroyOferta pentru a cur??a datele
	destroyOferta(&v->elems[index]);

	// Mut?m elementele r?mase pentru a evita golurile în vector
	for (int j = index; j < v->lg - 1; j++) {
		v->elems[j] = v->elems[j + 1];
	}

	v->lg--; // Reducem dimensiunea vectorului

	return 0; // Succes

}


void testDinamicList() {
	// Test creare vector
	VectorDinamic* v = creazaVectorDinamic();
	assert(v->lg == 0);
	assert(v->capacitate == INIT_CAPACITY);

	// Test distrugere vector gol
	distruge(v);
	assert(v->lg == 0);
	assert(v->capacitate == 0);
	assert(v->elems == NULL);

	// Creare vector nou pentru urm?toarele teste
	v = creazaVectorDinamic();

	// Test ad?ugare elemente
	Oferta of1 = creeazaOferta(1, "casa", 100, "strada1", 1000);
	Oferta of2 = creeazaOferta(2, "apartament", 200, "strada2", 2000);
	Oferta of3 = creeazaOferta(3, "vila", 300, "strada3", 3000);

	add(v, of1);
	assert(v->lg == 1);
	assert(getElemIndex(v, 1) != -1);

	add(v, of2);
	add(v, of3);
	assert(v->lg == 3);

	// Test accesare element existent ?i inexistent
	assert(getElemIndex(v, 2) != -1);
	assert(getElemIndex(v, 4) == -1); // Oferta cu id=4 nu exist?

	// Test redimensionare automat?
	for (int i = 4; i <= INIT_CAPACITY + 2; i++) {
		Oferta of = creeazaOferta(i, "bloc", 50, "stradaX", 500);
		add(v, of);
	}
	assert(v->lg == INIT_CAPACITY + 2);
	assert(v->capacitate >= INIT_CAPACITY + 2); // A trebuit s? se m?reasc? capacitatea

	// Test ?tergere ofert? existent?
	assert(stergeOferta(v, 2) == 0);
	assert(v->lg == INIT_CAPACITY + 1);
	assert(getElemIndex(v, 2) == -1); // Oferta 2 a fost ?tears?

	// Test ?tergere ofert? inexistent?
	assert(stergeOferta(v, 99) == -1);

	// Test ?tergere ultimul element
	int lastId = v->elems[v->lg - 1].id;
	assert(stergeOferta(v, lastId) == 0);
	assert(v->lg == INIT_CAPACITY);
	assert(getElemIndex(v, lastId) == -1);

	// Test ?tergere toate elementele
	while (v->lg > 0) {
		assert(stergeOferta(v, v->elems[0].id) == 0);
	}
	assert(v->lg == 0);

	// Test distrugere vector dup? ?tergerea tuturor elementelor
	distruge(v);
}
