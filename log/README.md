# Ein einfaches Log-Konzept

## Wer soll sich um Log-Dateien kümmern?

## Einfaches Interface

Header in `log.h`:

```c
#if !defined(log_h)
#define log_h

	void log_fatal(const char* message, const char* reason);
	void log_fatal_errno(const char* message);

#endif
```

Source in `log.c`:

```c
#include "log.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_fatal(const char* message, const char* reason) {
	if (! message) { message = "NULL"; }
	if (! reason) { reason = "NULL"; }
	fprintf(stderr, "%s: %s\n", message, reason);
	exit(10);
}

void log_fatal_errno(const char* message) {
	log_fatal(message, strerror(errno));
}
```

In `./Makefile`:

```Makefile
include ../Makefile.base
include Makefile.deps

lib: ../log/liblog.a

../log/liblog.a: ../log/log.o
	@echo building $@
	@$(AR) -rc $@ $^

test: ../log/liblog.a
	@#$(MAKE) sub_test

clean:
	@rm -f liblog.a log.o
	@#$(MAKE) sub_test_clean
```

Und `Makefile.lib`:

```Makefile
../log/liblog.a: ../log/log.o
	$(MAKE) --quiet --directory=../log liblog.a

include Makefile.deps
```

Und `Makefile.deps`:

```Makefile
../log/log.o: ../log/log.h
```
