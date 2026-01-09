GENERATED := Makefile lib.mk lazy.h lazy.cpp
include ../with-mdp.mk
include ../log/lib.mk
include lib.mk

include main.d

lazy: main.o $(LIBS)

$(LIB): $(LIB)(lazy.o)

test: lazy
	$(MAKE) sub_test

clean:
	$(RM) lazy liblazy.a lazy.o main.o
	$(MAKE) sub_test_clean
