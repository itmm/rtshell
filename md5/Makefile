include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

t_md5.o: $(LIBS_H)

t_md5: t_md5.o $(LIBS_O)

test: t_md5
	./t_md5

clean:
	$(RM) libmd5.a md5.o t_md5.o t_md5
