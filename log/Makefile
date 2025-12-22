include ../Makefile.base
include Makefile.lib

lib: liblog.a

liblog.a: log.o
	@echo building $@
	@$(AR) -rc $@ $^

test: liblog.a
	@#$(MAKE) sub_test

clean:
	@rm -f liblog.a log.o
	@#$(MAKE) sub_test_clean
