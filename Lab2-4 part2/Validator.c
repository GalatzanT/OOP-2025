#include "validator.h"
#include <assert.h>

int valideazaOferta(Oferta of)
{
	if (of.id < 0)
		return 0;
	if (of.suprafata < 0)
		return 0;
	if (of.pret < 0)
		return 0;
	if (strlen(of.tip) == 0)
		return 0;
	if (strlen(of.adresa) == 0)
		return 0;
	if (!strcmp(of.tip, "casa") == 0 && !strcmp(of.tip, "apartament") == 0 && !strcmp(of.tip, "teren") == 0)
		return 0;
	return 1;
}
void testValid() {
	Oferta of = creeazaOferta(1,"casa", 100, "strada", 1000);
	assert(valideazaOferta(of) == 1);
	destroyOferta(&of);
	of = creeazaOferta(3,"casa", -100, "strada", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta(3,"casa", 100, "", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta(10,"casa", 100, "strada", -1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta(20,"", 100, "strada", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta(10,"casa", 100, "strada", 1000);
	assert(valideazaOferta(of) == 1);
	destroyOferta(&of);
	of = creeazaOferta(10,"cort", 100, "strada", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta(-10, "casa", 100, "strada", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
}