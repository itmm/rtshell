include ../Makefile.base
include Makefile.lib

lib: libttsv.a

libttsv.a: ttsv.o
	@echo building $@
	@$(AR) -rc $@ $^

test: libttsv.a
	@#$(MAKE) sub_test

clean:
	@rm -f libttsv.a ttsv.o
	@#$(MAKE) sub_test_clean
