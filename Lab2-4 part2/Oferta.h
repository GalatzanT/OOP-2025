#pragma once
#include <string.h>
//fac cu id 
typedef struct {
	int id;
	char* tip;
	int suprafata;
	char* adresa;
	int pret;
} Oferta;

/// <summary> Functie care creeaza o oferta</summary>/// <param name="tip"> de tipul casa, apartament, teren</param>/// <param name="suprafata">int </param>/// <param name="adresa"></param>/// <param name="pret">int </param>/// <returns>o oferta cu aceste atribute</returns>
Oferta creeazaOferta(int id, const char* tip, int suprafata, const char* adresa, int pret);
/// <summary>
/// functie care updateaza o oferta
/// </summary>
/// <param name="of"> oferta intiala</param>
/// <param name="tip"></param>
/// <param name="suprafata"></param>
/// <param name="adresa"></param>
/// <param name="pret"></param>
/// <returns>oferta of cu noile atribute</returns>
void updateOferta(Oferta* of, const char* tip, int suprafata, const char* adresa, int pret);

/// <summary>
/// functionms that copys  a melody
/// </summary>
/// <param name="of">type Oferta</param>
/// <returns>copy of of</returns>
Oferta copyOferta(Oferta* of);
/// <summary>/// funcite care distruge oferta/// </summary>/// <param name="of">oferta ce vrem sa fie distrusa</param>
void destroyOferta(Oferta* of);
/// <summary>/// functie care testeaza functile din oferta/// </summary>
void testOferta();