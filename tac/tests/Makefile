APP := tac

include ../../Makefile.base

TESTS := test_simple test_escaping test_cascading test_empty test_empty_files

.PHONY: $(TESTS)

test_simple:
	echo "abc" > a
	echo "def" > b
	../tac a b > t
	echo "%file a\nabc\n%file b\ndef" > e
	diff t e
	$(RM) a b t e

test_escaping:
	echo "%ab%c" > a
	../tac a > t
	echo "%file a\n%%ab%c" > e
	diff t e
	$(RM) a t e

test_cascading:
	echo "abc" > a
	../tac a > tt
	../tac tt > t
	echo "%file tt\n%%file a\nabc" > e
	diff t e
	$(RM) a t tt e

test_empty:
	../tac > t
	cat /dev/null > e
	diff t e
	$(RM) t e

test_empty_files:
	cat /dev/null > a
	../tac a a > t
	echo "%file a\n%file a" > e
	diff t e
	$(RM) a t e

test: $(TESTS)
	# ok

clean:
	$(RM) t e
