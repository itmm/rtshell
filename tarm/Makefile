include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib

test: tarm
	# done

tarm: tarm.o $(LIBS_O)

tarm.o: $(LIBS_H)

clean:
	$(RM) tarm tarm.o
