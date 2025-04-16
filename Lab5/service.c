#define _CRT_SECURE_NO_WARNINGS
#include "service.h"
#include "repo.h"
#include "domain.h"
#include "sort.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

Service createService() {
    Service service;
    service.lista = creeazaOferte();
    service.undolist = createList(distrugeOferte, copy);
    return service;
}



int addEnt(Service* lista, int id, char* tip, int suprafata, char* adresa, float pret) {
	Offer* copyList = copy(lista->lista);
	add(lista->undolist, copyList);
    oferta* e = CreeazaOferta(id, tip, suprafata, adresa, pret);
    if (valideaza(e) == 1) {
        addEntitate(lista->lista, e);
        return 1;
    }
    else {
        distruge(e);
        return 0;
    }
}

int deleteEnt(Service* list, int i) {
    Offer* copyList = copy(list->lista);
    add(list->undolist, copyList);
    if (checkId(list, i) != 0) {
        deleteEntitate(list->lista, i);
        return 1;
    }
    return 0;
}

int checkId(Service* list, int id) {
    if (cauta(list->lista, id) == -1)
        return 0;
    return 1;
}

int updateEnt(Service* list, int id, char* tip, int suprafata, char* adresa, float pret) {
    Offer* copyList = copy(list->lista);
    add(list->undolist, copyList);
    for (int i = 0; i < list->lista->dimensiune; i++) {
        if (getId(get(list->lista, i)) == id) {
            oferta* e = CreeazaOferta(id, tip, suprafata, adresa, pret);
            
            modificaOferta(list->lista, e);
            return 0;
        }
    }
    return -1;
}

void destroyAll(Service* list) {
    if (list != NULL && list->lista != NULL) {
        distrugeOferte(list->lista);
        list->lista = NULL;
    }
	destroyList(list->undolist);
	list->undolist = NULL;
}

int cmpPret(oferta* m1, oferta* m2) {
    if (m1->pret == m2->pret)
        return 0;
    if (m1->pret > m2->pret)
        return 1;
    else
        return -1;
}

int cmpPretDesc(oferta* m1, oferta* m2) {
    if (m1->pret == m2->pret)
        return 0;
    if (m1->pret < m2->pret)
        return 1;
    else
        return -1;
}

int cmpTip(oferta* m1, oferta* m2) {
    return strcmp(m1->tip, m2->tip);
}

int cmpTipDest(oferta* m1, oferta* m2) {
    return strcmp(m2->tip, m1->tip);
}

Service* sortPret(Service* l) {
    sort(l->lista, cmpPret);
    return l;
}

Service* sortPretDesc(Service* l) {
    sort(l->lista, cmpPretDesc);
    return l;
}

Service* sortTip(Service* l) {
    sort(l->lista, cmpTip);
    return l;
}

Service* sortTipDest(Service* l) {
    sort(l->lista, cmpTipDest);
    return l;
}

Offer* filterPret(Service* list, int val) {
    Offer* copyList = copy(list->lista);
    add(list->undolist, copyList);
    Offer* f = copy(list->lista);

    for (int i = 0; i < f->dimensiune; i++) {
        oferta* m = get(f, i);
        if (m->pret > val) {
            deleteEntitate(f, m->id);
            i--;
        }
    }
    return f;
}

Offer* filterTip(Service* list, char litera) {
    Offer* copyList = copy(list->lista);
    add(list->undolist, copyList);
    Offer* f = copy(list->lista);

    for (int i = 0; i < f->dimensiune; i++) {
        oferta* m = get(f, i);
        if (m->tip[0] != litera) {
            deleteEntitate(f, m->id);
            i--;
        }
    }
    return f;
}

void filtrarePret2(Service* service, int val) {
    Offer* copyList = copy(service->lista);
    add(service->undolist, copyList);
	for (int i = 0; i < service->lista->dimensiune; i++) {
		oferta* m = get(service->lista, i);
		if (m->pret > val) {
			deleteEntitate(service->lista, m->id);
			i--;
		}
	}
}


void undo(Service* service) {
    if (service->undolist->size == 0) {
        return;
    }
    Offer* lastList = service->undolist->elements[service->undolist->size - 1];
    service->undolist->size--;
    distrugeOferte(service->lista);
    service->lista = lastList;
}

void testUndoFiltratePret2() {
	Service service = createService();
	addEnt(&service, 1, "casa", 100, "adresa1", 200);
	addEnt(&service, 2, "casa", 200, "adresa2", 300);
	addEnt(&service, 3, "casa", 300, "adresa3", 400);
    filtrarePret2(&service, 250);
	assert(service.lista->dimensiune == 1);
	undo(&service);
	assert(service.lista->dimensiune == 3);
	distrugeOferte(service.lista);
}