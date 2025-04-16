#include "validator.h"
#include <assert.h>

int valideazaOferta(Oferta of)
{
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
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	assert(valideazaOferta(of) == 1);
	destroyOferta(&of);
	of = creeazaOferta("casa", -100, "strada", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta("casa", 100, "", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta("casa", 100, "strada", -1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta("", 100, "strada", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
	of = creeazaOferta("casa", 100, "strada", 1000);
	assert(valideazaOferta(of) == 1);
	of = creeazaOferta("cort", 100, "strada", 1000);
	assert(valideazaOferta(of) == 0);
	destroyOferta(&of);
}