include ../Makefile.base
include Makefile.lib

lib: libcsv.a

libcsv.a: csv.o
	@echo building $@
	@$(AR) -rc $@ $^

test: libcsv.a
	@#$(MAKE) sub_test

clean:
	@rm -f libcsv.a csv.o
	@#$(MAKE) sub_test_clean
