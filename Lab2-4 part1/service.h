#pragma once
#include "myList.h"

/// <summary>/// /// </summary>/// <param name="l"></param>/// <param name="tip"></param>/// <param name="suprafata"></param>/// <param name="adresa"></param>/// <param name="pret"></param>/// <returns></returns>
int adaugaOferta(List* l, char* tip, int suprafata, char* adresa, int pret);

/// <summary>/// fucntie care sterge o ofeta din lsita/// </summary>/// <param name="l"></param>/// <param name="tip"></param>/// <param name="suprafata"></param>/// <param name="adresa"></param>/// <param name="pret"></param>/// <returns></returns>
int stergeOferta(List* l, char* tip, int suprafata, char* adresa, int pret);
/// <summary>/// functie care actualizeaza o oferta/// </summary>/// <param name="l"></param>/// <param name="poz"></param>/// <param name="tip"></param>/// <param name="suprafata"></param>/// <param name="adresa"></param>/// <param name="pret"></param>/// <returns></returns>
int actualizeazaOferta(List* l,int poz, char* tip, int suprafata, char* adresa, int pret);
/// <summary>
/// ordonare cres dupa pret
/// </summary>
/// <param name="l"></param>
void ordonareCres(List* l);
/// <summary>///ordonare desc dupa pret /// </summary>/// <param name="l"></param>
void ordonareDesc(List* l);
/// <summary>///functie care filtreaza dupa tipul ofertelor /// </summary>/// <param name="l"></param>/// <param name="tip"></param>/// <returns></returns>
List filtrareTip(List* l, char* tip);

void testService();