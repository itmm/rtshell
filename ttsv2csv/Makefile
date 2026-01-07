include ../Makefile.base
include ../log/Makefile.lib
include ../csv/Makefile.lib
include ../ttsv/Makefile.lib

test: ttsv2csv
	# done

ttsv2csv: ttsv2csv.o $(LIBS_O)

ttsv2csv.o: $(LIBS_H)

clean:
	$(RM) ttsv2csv ttsv2csv.o
