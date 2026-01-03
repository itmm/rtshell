include ../Makefile.base
include ../log/Makefile.lib
include ../csv/Makefile.lib
include ../ttsv/Makefile.lib

test: ttsv2csv
	@# $(MAKE) sub_test

ttsv2csv: ttsv2csv.o ../log/liblog.a ../csv/libcsv.a ../ttsv/libttsv.a
	@echo building $@
	@$(CXX) ttsv2csv.o -L../csv -lcsv -L../ttsv -lttsv -L../log -llog -o $@

ttsv2csv.o: ../csv/csv.h ../ttsv/ttsv.h

clean:
	@rm -f ttsv2csv ttsv2csv.o
	@# $(MAKE) sub_test_clean
