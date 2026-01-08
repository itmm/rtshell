include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

include main.d

lazy: main.o $(LIBS)

library: $(LIB)

$(LIB): $(LIB)(lazy.o)

test: lazy
	$(MAKE) sub_test

clean:
	$(RM) lazy liblazy.a lazy.o main.o
	$(MAKE) sub_test_clean
