#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>
#include "Oferta.h"
#include "Validator.h"
#include "Repo.h"
#include "Service.h"
#include <windows.h> 
#include <stdbool.h>
/// <summary>
/// functie care printeaza meniul
/// </summary>
void printMenu() {
	printf("Aplicatie de gestiune oferte:\n");
	printf("1. Adauga oferta\n");
	printf("2. Actualizeaza oferta\n");
	printf("3. Sterge oferta\n");
	printf("4. Ordonare\n");
	printf("5. Filtrare dupa tip \n");
	printf("6. Vizualizare toate ofertele\n");
	printf("7. Exit\n");


}





void uiAdaugaMelodie(VectorDinamic* lista) {
	int id;
	char tip[20];
	int suprafata;
	char adresa[20];
	int pret;
	printf("Dati id-ul: ");
	scanf("%d", &id);
	printf("Dati tipul: ");
	scanf("%s", tip);
	printf("Dati suprafata: ");
	scanf("%d", &suprafata);
	printf("Dati adresa: ");
	scanf("%s", adresa);
	printf("Dati pretul: ");
	scanf("%d", &pret);
	int rezultat = adaugaOferta(lista,id, tip, suprafata, adresa, pret);
	if (rezultat == 0) {
		printf("Oferta adaugata cu succes\n");
	}
	else {
		printf("Oferta invalida\n");
	}
}

void uiPrintList(VectorDinamic* l) {
	printf("Oferte:\n");
	for (int i = 0; i < l->lg; i++) {
		Oferta of = l->elems[i];
		printf("Id: %d Tip: %s, Suprafata: %d, Adresa: %s, Pret: %d\n",of.id, of.tip, of.suprafata, of.adresa, of.pret);
	}
}


void add10Oferte(VectorDinamic* l) {
	adaugaOferta(l,1, "casa", 100, "strada1", 1000);
	adaugaOferta(l,2, "apartament", 200, "strada2", 2000);
	adaugaOferta(l,3, "teren", 300, "strada3", 3000);
	adaugaOferta(l,4, "casa", 400, "strada4", 4000);
	adaugaOferta(l,5, "apartament", 500, "strada5", 5000);
	adaugaOferta(l,6, "teren", 600, "strada6", 6000);
	adaugaOferta(l,7, "casa", 700, "strada7", 7000);
	adaugaOferta(l,8, "apartament", 800, "strada8", 8000);
	adaugaOferta(l,9, "teren", 900, "strada9", 9000);
	adaugaOferta(l,10, "casa", 1000, "strada10", 10000);

}

void uiStergeOferta(VectorDinamic* l) {
	int id;
	printf("Dati id-ul: ");
	scanf("%d", &id);
	int rezultat = stergeOfertaService(l, id);
	if (rezultat == 0) {
		printf("Oferta stearsa cu succes\n");
	}
	else {
		printf("Oferta invalida sau nu a fost gasita\n");
	}
}

void uiActualiziazaOferta(VectorDinamic* l) {
	int id;
	char tip[20];
	int suprafata;
	char adresa[20];
	int pret;
	printf("Dati id-ul ofertei care vreti sa fie actualizate: ");
	scanf("%d", &id);
	printf("Dati tipul: ");
	scanf("%s", tip);
	printf("Dati suprafata: ");
	scanf("%d", &suprafata);
	printf("Dati adresa: ");
	scanf("%s", adresa);
	printf("Dati pretul: ");
	scanf("%d", &pret);
	int rezultat = actualizeazaOferta(l, id, tip, suprafata, adresa, pret);
	if (rezultat == 0) {
		printf("Oferta actualizata cu succes\n");
	}
	else {
		printf("Oferta invalida sau nu a fost gasita\n");
	}
}

void uiOrdonare(VectorDinamic* l) {
	char regula[20];
	char criteriu[20];

	printf("Alegeti criteriul de ordonare: pret sau suprafata: ");
	scanf("%s", criteriu);

	printf("Alegeti ordonarea: crescator (cres) sau descrescator (desc): ");
	scanf("%s", regula);

	if (strcmp(criteriu, "pret") == 0) {
		if (strcmp(regula, "cres") == 0) {
			ordonare(l, comparaPretCrescator);  // Ordonare crescătoare după preț
		}
		else if (strcmp(regula, "desc") == 0) {
			ordonare(l, comparaPretDescrescator);  // Ordonare descrescătoare după preț
		}
		else {
			printf("Regula invalida\n");
			return;
		}
	}
	else if (strcmp(criteriu, "suprafata") == 0) {
		if (strcmp(regula, "cres") == 0) {
			ordonare(l, comparaSuprafataCrescator);  // Ordonare crescătoare după suprafață
		}
		else if (strcmp(regula, "desc") == 0) {
			ordonare(l, comparaSuprafataDescrescator);  // Ordonare descrescătoare după suprafață
		}
		else {
			printf("Regula invalida\n");
			return;
		}
	}
	else {
		printf("Criteriu invalid\n");
		return;
	}

	uiPrintList(l);  // Afișează lista ordonată
}

void uiFiltrareTip(VectorDinamic* l) {
	char tip[20];
	printf("Dati tipul (casa, apartament, teren): ");
	scanf("%s", tip);

	for (int i = 0; i < l->lg; i++) {
		if (strcmp(l->elems[i].tip, tip) == 0) {
			printf("Id: %d Tip: %s, Suprafata: %d, Adresa: %s, Pret: %d\n", l->elems[i].id, l->elems[i].tip, l->elems[i].suprafata, l->elems[i].adresa, l->elems[i].pret);
		}
	}
}
void testAll() {

	printf("incepem testele\n");
	testOferta();
	testValid();
	testDinamicList();
	testService();	
	printf("testele s-au terminat\n");
}

void run() {
	testAll();
	VectorDinamic* l = creazaVectorDinamic();
	add10Oferte(l);
	while (true) {
		printMenu();
		int optiune;

		if (scanf("%d", &optiune) == 1 && optiune > 0 && optiune < 8) {



			if (optiune == 7) {
				break;
			}
			switch (optiune) {
			case 1:
				uiAdaugaMelodie(l);
				break;
			case 2:
				uiActualiziazaOferta(l);
				break;
			case 3:
				uiStergeOferta(l);
				break;
			case 4:
				uiOrdonare(l);
				break;
			case 5:
				uiFiltrareTip(l);
				break;
			case 6:
				uiPrintList(l);
				break;
			default:
				printf("Optiune invalida\n");
				break;
			}
		}
		else {
			printf("Optiune invalida\n");
			while (getchar() != '\n');
			continue;
		}
	}
	distruge(l);
}



int main() {
	run();
	_CrtDumpMemoryLeaks();
	return 0;
}