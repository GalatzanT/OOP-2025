#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domain.h"

oferta* CreeazaOferta(int id, char* tip, int suprafata, char* adresa, float pret) {
    oferta* p = (oferta*)malloc(sizeof(oferta));
    

    p->id = id;

    int nr = (int)strlen(tip) + 1;
    p->tip = (char*)malloc(sizeof(char) * nr);
    
    strcpy(p->tip, tip);

    p->suprafata = suprafata;

    nr = (int)strlen(adresa) + 1;
    p->adresa = (char*)malloc(sizeof(char) * nr);
    
    strcpy(p->adresa, adresa);

    p->pret = pret;

    return p;
}

int valideaza(oferta* o) {
    char tip_v[20];
    strcpy(tip_v, o->tip);
    if ((strcmp(tip_v, "teren") != 0) && (strcmp(tip_v, "casa") != 0) && (strcmp(tip_v, "apartament") != 0))
        return 0;
    if (strlen(o->adresa) == 0)
        return 0;
    if (o->suprafata < 0)
        return 0;
    if (o->pret < 0)
        return 0;
    if (o->id <= 0)
        return 0;
    return 1;
}

void distruge(oferta* o)
{
    if (o != NULL) {
        free(o->tip);
        free(o->adresa);
        free(o);
    }
}

int getId(oferta* o) {
    if (o == NULL) {
        return -1; 
    }
    return o->id;
}

float getPret(oferta* o) {
    if (o == NULL) {
        return -1.0f; 
    }
    return o->pret;
}

void setId(oferta* o, int id_nou) {
    if (o != NULL) {
        o->id = id_nou;
    }
}

void setPret(oferta* o, float pret_nou) {
    if (o != NULL) {
        o->pret = pret_nou;
    }
}
oferta* copyOferta(oferta* o) {
    

    oferta* p = (oferta*)malloc(sizeof(oferta));
    

    p->id = o->id;
    p->tip = (char*)malloc(sizeof(char) * (strlen(o->tip) + 1));
    
    strcpy(p->tip, o->tip);

    p->adresa = (char*)malloc(sizeof(char) * (strlen(o->adresa) + 1));
    
    strcpy(p->adresa, o->adresa);

    p->suprafata = o->suprafata;
    p->pret = o->pret;

    return p;
}