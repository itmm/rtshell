#include <stdlib.h>
#include "lazy.h"

int main(int argc, const char* argv[]) {
	if (argc != 2) { fprintf(stderr, "Syntax lazy <file path>\n"); exit(10); }
	process_lazy(stdin, argv[1]);
	return 0;
}
