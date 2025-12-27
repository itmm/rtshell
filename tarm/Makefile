include ../Makefile.base
include ../log/Makefile.lib
include ../ta/Makefile.lib

test: tarm
	@#$(MAKE) sub_test

tarm: tarm.o ../ta/libta.a ../log/liblog.a
	@echo building $@
	@$(CXX) tarm.o -L../ta -lta -L../log -llog -o $@

tarm.o: ../ta/ta.h ../log/log.h

clean:
	@rm -f tarm tarm.o
	@#$(MAKE) sub_test_clean
