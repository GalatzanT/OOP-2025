#pragma once
#include "repo.h"
#include "domain.h"
#include <stdlib.h>

typedef int (*CompareFct)(oferta* el1, oferta* el2);

// Sorts the list of offers
// l - the list of offers
// cmpF - the comparison function

void sort(Offer* l, CompareFct cmpF);