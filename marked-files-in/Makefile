include ../base.mk
include ../log/lib.mk
include lib.mk

test: $(LIBS)
	# done

$(LIB): $(LIB)(marked-files-in.o)

include marked-files-in.d

clean:
	$(RM) libmarked-files-in.a marked-files-in.o
