include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

t_md5: t_md5.o $(LIBS)

include md5.d
include t_md5.d

test: t_md5
	./t_md5

library: $(LIB)

$(LIB): $(LIB)(md5.o)

clean:
	$(RM) libmd5.a md5.o t_md5.o t_md5
