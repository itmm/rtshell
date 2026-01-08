include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

include ttsv.d

test: $(LIBS)
	# done

library: $(LIB)

$(LIB): $(LIB)(ttsv.o)

clean:
	$(RM) libttsv.a ttsv.o
