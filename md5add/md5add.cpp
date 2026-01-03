#include <iostream>

#include "marked-files/marked-files.h"
#include "md5/md5.h"

int main() {
	marked_files::ostream escaper { std::cout };
	md5::ostream out { escaper };
	int ch;
	while ((ch = std::cin.get()) >= 0) {
		out.put(ch);
	}
	auto digest { out.finish() };
	escaper.send_command("md5-digest", digest);
}
