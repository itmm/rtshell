#include <iostream>
#include <cstdint>

#include "log/log.h"

static int ch;

static inline bool match(const char* p) {
	while (*p) {
		if (ch != *p) { return false; }
		++p;
		ch = std::cin.get();
	}
	return true;
}

static inline void list_file(void) {
	if (! match("file ")) { log_fatal("kein ta-Archiv", "Datei-Präfix"); }

	while (ch >= 0 && ch != '\n') {
		std::cout.put(ch); ch = std::cin.get();
	}
	std::cout.put(' ');

	if (ch == '\n') { ch = std::cin.get(); }

	std::uintmax_t size = 0;
	bool last_is_newline = true;

	for (;;) {
		while ((! last_is_newline || ch != '%') && ch >= 0) {
			last_is_newline = (ch == '\n');
			ch = std::cin.get();
			++size;
		}
		
		if (ch < 0) { break; }

		ch = std::cin.get();
		if (ch != '%') { break; }
	}

	std::cout << size << '\n';
}

int main(void) {
	try {
		ch = std::cin.get(); if (ch < 0) { return EXIT_SUCCESS; }
		if (ch != '%') { log_fatal("Kein ta-Archiv", "Header"); }
		ch = std::cin.get();
		do {
			list_file();
		} while (ch >= 0);
		return EXIT_SUCCESS;
	} catch (const terminate_exception&) {
		return EXIT_FAILURE;
	}
}
