#include <iostream>

#include "csv/csv.h"
#include "ttsv/ttsv.h"

int main(void) {
	csv::Reader reader { std::cin };
	ttsv::Writer writer { std::cout };

	std::string value;
	for (;;) {
		while (reader.read_next_cell_in_line(value)) {
			writer.write_cell(value);
		}
		writer.close_line();
		if (! reader.goto_next_line()) { break; }
	}
	return EXIT_SUCCESS;
}
