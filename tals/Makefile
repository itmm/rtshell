include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib

test: tals
	# done

tals: tals.o $(LIBS)

include tals.d

clean:
	$(RM) tals tals.o
