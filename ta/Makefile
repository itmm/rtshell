include ../Makefile.base
include ../log/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib
include Makefile.lib

include ta.d

test: $(LIBS)
	# done

library: $(LIB)

$(LIB): $(LIB)(ta.o)

clean:
	$(RM) libta.a ta.o
