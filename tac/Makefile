include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib

test: tac
	$(MAKE) sub_test

tac: tac.o $(LIBS_O)

tac.o: $(LIBS_H)

clean:
	$(RM) tac tac.o .mdp_run
	$(MAKE) sub_test_clean
