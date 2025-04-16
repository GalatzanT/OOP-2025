#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <crtdbg.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h> 

#include "service.h"
/// <summary>
/// functie care printeaza meniul
/// </summary>
void printMenu() {
	printf("Aplicatie de gestiune oferte:\n");
	printf("1. Adauga oferta\n");
	printf("2. Actualizeaza oferta\n");
	printf("3. Sterge oferta\n");
	printf("4. Ordonare dupa pret\n");
	printf("5. Filtrare dupa tip \n");
	printf("6. Vizualizare toate ofertele\n");
	printf("7. Exit\n");
	

}
/// <summary>
/// functie care afiseaza un mesaj colorat
/// </summary>
/// <param name="message"> char</param>
/// <param name="colorCode"> culoarea dorita de tip int</param>
void printColoredText(char* message, int colorCode) {
	//albastru inchis: 1 sau 9
	//verde: 2 sau 10
	//rosu: 4 sau 12

	HANDLE  hConsole;


	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// you can loop k higher to see more color choices

	SetConsoleTextAttribute(hConsole, colorCode);
	printf("%s", message);
	//reset to default
	SetConsoleTextAttribute(hConsole, 7);




}




void uiAdaugaMelodie(List* lista) {
	char tip[20];
	int suprafata;
	char adresa[20];
	int pret;
	printf("Dati tipul: ");
	scanf("%s", tip);
	printf("Dati suprafata: ");
	scanf("%d", &suprafata);
	printf("Dati adresa: ");
	scanf("%s", adresa);
	printf("Dati pretul: ");
	scanf("%d", &pret);
	int rezultat = adaugaOferta(lista,tip, suprafata, adresa, pret);
	if (rezultat == 0) {
		printColoredText("Oferta adaugata cu succes\n", 10);
	}
	else {
		printColoredText("Oferta invalida\n", 12);
	}
}

void uiPrintList(List* l) {
	printColoredText("Oferte:\n", 10);
	for (int i = 0; i < l->lungime; i++) {
		Oferta of = getElem(l, i);
		printf("Tip: %s, Suprafata: %d, Adresa: %s, Pret: %d\n", of.tip, of.suprafata, of.adresa, of.pret);
	}
}


void add10Oferte(List* l) {
	adaugaOferta(l, "casa", 100, "strada1", 1000);
	adaugaOferta(l, "apartament", 200, "strada2", 2000);
	adaugaOferta(l, "teren", 300, "strada3", 3000);
	adaugaOferta(l, "casa", 400, "strada4", 4000);
	adaugaOferta(l, "apartament", 500, "strada5", 5000);
	adaugaOferta(l, "teren", 600, "strada6", 6000);
	adaugaOferta(l, "casa", 700, "strada7", 7000);
	adaugaOferta(l, "apartament", 800, "strada8", 8000);
	adaugaOferta(l, "teren", 900, "strada9", 9000);
	adaugaOferta(l, "casa", 1000, "strada10", 10000);

}

void uiStergeOferta(List* l) {
	char tip[20];
	int suprafata;
	char adresa[20];
	int pret;
	printf("Dati tipul: ");
	scanf("%s", tip);
	printf("Dati suprafata: ");
	scanf("%d", &suprafata);
	printf("Dati adresa: ");
	scanf("%s", adresa);
	printf("Dati pretul: ");
	scanf("%d", &pret);
	int rezultat = stergeOferta(l, tip, suprafata, adresa, pret);
	if (rezultat == 0) {
		printColoredText("Oferta stearsa cu succes\n", 10);
	}
	else {
		printColoredText("Oferta invalida sau nu a fost gasita\n", 12);
	}
}

void uiActualiziazaOferta(List* l) {
	int poz;
	char tip[20];
	int suprafata;
	char adresa[20];
	int pret;
	printf("Dati pozitia: ");
	scanf("%d", &poz);
	printf("Dati tipul: ");
	scanf("%s", tip);
	printf("Dati suprafata: ");
	scanf("%d", &suprafata);
	printf("Dati adresa: ");
	scanf("%s", adresa);
	printf("Dati pretul: ");
	scanf("%d", &pret);
	int rezultat = actualizeazaOferta(l, poz, tip, suprafata, adresa, pret);
	if (rezultat == 0) {
		printColoredText("Oferta actualizata cu succes\n", 10);
	}
	else {
		printColoredText("Oferta invalida sau nu a fost gasita\n", 12);
	}
}

void uiOrdonarePret(List* l) {
	char regula[20];
	printColoredText("cres sau desc:\n", 10);
	scanf("%s", regula);
	if (strcmp(regula, "cres") == 0 ) {
		
		ordonareCres(l);
		uiPrintList(l);
	}
	else if (strcmp(regula, "desc") == 0) {
		ordonareDesc(l);
		uiPrintList(l);
	}
	else {
		printColoredText("Regula invalida\n", 12);
	}
		
	
}

void uiFiltrareTip(List* l) {
	char tip[20];		
	printf("Dati tipul: ");
	scanf("%s", tip);
	if (strcmp(tip, "casa") == 0 || strcmp(tip, "apartament") == 0 || strcmp(tip, "teren") == 0) {
		List copie = filtrareTip(l, tip);
		uiPrintList(&copie);
	}
	else {
		printColoredText("Tip invalid\n", 12);
	}
}
void testALL() {
	testCreeazaUpdateDestroyOferta();
	testAllList();
	testValid();
	testService();
}

void run() {
	testALL();
	List l = createEmpty();
	add10Oferte(&l);
	while (true) {
		printMenu();
		int optiune;
		
		if (scanf("%d", &optiune) == 1 && optiune > 0 && optiune < 8) {



			if (optiune == 7) {
				break;
			}
			switch (optiune) {
			case 1:
				uiAdaugaMelodie(&l);
				break;
			case 2:
				uiActualiziazaOferta(&l);
				break;
			case 3:
				uiStergeOferta(&l);
				break;
			case 4:
				uiOrdonarePret(&l);
				break;
			case 5:
				uiFiltrareTip(&l);
				break;
			case 6:
				uiPrintList(&l);
				break;
			default:
				printColoredText("Optiune invalida\n", 12);
				break;
			}
		}
		else {
			printColoredText("Optiune invalida\n", 12);
			while (getchar() != '\n');
			continue;
		}
	}
}


int main(){
	
	run();
	return 0;
}

