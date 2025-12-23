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

