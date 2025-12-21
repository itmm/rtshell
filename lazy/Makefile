.PHONY: all test clean

CFLAGS += -Wall -pedantic -Werror

all: test

test: lazy
	@$(MAKE) --directory=tests test

clean:
	@rm -f lazy
	@$(MAKE) --directory=tests clean
