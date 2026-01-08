include ../Makefile.base
include Makefile.lib

test: $(LIB)
    # done

include log.d

library: $(LIB)

$(LIB): $(LIB)(log.o)

clean:
	$(RM) $(LIB) log.o
