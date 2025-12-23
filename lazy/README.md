In `main.c`:

```c
#include "lazy.h"
#include "log/log.h"

int main(int argc, const char* argv[]) {
	if (argc != 2) { log_fatal("Syntax", "lazy <file path>"); }
	process_lazy(stdin, argv[1]);
	return 0;
}
```

In `lazy.h`:

```c
#if !defined(lazy_h)
#define lazy_h

	#include <stdio.h>

	void process_lazy(FILE* in, const char* out);

#endif
```

In `lazy.c`:

```c
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "lazy.h"
#include "log/log.h"

#if _BSD_SOURCE || _XOPEN_SOURCE >= 500 || _XOPEN_VERSION >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED || /* Since glibc 2.3.5: */ _POSIX_C_SOURCE >= 200112L
#else
	int ftruncate(int fd, long length);
#endif

struct State {
	FILE* in;
	int fd;
	long offset;
	char* cur;
	const char* end;
	int ch;
	char buffer[4096];
};

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

void process_lazy(FILE* in, const char* out) {
	if (! in || ! out) { log_fatal("invalid arguments", "process_lazy"); }

	struct State state;
	state.fd  = open(out, O_RDWR | O_CREAT, 0660);
	if (state.fd < 0) { log_fatal_errno("Kann Datei nicht öffnen"); }
	state.in = in;
	state.offset = 0;
	match_prefix(&state);
	if (state.ch != EOF) {
		overwrite_rest(&state);
	}
	truncate_file(&state);
	close(state.fd);

	if (ferror(state.in)) { log_fatal_errno("Fehler beim Lesen"); }
}
```

In `./Makefile`:

```Makefile
include ../Makefile.base
include ../log/Makefile.lib
include Makefile.deps

lib: liblazy.a

liblazy.a: ../lazy/lazy.o
	@echo building $@
	@$(AR) -rc $@ $^

main.o: ../lazy/lazy.h ../log/log.h

lazy: main.o liblazy.a ../log/liblog.a
	@echo building $@
	@$(CC) main.o -L. -llazy -L../log -llog -o $@

test: lazy
	@$(MAKE) sub_test

clean:
	@rm -f lazy liblazy.a lazy.o main.o
	@$(MAKE) sub_test_clean
```

In `Makefile.lib`:

```Makefile
include Makefile.deps

../lazy/liblazy.a: ../lazy/lazy.o
	@$(MAKE) --quite --directory=../lazy liblazy.a
```

In `Makefile.deps`:

```Makefile
../lazy/lazy.o: ../lazy/lazy.h ../log/log.h
```

## Tests

Die Test für `lazy` befinden sich im Ordner [tests](tests/).

