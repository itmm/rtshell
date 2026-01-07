include ../Makefile.base
include ../log/Makefile.lib
include ../csv/Makefile.lib
include ../ttsv/Makefile.lib

test: csv2ttsv
	# done

csv2ttsv: csv2ttsv.o $(LIBS_O)

csv2ttsv.o: $(LIBS_H)

clean:
	$(RM) csv2ttsv csv2ttsv.o
