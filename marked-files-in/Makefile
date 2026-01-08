include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

test: $(LIBS)
	# done

library: $(LIB)

$(LIB): $(LIB)(marked-files-in.o)

include marked-files-in.d

clean:
	$(RM) libmarked-files-in.a marked-files-in.o
