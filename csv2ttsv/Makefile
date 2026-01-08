include ../Makefile.base
include ../log/Makefile.lib
include ../csv/Makefile.lib
include ../ttsv/Makefile.lib

test: csv2ttsv
	# done

csv2ttsv: csv2ttsv.o $(LIBS)

include csv2ttsv.d

clean:
	$(RM) csv2ttsv csv2ttsv.o
