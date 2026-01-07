APP := lazy

include ../../Makefile.base

TESTS := test_no_output \
	test_change \
	test_increase \
	test_decrease \
	test_truncate \
	test_dont_modify \
	test_dont_modify_big \


.PHONY: $(TESTS)

test: $(TESTS)
	# ok

clean:
	$(RM) t e

test_no_output:
	$(RM) t
	cat /dev/null > e
	cat e | ../lazy t
	diff t e
	$(RM) t e

test_change:
	echo "abc" > t
	echo "xyz" > e
	cat e | ../lazy t
	diff t e
	$(RM) t e

test_increase:
	echo "abc" > t
	echo "abcdef" > e
	cat e | ../lazy t
	diff t e
	$(RM) t e

test_decrease:
	echo "abcdef" > t
	echo "abc" > e
	cat e | ../lazy t
	diff t e
	$(RM) t e

test_truncate:
	echo "abc" > t
	cat /dev/null > e
	cat e | ../lazy t
	diff t e
	$(RM) t e

test_dont_modify:
	cp old-file.txt e
	cat e | ../lazy old-file.txt
	[ old-file.txt -ot e ]
	$(RM) e

test_dont_modify_big:
	cp old-big.txt e
	cat e | ../lazy old-big.txt
	[ old-big.txt -ot e ]
	$(RM) e

