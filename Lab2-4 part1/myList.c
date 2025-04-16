#include "myList.h"
#include <assert.h>

List createEmpty()
{
	List lst;
	lst.lungime = 0;
	return lst;
}

void add(List* lista, TElem m)
{
	lista->oferte[lista->lungime] = m;
	lista->lungime++;
}

TElem getElem(List* lista, int poz)
{
	return lista->oferte[poz];
}

TElem setElem(List* lista, int poz, TElem el)
{
	TElem deletedElement = getElem(lista, poz);
	lista->oferte[poz] = el;
	return deletedElement;
}

TElem del(List* lista, int poz)
{

	TElem deletedElement = getElem(lista, poz);
	TElem lastElement = getElem(lista, lista->lungime - 1);
	setElem(lista, poz, lastElement);
	lista->lungime--;
	return deletedElement;
}

List copyList(List* lista)
{
	List copieLista = createEmpty();
	for (int i = 0; i < lista->lungime; i++) {
		TElem e = getElem(lista, i);
		add(&copieLista, e);
	}
	return copieLista;
}

void destroy(List* lista)
{
	lista->lungime = 0;
}

int size(List* lista)
{
	return lista->lungime;
}

int find(List* lista, Oferta of) {
	for (int i = 0; i < lista->lungime; i++) {
		Oferta current = getElem(lista, i);
		if (strcmp(current.tip, of.tip) == 0 &&
			current.suprafata == of.suprafata &&
			strcmp(current.adresa, of.adresa) == 0 &&
			current.pret == of.pret) {
			return i; // Găsit, returnează poziția
		}
	}
	return -1; // Nu s-a găsit oferta
}

void testCreateList()
{
	List testList = createEmpty();
	assert(size(&testList) == 0);
}

void testAdd()
{
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	assert(size(&testList) == 1);
}

void testGetElem()
{
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	Oferta of2 = getElem(&testList, 0);
	assert(strcmp(of2.tip, "casa") == 0);
	assert(of2.suprafata == 100);
	assert(strcmp(of2.adresa, "strada") == 0);
	assert(of2.pret == 1000);
}

void testSetElem()
{
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	Oferta of2 = creeazaOferta("apartament", 200, "strada2", 2000);
	Oferta of3 = setElem(&testList, 0, of2);
	assert(strcmp(of3.tip, "casa") == 0);
	assert(of3.suprafata == 100);
	assert(strcmp(of3.adresa, "strada") == 0);
	assert(of3.pret == 1000);
	Oferta of4 = getElem(&testList, 0);
	assert(strcmp(of4.tip, "apartament") == 0);
	assert(of4.suprafata == 200);
	assert(strcmp(of4.adresa, "strada2") == 0);
	assert(of4.pret == 2000);
}

void testDel()
{
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	Oferta of2 = del(&testList, 0);
	assert(strcmp(of2.tip, "casa") == 0);
	assert(of2.suprafata == 100);
	assert(strcmp(of2.adresa, "strada") == 0);
	assert(of2.pret == 1000);
	assert(size(&testList) == 0);
}
void testCopyList()
{
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	List copie = copyList(&testList);
	assert(size(&copie) == 1);
	Oferta of2 = getElem(&copie, 0);
	assert(strcmp(of2.tip, "casa") == 0);
	assert(of2.suprafata == 100);
	assert(strcmp(of2.adresa, "strada") == 0);
	assert(of2.pret == 1000);
}
void testDestroy()
{
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	destroy(&testList);
	assert(size(&testList) == 0);
}
void testSize()
{
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	assert(size(&testList) == 1);
}
void testFind() {
	List testList = createEmpty();
	Oferta of = creeazaOferta("casa", 100, "strada", 1000);
	add(&testList, of);
	Oferta of2 = creeazaOferta("casa", 100, "strada", 1000);
	assert(find(&testList, of2) == 0);
	Oferta of3 = creeazaOferta("apartament", 200, "strada2", 2000);
	assert(find(&testList, of3) == -1);

}

void testAllList()
{
	testFind();
	testCreateList();
	testAdd();
	testGetElem();
	testSetElem();
	testDel();
	testCopyList();
	testDestroy();
	testSize();
}
