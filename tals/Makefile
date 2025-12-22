include ../Makefile.base
include ../log/Makefile.lib

test: tals
	@#$(MAKE) sub_test

tals: tals.o ../log/liblog.a
	@echo building $@
	@$(CC) tals.o -L../log -llog -o $@

tals.o: ../log/log.h

clean:
	@rm -f tals tals.o
	@#$(MAKE) sub_test_clean
