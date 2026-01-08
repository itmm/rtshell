include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib

test: tarm
	# done

tarm: tarm.o $(LIBS)

include tarm.d

clean:
	$(RM) tarm tarm.o
