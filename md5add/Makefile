include ../base.mk
include ../md5/lib.mk
include ../marked-files-out/lib.mk
include ../log/lib.mk

test: md5add
	# done

md5add: md5add.o $(LIBS)

include md5add.d

clean:
	$(RM) md5add md5add.o .mdp_run
