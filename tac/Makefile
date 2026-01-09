include ../base.mk
include ../log/lib.mk
include ../ta/lib.mk
include ../marked-files-in/lib.mk
include ../marked-files-out/lib.mk

test: tac
	$(MAKE) sub_test

include tac.d

tac: tac.o $(LIBS)

clean:
	$(RM) tac tac.o .mdp_run
	$(MAKE) sub_test_clean
