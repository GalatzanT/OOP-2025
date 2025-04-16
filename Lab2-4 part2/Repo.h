#include "Oferta.h"
#pragma once
typedef Oferta Elem;

#define INIT_CAPACITY 2

typedef struct {
	Elem* elems;
	int lg;
	int capacitate;
} VectorDinamic;


/**
*Creaza un vector dinamic
* v vector
* post: vectorul e gol
*/
VectorDinamic* creazaVectorDinamic();


/**
* Aloca memorie aditionala pentru vector
*/
void resize(VectorDinamic* v);

/// <summary>
/// returneaza pointer la elementul cu id-ul dat
/// </summary>
/// <param name="v"></param>
/// <param name="id"></param>
/// <returns></returns>
int getElemIndex(VectorDinamic* v, int id);
/**
* Adauga un element in vector
* v - vector dinamic
* el - elementul de adaugat
*/
/// <summary>
/// sterge o oferta din vector
int stergeOferta(VectorDinamic* v, int id);

void add(VectorDinamic* v, Elem el);

/**
* Elibereaza memoria ocupata de vector
*/
void distruge(VectorDinamic* v);
/// <summary>
/// functie pentru testarea functiilor dinamic list
/// </summary>
/// 

void testDinamicList();





