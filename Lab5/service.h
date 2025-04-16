#pragma once
#include "domain.h"
#include "list.h"
#include "repo.h"

typedef struct {
	Offer* lista;
	List* undolist;
}Service;

/*Creaza o lista de oferte
 return - lista de oferte

*/
Service createService();

/*Distruge lista de oferte
* param list - lista de oferte
*/
void destroyService(Service*);

int addEnt(Service*, int, char*, int, char*, float);

int deleteEnt(Service* list, int i);

int checkId(Service* list, int id);

int updateEnt(Service* list, int id, char* tip, int suprafata, char* adresa, float pret);

Service* sortPret(Service* l);

Service* sortPretDesc(Service* l);

Service* sortTip(Service* l);

Service* sortTipDest(Service* l);

void destroyAll(Service* list);

int cmpPret(oferta* m1, oferta* m2);

int cmpPretDesc(oferta* m1, oferta* m2);

int cmpTip(oferta* m1, oferta* m2);

int cmpTipDest(oferta* m1, oferta* m2);

Offer* filterTip(Service* list, char litera);

Offer* filterPret(Service* list, int val);

void filtrarePret2(Service* service, int val);

void undo(Service* service);

void testUndoFiltratePret2();