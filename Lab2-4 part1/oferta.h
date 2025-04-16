#pragma once
#include <string.h>
//fac cu id 
typedef struct {
	char tip[20];
	int suprafata;
	char adresa[20];
	int pret;
} Oferta;

/// <summary> Functie care creeaza o oferta</summary>/// <param name="tip"> de tipul casa, apartament, teren</param>/// <param name="suprafata">int </param>/// <param name="adresa"></param>/// <param name="pret">int </param>/// <returns>o oferta cu aceste atribute</returns>
Oferta creeazaOferta(const char* tip, int suprafata, const char* adresa, int pret);
/// <summary>
/// functie care updateaza o oferta
/// </summary>
/// <param name="of"> oferta intiala</param>
/// <param name="tip"></param>
/// <param name="suprafata"></param>
/// <param name="adresa"></param>
/// <param name="pret"></param>
/// <returns>oferta of cu noile atribute</returns>
Oferta updateOferta(Oferta* of, const char* tip, int suprafata, const char* adresa, int pret);

/// <summary>/// funcite care distruge oferta/// </summary>/// <param name="of">oferta ce vrem sa fie distrusa</param>
void destroyOferta(Oferta* of);
/// <summary>/// functie care testeaza functile din oferta/// </summary>
void testCreeazaUpdateDestroyOferta();