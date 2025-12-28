#include <iostream>

#include "csv/csv.h"
#include "ttsv/ttsv.h"

int main(void) {
	csv::Reader reader { std::cin };
	ttsv::ostream out { std::cout };

	std::string value;
	for (;;) {
		while (reader.read_next_cell_in_line(value)) {
			out << value; out.close_cell();
		}
		out.close_line();
		if (! reader.goto_next_line()) { break; }
	}
	return EXIT_SUCCESS;
}
