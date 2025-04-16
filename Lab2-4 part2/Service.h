#pragma once
#include "Repo.h"
#include "Validator.h"


/// <summary>/// /// </summary>/// <param name="l"></param>/// <param name="tip"></param>/// <param name="suprafata"></param>/// <param name="adresa"></param>/// <param name="pret"></param>/// <returns></returns>
int adaugaOferta(VectorDinamic* l,int id, char* tip, int suprafata, char* adresa, int pret);

/// <summary>/// fucntie care sterge o ofeta din lsita/// </summary>/// <param name="l"></param>/// <param name="tip"></param>/// <param name="suprafata"></param>/// <param name="adresa"></param>/// <param name="pret"></param>/// <returns></returns>
int stergeOfertaService(VectorDinamic* l, int id);
/// <summary>/// functie care actualizeaza o oferta/// </summary>/// <param name="l"></param>/// <param name="poz"></param>/// <param name="tip"></param>/// <param name="suprafata"></param>/// <param name="adresa"></param>/// <param name="pret"></param>/// <returns></returns>
int actualizeazaOferta(VectorDinamic* l, int id, char* tip, int suprafata, char* adresa, int pret);
/// <summary>
/// ordonare cres dupa pret
/// </summary>
/// <param name="l"></param>
//void ordonareCres(VectorDinamic* l);
/// <summary>///ordonare desc dupa pret /// </summary>/// <param name="l"></param>
//void ordonareDesc(VectorDinamic* l);
/// <summary>///functie care filtreaza dupa tipul ofertelor /// </summary>/// <param name="l"></param>/// <param name="tip"></param>/// <returns></returns>
//VectorDinamic filtrareTip(VectorDinamic* l, char* tip);


int comparaPretCrescator(const void* a, const void* b);
int comparaPretDescrescator(const void* a, const void* b);
int comparaSuprafataCrescator(const void* a, const void* b);
int comparaSuprafataDescrescator(const void* a, const void* b);
void ordonare(VectorDinamic* l, int (*compara)(const void*, const void*));

void testService();
