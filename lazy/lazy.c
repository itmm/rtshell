#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "lazy.h"

// -- Logging --

static void log_fatal(const char* message, const char* reason) {
	if (! message) { message = "NULL"; }
	if (! reason) { reason = "NULL"; }
	fprintf(stderr, "%s: %s\n", message, reason);
	exit(10);
}

static void log_fatal_errno(const char* message) {
	log_fatal(message, strerror(errno));
}


// -- POSIX Ein-/Ausgabe --

static int fd = -1;

static char buffer[4096];
static char* cur = buffer;
static const char* end = buffer + sizeof(buffer);

static inline int read_char(void) {
	if (! end) { return EOF; }
	if (cur >= end) {
		off_t got = read(fd, buffer, sizeof(buffer));
		if (got > 0) {
			cur = buffer;
			end = cur + got;
		} else {
			if (got < 0) { log_fatal_errno("Kann nicht lesen"); }
			end = NULL;
			return EOF;
		}
	}
	return *cur++;
}

static void write_buffer(void) {
	off_t size = cur - buffer;
	if (size > 0) {
		off_t got = write(fd, buffer, size);
		if (got != size) { log_fatal_errno("Kann nicht schreiben"); }
	}
	cur = buffer;
}

static inline void write_char(int ch) {
	if (cur >= end) { write_buffer(); }
	*cur++ = ch;
}


// -- Eingabe ignorieren, solange sie passt --

static int got = ' ';

static inline off_t match_prefix(void) {
	off_t offset = 0;
	end = cur = buffer;

	for (;;) {
		got = getchar();
		if (got == EOF) { break; }
		int should = read_char();
		if (should != got) { break; }
		++offset;
	}
	return offset;
}


// -- Rest der Ausgabe in Datei schreiben --

static inline off_t overwrite_rest(off_t offset) {
	cur = buffer; end = buffer + sizeof(buffer);
	off_t pos = lseek(fd, offset, SEEK_SET);
	if (pos != offset) { log_fatal_errno("Kann Cursor nicht neu setzen"); }
	for (;;) {
		if (got == EOF) { break; }
		write_char(got);
		++offset;
		got = getchar();
	}
	write_buffer();
	return offset;
}


// -- Dateigröße auf geschriebene Daten reduzieren --

static inline void truncate_file(off_t length) {
	off_t s = lseek(fd, 0, SEEK_END);
	if (s < 0) { log_fatal_errno("Kann Dateiende nicht ermitteln"); }
	if (s != length) {
		if (ftruncate(fd, length) < 0) {
			log_fatal_errno("Kann Dateigröße nicht anpassen");
		}
	}
}

void process_lazy(FILE* in, const char* out) {
	fd  = open(out, O_RDWR | O_CREAT, 0660);
	if (fd < 0) { log_fatal_errno("Kann Datei nicht öffnen"); }
	off_t offset = match_prefix();
	if (got != EOF) {
		offset = overwrite_rest(offset);
	}
	truncate_file(offset);
	close(fd);
}
