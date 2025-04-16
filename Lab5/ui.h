#pragma once
#include "service.h"
#include "repo.h"
#include "domain.h"

void run();
void printMeniu();
void printOferte(Service* service);
void modOferta(Service* service);
void citOferta(Service* service);
void destroy(Service* service);
void sortare(Service* service);
void filtrare(Service* service);