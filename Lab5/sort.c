#include <stdlib.h>
#include "sort.h"
#include"service.h"
#include "string.h"
#include "repo.h"

void sort(Offer* l, CompareFct cmpF) {
	int i, j;
	for ( i = 0; i < l->dimensiune - 1; i++) {
		for (j = i + 1; j < l->dimensiune; j++) {
			if (cmpF(l->oferte[i], l->oferte[j]) > 0) {
				ElemType tmp = l->oferte[i];
				l->oferte[i] = l->oferte[j];
				l->oferte[j] = tmp;
			}
		}
	}
}