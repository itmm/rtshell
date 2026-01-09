include ../base.mk
include ../log/lib.mk
include ../csv/lib.mk
include ../ttsv/lib.mk

test: csv2ttsv
	# done

csv2ttsv: csv2ttsv.o $(LIBS)

include csv2ttsv.d

clean:
	$(RM) csv2ttsv csv2ttsv.o
