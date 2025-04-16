#pragma once

typedef struct {
	int id;
	char* tip;
	int suprafata;
	char* adresa;
	float pret;
}oferta;

/*
 Creeaza o oferta noua
 param id - id-ul ofertei
 param tip - tipul ofertei
 param suprafata - suprafata ofertei
 param adresa - adresa ofertei
 param pret - pretul ofertei
 return - pointer catre oferta creata
*/

oferta* CreeazaOferta(int id,char* tip, int suprafata, char* adresa, float pret);

/*
	Verifica daca oferta facuta este valida
	param o - oferta

	return - 1 daca oferta este valida, 0 altfel
*/

int valideaza(oferta* o);

/*
	Distruge o oferta
	param o - oferta
*/

void distruge(oferta* o);

/*
	Returneaza id-ul unei oferte
	param o - oferta
	return - id-ul ofertei
*/

int getId(oferta*);

/*
	Returneaza pretul unei oferte
	param o - oferta
	return - pretul ofertei
*/

float getPret(oferta*);

/*
	Seteaza id-ul unei oferte
	param o - oferta
	param id - id-ul ofertei
*/

void setId(oferta*,int);

/*
	Seteaza pretul unei oferte
	param o - oferta
	param pret - pretul ofertei
*/

void setPret(oferta*,float);

/*
	Copiaza o oferta
	param o - oferta
	return - copia ofertei
*/

oferta* copyOferta(oferta*);
