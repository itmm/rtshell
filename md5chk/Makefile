include ../Makefile.base
include ../md5/Makefile.lib
include ../marked-files/Makefile.lib
include ../log/Makefile.lib

test: md5chk
	@#$(MAKE) sub_test

md5chk: md5chk.o ../md5/libmd5.a ../marked-files/libmarked-files.a
	@echo building $@
	@$(CXX) md5chk.o -L../md5 -lmd5 -L../marked-files -lmarked-files -L../log -llog -o $@

md5chk.o: ../md5/md5.h ../marked-files/marked-files.h

clean:
	@rm -f md5chk md5chk.o .mdp_run
