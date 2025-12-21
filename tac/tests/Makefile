TESTS := test_simple test_escaping test_cascading test_empty test_empty_files

.PHONY: all test $(TESTS) clean

all: test

test_simple:
	@echo "abc" > a
	@echo "def" > b
	@../tac a b > t
	@echo "%file a\nabc\n%file b\ndef" > e
	@diff t e
	@rm a b t e

test_escaping:
	@echo "%ab%c" > a
	@../tac a > t
	@echo "%file a\n%%ab%c" > e
	@diff t e
	@rm a t e

test_cascading:
	@echo "abc" > a
	@../tac a > tt
	@../tac tt > t
	@echo "%file tt\n%%file a\nabc" > e
	@diff t e
	@rm a t tt e

test_empty:
	@../tac > t
	@cat /dev/null > e
	@diff t e
	@rm t e

test: $(TESTS)
	@cat /dev/null > a
	@../tac a a > t
	@echo "%file a\n%file a" > e
	@diff t e
	@rm a t e

clean:
	@rm -f t e
