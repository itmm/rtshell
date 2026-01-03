include ../Makefile.base
include Makefile.deps

../marked-files/libmarked-files.a: ../marked-files/marked-files.o
	@echo building $@
	@$(AR) -rc $@ $^

test: ../marked-files/libmarked-files.a
	@#$(MAKE) sub_test

clean:
	@rm -f libmarked-files.a marked-files.o
	@#$(MAKE) sub_test_clean
