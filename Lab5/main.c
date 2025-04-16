#include <stdio.h>
#include <crtdbg.h>
#include "ui.h"
#include "tests.h"

int main() {
	run_all_tests();
	run();
	if (_CrtDumpMemoryLeaks()) {
		printf("Memory leaks found!\n");
	}
	else {
		printf("No memory leaks found!\n");
	return 0;
	}
}