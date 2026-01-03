#include <iostream>

#include "marked-files/marked-files.h"
#include "md5/md5.h"

int main() {
	marked_files::istream in { std::cin };
	int ch;
	for (;;) {
		md5::ostream out { std::cout };
		while ((ch = in.get()) >= 0) {
			out.put(ch);
		}
		if (auto command = in.read_next_command()) {
			if (command->name != "md5-digest") {
				log_fatal("Unbekanntes Kommando", command->name.c_str());
			}
			std::string digest { out.finish() };
			if (command->args != digest) {
				log_fatal("Falscher Digest", digest.c_str());
			}
		} else { break; }
	}
	return EXIT_SUCCESS;
}
