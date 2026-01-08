include ../Makefile.base
include ../md5/Makefile.lib
include ../marked-files-in/Makefile.lib
include ../log/Makefile.lib

test: md5chk
	# done

md5chk: md5chk.o $(LIBS)

include md5chk.d

clean:
	$(RM) md5chk md5chk.o .mdp_run
