include ../base.mk
include ../log/lib.mk
include ../ta/lib.mk
include ../marked-files-in/lib.mk
include ../marked-files-out/lib.mk

test: tals
	# done

tals: tals.o $(LIBS)

include tals.d

clean:
	$(RM) tals tals.o
