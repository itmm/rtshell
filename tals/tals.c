#include <stdbool.h>
#include <stdio.h>
#include "log/log.h"

int ch;

bool match(const char* p) {
	while (*p) {
		if (ch != *p) { return false; }
		++p;
		ch = getchar();
	}
	return true;
}

void list_file(void) {
	if (! match("file ")) { log_fatal("kein ta-Archiv", "Datei-Präfix"); }

	while (ch != EOF && ch != '\n') {
		putchar(ch); ch = getchar();
	}
	putchar(' ');

	if (ch != EOF) { ch = getchar(); }

	long size = 0;
	bool last_is_newline = true;

	for (;;) {
		while ((! last_is_newline || ch != '%') && ch != EOF) {
			last_is_newline = (ch == '\n');
			ch = getchar();
			++size;
		}
		
		if (ch == EOF) { break; }

		ch = getchar();
		if (ch != '%') { break; }
	}

	printf("%ld\n", size);
}

int main(void) {
	ch = getchar(); if (ch == EOF) { return 0; }
	if (ch != '%') { log_fatal("Kein ta-Archiv", "Header"); }
	ch = getchar();
	do {
		list_file();
	} while (ch != EOF);
	if (ferror(stdin)) { log_fatal_errno("Kann nicht lesen"); }
}
