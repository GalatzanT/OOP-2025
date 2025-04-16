#pragma once

typedef void* TElem;
typedef void (*DestroyFunction)(TElem);
typedef TElem(*CopyFunction)(TElem);

typedef struct {
	TElem* elements;
	int size;
	int capacity;
	DestroyFunction destroyElement;
	CopyFunction copyElement;
} List;

List* createList(DestroyFunction destroyFn, CopyFunction copyFn);

void destroyList(List* list);

void add(List* list, TElem elem);

List* copyList(List* list);

void testList();
