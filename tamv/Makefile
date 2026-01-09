include ../base.mk
include ../log/lib.mk
include ../ta/lib.mk
include ../marked-files-in/lib.mk
include ../marked-files-out/lib.mk

test: tamv
	# done

tamv: tamv.o $(LIBS)

include tamv.d

clean:
	$(RM) tamv tamv.o
