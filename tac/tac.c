#include <stdbool.h>
#include <stdio.h>
#include "log/log.h"

static inline void process(const char* path) {
	printf("%%file %s\n", path);
	FILE *f = fopen(path, "r");
	if (! f) { log_fatal_errno("Kann Datei nicht öffnen"); }

	bool last_is_newline = true;
	int ch;
	while ((ch = fgetc(f)) != EOF) {
		if (last_is_newline) {
			if (ch == '%') { putchar(ch); }
		}
		putchar(ch);
		last_is_newline = (ch == '\n');
	}
	if (ferror(f)) { log_fatal_errno("Kann Datei nicht lesen"); }
	if (! last_is_newline) { putchar('\n'); }

	fclose(f);
}

int main(int argc, const char *argv[]) {
	const char** path = argv + 1;
	for (int i = argc - 1; i; --i) {
		process(*path++);
	}
}
