include ../Makefile.base
include Makefile.lib

libmd5.a: md5.o
	@echo building $@
	@$(AR) -rc $@ $^

t_md5.o: ../md5/md5.h

t_md5: t_md5.o ../md5/libmd5.a
	@echo building $@
	@$(CXX) t_md5.o -L../md5 -lmd5 -L../log -llog -o $@

test: t_md5
	@echo "testing md5 ... \c"
	@./t_md5
	@echo "ok"

clean:
	@rm -f libmd5.a md5.o t_md5.o t_md5
