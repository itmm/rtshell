#include <iostream>

#include "csv/csv.h"
#include "ttsv/ttsv.h"

int main(void) {
	ttsv::istream in { std::cin };
	csv::ostream out { std::cout };

	for (;;) {
		char ch;
		while (in.get(ch)) { out.put(ch); }
		if (in.next_cell()) { out.close_cell(); continue; }
		out.close_line();
		if (in.next_line()) { continue; }
		break;
	}
	return EXIT_SUCCESS;
}
