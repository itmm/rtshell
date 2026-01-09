include ../base.mk
include ../log/lib.mk
include ../marked-files-in/lib.mk
include ../marked-files-out/lib.mk
include lib.mk

include ta.d

test: $(LIBS)
	# done

$(LIB): $(LIB)(ta.o)

clean:
	$(RM) libta.a ta.o
