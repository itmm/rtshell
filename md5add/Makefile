include ../Makefile.base
include ../md5/Makefile.lib
include ../marked-files-out/Makefile.lib
include ../log/Makefile.lib

test: md5add
	# done

md5add: md5add.o $(LIBS)

include md5add.d

clean:
	$(RM) md5add md5add.o .mdp_run
