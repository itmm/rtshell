include ../Makefile.base
include ../log/Makefile.lib
include ../csv/Makefile.lib
include ../ttsv/Makefile.lib

test: csv2ttsv
	@# $(MAKE) sub_test

csv2ttsv: csv2ttsv.o ../log/liblog.a ../csv/libcsv.a ../ttsv/libttsv.a
	@echo building $@
	@$(CC) csv2ttsv.o -L../csv -lcsv -L../ttsv -lttsv -L../log -llog -o $@

csv2ttsv.o: ../csv/csv.h ../ttsv/ttsv.h

clean:
	@rm -f csv2ttsv csv2ttsv.o
	@# $(MAKE) sub_test_clean
