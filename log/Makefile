GENERATED = Makefile lib.mk log.h log.cpp

include ../with-mdp.mk
include lib.mk

test: $(LIB)
    # done

include log.d

$(LIB): $(LIB)(log.o)

clean:
	$(RM) $(LIB) log.o
