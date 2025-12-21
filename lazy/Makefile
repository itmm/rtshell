include ../Makefile.base

lib: liblazy.a

liblazy.a: lazy.o
	@echo building $@
	@$(AR) -rc $@ $^

lazy: main.o liblazy.a
	@echo building $@
	@$(CC) $^ -o $@

test: lazy
	@$(MAKE) sub_test

clean:
	@rm -f lazy liblazy.a lazy.o main.o
	@$(MAKE) sub_test_clean
