include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

include main.d

lazy: main.o $(LIBS)

test: lazy
	@$(MAKE) sub_test

clean:
	@rm -f lazy liblazy.a lazy.o main.o
	@$(MAKE) sub_test_clean
