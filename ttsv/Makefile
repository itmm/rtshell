include ../Makefile.base

lib: libttsv.a

libttsv.a: ttsv.o
	@echo building $@
	@$(AR) -rc $@ $^

ttsv.o: ttsv.h ../log/log.h

test: libttsv.a
	@#$(MAKE) sub_test

clean:
	@rm -f libttsv.a ttsv.o
	@#$(MAKE) sub_test_clean
