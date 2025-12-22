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
