#include "domain.h"
#include "list.h"
#include <stdlib.h>
#define INIT_CAPACITY 2


List* createList(DestroyFunction destroyFn, CopyFunction copyFn) {
	List* list = (List*)malloc(sizeof(List));
	list->elements = (TElem*)malloc(sizeof(TElem) * INIT_CAPACITY);
	list->size = 0;
	list->capacity = INIT_CAPACITY;
	list->destroyElement = destroyFn;
	list->copyElement = copyFn;
	return list;
}

void destroyList(List* list) {
	if (list != NULL) {
		for (int i = 0; i < list->size; i++) {
			list->destroyElement(list->elements[i]);
		}
		free(list->elements);
		free(list);
	}
}
void resize(List* list) {
    int newCapacity = list->capacity * 2;
    TElem* newElements = (TElem*)malloc(sizeof(TElem) * newCapacity);
    for (int i = 0; i < list->size; i++) {
        newElements[i] = list->elements[i];
    }
    free(list->elements);
    list->elements = newElements;
    list->capacity = newCapacity;
}

void add(List* list, TElem elem) {
    if (list->size == list->capacity) {
        resize(list);
    }
    list->elements[list->size++] = elem;
}

List* copyList(List* list) {
    List* copy = (List*)malloc(sizeof(List));
    copy->elements = (TElem*)malloc(sizeof(TElem) * list->capacity);
    for (int i = 0; i < list->size; i++) {
        copy->elements[i] = list->copyElement(list->elements[i]);
        //copy->elements[i] = list->elements[i];
    }
    copy->size = list->size;
    copy->capacity = list->capacity;
    copy->destroyElement = list->destroyElement;
    copy->copyElement = list->copyElement;
    return copy;
}

void testList() {
    List* list = createList(distruge,copyOferta);
    
    add(list, CreeazaOferta(1, "casa", 100, "Tazlau", 50));
    add(list, CreeazaOferta(2, "casa", 100, "Tazlau", 50));
    add(list, CreeazaOferta(3, "casa", 100, "Tazlau", 50));
    // todo actually assert that the function does what it's supposed to
    List* list2 = copyList(list);
    destroyList(list2);
    destroyList(list);
}