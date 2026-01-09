include ../base.mk
include ../md5/lib.mk
include ../marked-files-in/lib.mk
include ../log/lib.mk

test: md5chk
	# done

md5chk: md5chk.o $(LIBS)

include md5chk.d

clean:
	$(RM) md5chk md5chk.o .mdp_run
