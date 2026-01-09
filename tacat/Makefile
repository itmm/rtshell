include ../base.mk
include ../log/lib.mk
include ../ta/lib.mk
include ../marked-files-in/lib.mk
include ../marked-files-out/lib.mk

test: tacat
    # ok

tacat: tacat.o $(LIBS)

include tacat.d

clean:
	$(RM) tacat tacat.o
