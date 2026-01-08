include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib

test: tamv
	# done

tamv: tamv.o $(LIBS)

include tamv.d

clean:
	$(RM) tamv tamv.o
