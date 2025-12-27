#include <iostream>
#include <cstdint>

#include "log/log.h"
#include "ta/ta.h"

int main(int argc, const char* argv[]) {
	try {
		if (argc != 2) { log_fatal("Syntax", "tacat <archive path>"); }
		std::string search { argv[1] };
		ta::Reader reader { std::cin };
		std::string name;
		while (reader.open_next_file(name)) {
			int ch;
			if (name == search) {
				while ((ch = reader.next_ch()) >= 0) { std::cout.put(ch); }
				return EXIT_SUCCESS;
			}
			while ((ch = reader.next_ch()) >= 0) { }
		}
	} catch (const terminate_exception&) { }
	return EXIT_FAILURE;
}
