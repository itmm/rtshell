#line 4 "README.md"
#include "lazy.h"
#include "log/log.h"

int main(int argc, const char* argv[]) {
	if (argc != 2) { log_fatal("Syntax", "lazy <file path>"); }
	process_lazy(stdin, argv[1]);
	return 0;
}
