include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib

test: tacat
    # ok

tacat: tacat.o $(LIBS)

include tacat.d

clean:
	$(RM) tacat tacat.o
