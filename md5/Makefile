include ../base.mk
include ../log/lib.mk
include lib.mk

t_md5: t_md5.o $(LIBS)

include md5.d
include t_md5.d

test: t_md5
	./t_md5

$(LIB): $(LIB)(md5.o)

clean:
	$(RM) libmd5.a md5.o t_md5.o t_md5
