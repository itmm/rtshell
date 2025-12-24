#line 75 "README.md"
#include <fcntl.h>
#include <unistd.h>
#line 57
#include <stdio.h>

#line 35
#include "lazy.h"
#line 79
#include "log/log.h"
#line 61

struct State {
	FILE* in;
	int fd;
	long offset;
	char* cur;
	const char* end;
	int ch;
	char buffer[4096];
};
#line 84

#if _BSD_SOURCE || _XOPEN_SOURCE >= 500 || _XOPEN_VERSION >= 500 || \
    _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED || \
    /* Since glibc 2.3.5: */ _POSIX_C_SOURCE >= 200112L
#else
	int ftruncate(int fd, long length);
#endif

// -- POSIX Ein-/Ausgabe --

static inline int read_char(struct State* state) {
	if (! state->end) { return EOF; }
	if (state->cur >= state->end) {
		long got = read(state->fd, state->buffer, sizeof(state->buffer));
		if (got > 0) {
			state->cur = state->buffer;
			state->end = state->cur + got;
		} else {
			if (got < 0) { log_fatal_errno("Kann nicht lesen"); }
			state->end = NULL;
			return EOF;
		}
	}
	return *state->cur++;
}

// -- Eingabe ignorieren, solange sie passt --

static inline void match_prefix(struct State* state) {
	state->end = state->cur = state->buffer;

	for (;;) {
		state->ch = fgetc(state->in);
		if (state->ch == EOF) { break; }
		int should = read_char(state);
		if (should != state->ch) { break; }
		++state->offset;
	}
}


// -- Rest der Ausgabe in Datei schreiben --

static void write_buffer(struct State* state) {
	long size = state->cur - state->buffer;
	if (size > 0) {
		long written = write(state->fd, state->buffer, size);
		if (written != size) { log_fatal_errno("Kann nicht schreiben"); }
	}
	state->cur = state->buffer;
}

static inline void write_char(struct State* state) {
	if (state->cur >= state->end) { write_buffer(state); }
	*state->cur++ = state->ch;
	++state->offset;
}


static inline void overwrite_rest(struct State* state) {
	state->cur = state->buffer;
	state->end = state->buffer + sizeof(state->buffer);
	long pos = lseek(state->fd, state->offset, SEEK_SET);
	if (pos != state->offset) {
		log_fatal_errno("Kann Cursor nicht neu setzen");
	}
	for (;;) {
		if (state->ch == EOF) { break; }
		write_char(state);
		state->ch = fgetc(state->in);
	}
	write_buffer(state);
}


// -- Dateigröße auf geschriebene Daten reduzieren --

static inline void truncate_file(const struct State* state) {
	long size = lseek(state->fd, 0, SEEK_END);
	if (size < 0) { log_fatal_errno("Kann Dateiende nicht ermitteln"); }
	if (size != state->offset) {
		if (ftruncate(state->fd, state->offset) < 0) {
			log_fatal_errno("Kann Dateigröße nicht anpassen");
		}
	}
}

#line 36
#include "log/log.h"

void process_lazy(FILE* in, const char* out) {
	if (! in || ! out) { log_fatal("invalid arguments", "process_lazy"); }
#line 174
	// open output
	struct State state;
	state.fd  = open(out, O_RDWR | O_CREAT, 0660);
	if (state.fd < 0) { log_fatal_errno("Kann Datei nicht öffnen"); }
	state.in = in;
	state.offset = 0;
#line 181
	// match prefix
	match_prefix(&state);
#line 184
	// write rest into file
	if (state.ch != EOF) {
		overwrite_rest(&state);
	}

	if (ferror(state.in)) {
		close(state.fd);
		log_fatal_errno("Fehler beim Lesen");
		return;
	}

#line 196
	// trim file length
	truncate_file(&state);
#line 199
	// close output
	close(state.fd);
#line 40

    // open output
    // match prefix
    // write rest into file
    // trim file length
    // close output
}
