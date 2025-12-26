#line 9 "README.md"
#include "lazy.h"
extern "C" {
	#include "log/log.h"
}

int main(int argc, const char* argv[]) {
	if (argc != 2) { log_fatal("Syntax", "lazy <file path>"); }
	process_lazy(std::cin, argv[1]);
	return 0;
}
