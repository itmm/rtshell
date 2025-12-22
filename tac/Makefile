include ../Makefile.base
include ../log/Makefile.lib

test: tac
	@$(MAKE) sub_test

tac: tac.o ../log/liblog.a
	@echo building $@
	@$(CC) tac.o -L../log -llog -o $@

tac.o: ../log/log.h

clean:
	@rm -f tac tac.o
	@$(MAKE) sub_test_clean
