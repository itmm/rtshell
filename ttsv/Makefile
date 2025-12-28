include ../Makefile.base
include Makefile.lib

libttsv.a: ttsv.o
	@echo building $@
	@$(AR) -rc $@ $^

ttsv.o: ../ttsv/ttsv.h

test: libttsv.a
	@#$(MAKE) sub_test

clean:
	@rm -f libttsv.a ttsv.o
	@#$(MAKE) sub_test_clean
