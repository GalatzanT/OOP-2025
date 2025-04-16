#pragma once
#include "oferta.h"

typedef Oferta TElem;

typedef struct {
	TElem oferte[100];
	int lungime;
} List;
/// <summary>
/// Functie care creeaza o lista vida
/// </summary>
/// <returns>returneaza o lista vida</returns>
List createEmpty();

/// <summary>
/// Adauga un element la sfarsitul listei
/// </summary>
/// <param name="lista">lista in care se adauga (List*)</param>
/// <param name="m"> elementul care se adauga (TElem)</param>
void add(List* lista, TElem m);

/// <summary>
/// Returneaza elementul de pe pozitia data
/// </summary>
/// <param name="lista">lista data (List*)</param>
/// <param name="poz">pozitia data (int)</param>
/// <returns> elementul de pe pozitia poz (TElem) </returns>
TElem getElem(List* lista, int poz);

/// <summary>
/// Pune elementul el pe pozitia poz in lista data
/// </summary>
/// <param name="lista">lista care se modifica (List*)</param>
/// <param name="poz">pozitia pe care este pus elementul (int), pre: poz>=0, lista.lungime>poz</param>
/// <param name="el">elementul dat (TElem)</param>
/// <returns>elementul care era anterior pe pozitia poz (TElem)</returns>
TElem setElem(List* lista, int poz, TElem el);
/// <summary>
/// Sterge elementul de pe pozitia data din lista
/// </summary>
/// <param name="lista">lista din care se sterge (List*)</param>
/// <param name="poz">pozitia de pe care se sterge (int), pre: poz>=0, lista.lungime>poz</param>
/// <returns> elementul sters (TElem)</returns>
TElem del(List* lista, int poz);

/// <summary>
/// Face o copie a listei date
/// </summary>
/// <param name="lista">lista care se copiaza (List*)</param>
/// <returns>copie a listei date (List)</returns>
List copyList(List* lista);

/// <summary>
/// Distruge lista data (dealoca memoria utilizata de aceasta)
/// </summary>
/// <param name="lista">lista care se distruge (List*)</param>
void destroy(List* lista);

/// <summary>
/// Returneaza numarul de elemente din lista
/// </summary>
/// <param name="lista">lista data (List*)</param>
/// <returns>numarul de elemente din lista (int)</returns>
int size(List* lista);
/// <summary>
/// gaseste poz unei oferte in lista
/// </summary>
/// <param name="lista"></param>
/// <param name="of"></param>
/// <returns></returns>
int find(List* lista, Oferta of);

void testFind();
void testCreateList();
void testAdd();
void testGetElem();
void testSetElem();
void testDel();
void testCopyList();
void testDestroy();
void testSize();
void testAllList();
