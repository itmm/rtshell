#line 9 "README.md"
#include "lazy.h"
#include "log/log.h"

int main(int argc, const char* argv[]) {
	try {
		if (argc != 2) { log_fatal("Syntax", "lazy <file path>"); }
		Lazy lazy { std::cin, argv[1] };
		lazy();
		return EXIT_SUCCESS;
	} catch (const terminate_exception& ex) {
		return EXIT_FAILURE;
	}
}
