include ../base.mk
include ../log/lib.mk
include ../ta/lib.mk
include ../marked-files-in/lib.mk
include ../marked-files-out/lib.mk

test: tarm
	# done

tarm: tarm.o $(LIBS)

include tarm.d

clean:
	$(RM) tarm tarm.o
