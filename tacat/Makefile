include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib

test: tacat
	@#$(MAKE) sub_test

tacat: tacat.o ../ta/libta.a ../log/liblog.a
	@echo building $@
	@$(CXX) tacat.o -L../ta -lta -L../log -llog -o $@

tacat.o: ../ta/ta.h ../log/log.h

clean:
	@rm -f tacat tacat.o
	@#$(MAKE) sub_test_clean
