include ../Makefile.base

test: tac
	@$(MAKE) sub_test

tac: tac.o log_lib
	@echo building $@
	@$(CC) tac.o -L../log -llog -o $@

clean:
	@rm -f tac tac.o
	@$(MAKE) sub_test_clean
