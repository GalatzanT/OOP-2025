#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <string.h>
#include "service.h"
#include "repo.h"
#include "domain.h"
#include "ui.h"

void printMeniu() {
    printf("1.Adaugare\n");
    printf("2.Modifica\n");
    printf("3.Stergere\n");
    printf("4.Vizualizare ordonat\n");
    printf("5.Filtrare\n");
    printf("6.Afisare\n");
	printf("7.Undo\n");
	printf("8.Filtrate pret mai mic 1500\n");
    printf("0.Iesire\n");
}

void citOferta(Service* service) {
    printf("Adauga oferta: id, tip, suprafata, adresa, pret\n");
    char tip[30], adresa[50];
    int suprafata, id;
    float pret;
    printf("Introduceti id-ul: ");
    if (scanf("%d", &id) != 1) {
        printf("Eroare la citirea id-ului!\n");
        while (getchar() != '\n'); 
        return;
    }
    getchar(); 
    if (checkId(service, id) == 0) {
        printf("Introduceti tipul(teren/casa/apartament): ");
        if (scanf("%29s", tip) != 1) {
            printf("Eroare la citirea tipului!\n");
            while (getchar() != '\n');
            return;
        }
        printf("Introduceti suprafata: ");
        if (scanf("%d", &suprafata) != 1) {
            printf("Eroare la citirea suprafetei!\n");
            while (getchar() != '\n');
            return;
        }
        getchar(); 
        printf("Introduceti adresa: ");
        if (fgets(adresa, sizeof(adresa), stdin) == NULL) {
            printf("Eroare la citirea adresei!\n");
            return;
        }
        adresa[strcspn(adresa, "\n")] = '\0'; 
        printf("Introduceti pretul: ");
        if (scanf("%f", &pret) != 1) {
            printf("Eroare la citirea pretului!\n");
            while (getchar() != '\n'); 
            return;
        }
        if (addEnt(service, id, tip, suprafata, adresa, pret))
            printf("Oferta a fost adaugata cu succes!\n");
        else
            printf("Oferta invalida!\n");
    }
    else {
        printf("Exista deja oferta cu id-ul dat!\n");
    }
}

void modOferta(Service* service) {
    printf("Adauga oferta: id, tip, suprafata, adresa, pret\n");
    char tip[30], adresa[50];
    int suprafata, id;
    float pret;
    printf("Introduceti id-ul: ");
    if (scanf("%d", &id) != 1) {
        printf("Eroare la citirea id-ului!\n");
        while (getchar() != '\n'); 
        return;
    }
    getchar(); 
    printf("Introduceti tipul(teren/casa/apartament): ");
    if (scanf("%29s", tip) != 1) {
        printf("Eroare la citirea tipului!\n");
        while (getchar() != '\n');
        return;
    }
    printf("Introduceti suprafata: ");
    if (scanf("%d", &suprafata) != 1) {
        printf("Eroare la citirea suprafetei!\n");
        while (getchar() != '\n'); 
        return;
    }
    getchar();
    printf("Introduceti adresa: ");
    if (fgets(adresa, sizeof(adresa), stdin) == NULL) {
        printf("Eroare la citirea adresei!\n");
        return;
    }
    adresa[strcspn(adresa, "\n")] = '\0'; 
    printf("Introduceti pretul: ");
    if (scanf("%f", &pret) != 1) {
        printf("Eroare la citirea pretului!\n");
        while (getchar() != '\n'); 
        return;
    }
    if (!updateEnt(service, id, tip, suprafata, adresa, pret))
        printf("Modificare efectuata cu succes!\n");
    else
        printf("Ati introdus o oferta invalida!\n");
}

void stergeOferta(Service* service) {
    printf("Id-ul ofertei pe care doriti sa il stergeti:\n");
    int id;
    if (scanf("%d", &id) != 1) {
        printf("Eroare la citirea id-ului!\n");
        while (getchar() != '\n'); 
        return;
    }
    getchar();
    if (!deleteEnt(service, id))
        printf("Aceasta oferta nu exista!\n");
    else
        printf("Oferta stearsa cu succes!\n");
}

void printOferte(Service* service) {
    for (int i = 0; i < service->lista->dimensiune; i++) {
        oferta* m = get(service->lista, i);
        printf("[%d] Tip:%s, Suprafata:%d, Adresa:%s, Pret:%f\n", m->id, m->tip, m->suprafata, m->adresa, m->pret);
    }
}

