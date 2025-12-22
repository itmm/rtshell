include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

lib: liblazy.a

liblazy.a: lazy.o
	@echo building $@
	@$(AR) -rc $@ $^

main.o: lazy.h ../log/log.h

lazy: main.o liblazy.a ../log/liblog.a
	@echo building $@
	@$(CC) main.o -L. -llazy -L../log -llog -o $@

test: lazy
	@$(MAKE) sub_test

clean:
	@rm -f lazy liblazy.a lazy.o main.o
	@$(MAKE) sub_test_clean
