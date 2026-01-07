include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../marked-files-out/Makefile.lib

test: tamv
	@#$(MAKE) sub_test

tamv: tamv.o $(LIBS_O)

tamv.o: $(LIBS_H)

clean:
	$(RM) tamv tamv.o
