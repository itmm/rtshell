#include <iostream>
#include <cstdint>

#include "log/log.h"
#include "ta/ta.h"

int main(int argc, const char* argv[]) {
	try {
		if (argc != 2) { log_fatal("Syntax", "tacat <archive path>"); }
		std::string search { argv[1] };
		ta::istream in { std::cin };
		while (auto name = in.open_next_file()) {
			int ch;
			if (*name == search) {
				while ((ch = in.get()) >= 0) { std::cout.put(ch); }
				return EXIT_SUCCESS;
			}
		}
	} catch (const terminate_exception&) { }
	return EXIT_FAILURE;
}
