include ../base.mk
include ../log/lib.mk
include ../csv/lib.mk
include ../ttsv/lib.mk

test: ttsv2csv
	# done

ttsv2csv: ttsv2csv.o $(LIBS)

include ttsv2csv.d

clean:
	$(RM) ttsv2csv ttsv2csv.o
