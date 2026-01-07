include ../Makefile.base
include ../md5/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../log/Makefile.lib

test: md5chk
	# done

md5chk: md5chk.o $(LIBS_O)

md5chk.o: ../md5/md5.h $(LIBS_H)

clean:
	$(RM) md5chk md5chk.o .mdp_run
