#define _CRT_SECURE_NO_WARNINGS
#include "repo.h"
#include "domain.h"
#include <stdlib.h>

void addEntitate(Offer* lista, ElemType p) {
    if (lista->dimensiune < lista->capacitate) {
        lista->oferte[lista->dimensiune] = p;
        lista->dimensiune += 1;
    }
    else {
        asiguraCapacitate(lista);
        addEntitate(lista, p);
    }
}

int deleteEntitate(Offer* lista, int id_cautat) {
    int i = 0;
    int ok = 1;
    while (i < lista->dimensiune) {
        oferta* p = get(lista, i);
        if (p->id == id_cautat) {
            distruge(p);
            for (int j = i; j < lista->dimensiune - 1; j++)
                lista->oferte[j] = lista->oferte[j + 1];
            lista->dimensiune -= 1;
            ok = 0;
            break;
        }
        i++;
    }
    return ok;
}

void asiguraCapacitate(Offer* lista) {
    ElemType* capacitateNoua = malloc(sizeof(ElemType) * (lista->capacitate * 2));
    for (int i = 0; i < lista->dimensiune; i++)
        capacitateNoua[i] = lista->oferte[i];
    free(lista->oferte);
    lista->oferte = capacitateNoua;
    lista->capacitate *= 2;
}

Offer* creeazaOferte() {
    Offer* f = malloc(sizeof(Offer));
    
    f->dimensiune = 0;
    f->capacitate = 2;
    f->oferte = malloc(sizeof(ElemType) * f->capacitate);
    

    return f;
}

void distrugeOferte(Offer* lista) {
    if (lista != NULL) {
        for (int i = 0; i < lista->dimensiune; i++)
            distruge(lista->oferte[i]);
        free(lista->oferte);
        free(lista);
    }
}

int modificaOferta(Offer* lista, oferta* o) {
    int ok = -1;
    for (int i = 0; i < lista->dimensiune; i++)
    {
        oferta* p = get(lista, i);
        if (p->id == o->id)
        {
            distruge(set(lista, i, o));
            ok = 0;
            break;
        }
    }
    return ok;
}

int cauta(Offer* f, int id) {
    for (int i = 0; i < f->dimensiune; i++) {
        oferta* p = get(f, i);
        if (p->id == id)
            return i;
    }
    return -1;
}

ElemType get(Offer* list, int i) {
    return list->oferte[i];
}

//Schimba elementul de pe pozitia i cu elementul e si returneaza elementul schimbat
ElemType set(Offer* list, int i, ElemType e) {
    ElemType rez = list->oferte[i];
    list->oferte[i] = e;
    return rez;
}

Offer* copy(Offer* p) {
    Offer* f = malloc(sizeof(Offer));
	if (f == NULL)
		return NULL;
    

    f->dimensiune = p->dimensiune;
    f->capacitate = p->capacitate;
    f->oferte = malloc(sizeof(ElemType) * p->capacitate);

    for (int i = 0; i < f->dimensiune; i++)
        f->oferte[i] = copyOferta(p->oferte[i]);
    return f;
}
