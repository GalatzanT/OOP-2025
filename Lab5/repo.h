#pragma once
#include "domain.h"

typedef void* ElemType;

typedef struct {
    ElemType* oferte;
    int dimensiune;
    int capacitate;
}Offer;

void addEntitate(Offer*, ElemType);

//Sterge dupa id
int deleteEntitate(Offer*, int);

//Dubleaza capacitatea
void asiguraCapacitate(Offer*);

//Creeaza oferta noua
Offer* creeazaOferte();

//Distruge ogerte
void distrugeOferte(Offer*);

//Modifica oferta
int modificaOferta(Offer* lista, oferta* o);

//returneaza oferta dupa id
ElemType get(Offer*, int);

//pune pe pozitie entinatea
ElemType set(Offer*, int, ElemType);

//cauta oferta dupa id
int cauta(Offer*, int);

//Copiere lista de oferte
Offer* copy(Offer*);