void destroy(Service* service) {
    destroyAll(service);
}

void sortare(Service* service) {
    printf("1.Sortare dupa pret\n");
    printf("2.Sortare dupa tip\n");
    printf("Alegeti optiunea: ");
    int cmd1;
    if (scanf("%d", &cmd1) != 1) {
        printf("Eroare la citirea optiunii!\n");
        while (getchar() != '\n');
        return;
    }
    if (cmd1 == 1) {
        printf("1.Crescator\n");
        printf("2.Descrescator\n");
        printf("Alegeti optiunea: ");
        int cmd2;
        if (scanf("%d", &cmd2) != 1) {
            printf("Eroare la citirea optiunii!\n");
            while (getchar() != '\n'); 
            return;
        }
        if (cmd2 == 1) {
            Service* lst = sortPret(service);
            printOferte(lst);
			
        }
        else {
            Service* lst = sortPretDesc(service);
            printOferte(lst);
			
        }
    }
    else {
        printf("1.Crescator\n");
        printf("2.Descrescator\n");
        printf("Alegeti optiunea: ");
        int cmd2;
        if (scanf("%d", &cmd2) != 1) {
            printf("Eroare la citirea optiunii!\n");
            while (getchar() != '\n'); 
            return;
        }
        if (cmd2 == 1) {
            Service* lst = sortTip(service);
            printOferte(lst);
		
        }
        else {
            Service* lst = sortTipDest(service);
            printOferte(lst);
		
        }
    }
}

void filtrare(Service* service) {
    printf("1.Filtrare dupa tip\n");
    printf("2.Filtrare dupa pret\n");
    printf("Alegeti optiunea: ");
    int cmd1;
    if (scanf("%d", &cmd1) != 1) {
        printf("Eroare la citirea optiunii!\n");
        while (getchar() != '\n'); 
        return;
    }
    getchar(); 
    if (cmd1 == 1) {
        printf("Introduceti litera: ");
        char litera[2];
        if (scanf("%1s", litera) != 1) {
            printf("Eroare la citirea literei!\n");
            while (getchar() != '\n'); 
            return;
        }
        getchar(); 

        Offer* f = filterTip(service, litera[0]);
        for (int i = 0; i < f->dimensiune; i++) {
            oferta* m = get(f, i);
            printf("Id: %d; Tip: %s; Suprafata: %d; Adresa: %s; Pret: %.2f\n", m->id, m->tip, m->suprafata, m->adresa, m->pret);
        }

        distrugeOferte(f);
    }
    else {
        printf("Dati o valoare intrega, pozitiva, nenula:\n");
        int val;
        if (scanf("%d", &val) != 1) {
            printf("Eroare la citirea valorii!\n");
            while (getchar() != '\n'); 
            return;
        }
        getchar(); 
        Offer* f = filterPret(service, val);
        for (int i = 0; i < f->dimensiune; i++) {
            oferta* m = get(f, i);
            printf("Id: %d; Tip: %s; Suprafata: %d; Adresa: %s; Pret: %.2f\n", m->id, m->tip, m->suprafata, m->adresa, m->pret);
        }

        distrugeOferte(f);
    }
}

void addDefault(Service* service) {
    addEnt(service, 1, "teren", 100, "strada1", 1000);
    addEnt(service, 2, "casa", 200, "strada2", 2000);
    addEnt(service, 3, "apartament", 300, "strada3", 3000);
}

void run() {
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    Service service = createService();
	addDefault(&service);
    int isrunning = 1;
    while (isrunning) {
        int cmd;
        printMeniu();
        printf("Introduceti comanda: ");
        if (scanf("%d", &cmd) != 1) {
            while (getchar() != '\n'); 
            printf("Optiune invalida\n");
            continue;
        }
        getchar(); 
        switch (cmd) {
        case 1:
            citOferta(&service);
            break;
        case 2:
            modOferta(&service);
            break;
        case 3:
            stergeOferta(&service);
            break;
        case 4:
            sortare(&service);
            break;
        case 5:
            filtrare(&service);
            break;
        case 6:
            printOferte(&service);
            break;
        case 7:
            undo(&service);
            break;
        case 8:
			filtrarePret2(&service, 1500);
			break;
        case 0:
            destroy(&service);
            isrunning = 0;
            break;
        default:
            printf("Comanda invalida! Va rugam sa introduceti o comanda valida.\n");
            break;
        }
    }
}