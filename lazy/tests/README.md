# Tests von `lazy`

Die Tests werden im `./Makefile` durchgeführt. Hier erst mal den Rahmen mit
einem ersten Test. Wenn keine Daten gesendet werden, soll die Zieldatei auch
leer sein:

```Makefile
APP := lazy

include ../../Makefile.base

TESTS := test_no_output \


.PHONY: $(TESTS)

test: test_prefix $(TESTS)
	@echo ok

clean:
	@rm -f t e

test_no_output:
	@rm -f t
	@cat /dev/null > e
	@cat e | ../lazy t
	@diff t e
	@rm t e

```

## `test_change`


```Makefile
// ...
TESTS := test_no_output \
	test_change \
// ...
test_change:
	@echo "abc" > t
	@echo "xyz" > e
	@cat e | ../lazy t
	@diff t e
	@rm t e

```


## `test_increase`

```Makefile
// ...
	test_change \
	test_increase \
// ...
test_increase:
	@echo "abc" > t
	@echo "abcdef" > e
	@cat e | ../lazy t
	@diff t e
	@rm t e

```


## `test_decrease`

```Makefile
// ...
	test_increase \
	test_decrease \
// ...
test_decrease:
	@echo "abcdef" > t
	@echo "abc" > e
	@cat e | ../lazy t
	@diff t e
	@rm t e

```

## `test_truncate`

```Makefile
// ...
	test_decrease \
	test_truncate \
// ...
test_truncate:
	@echo "abc" > t
	@cat /dev/null > e
	@cat e | ../lazy t
	@diff t e
	@rm t e

```

## `test_dont_modify`

```Makefile
// ...
	test_truncate \
	test_dont_modify \
// ...
test_dont_modify:
	@cp old-file.txt e
	@cat e | ../lazy old-file.txt
	@[ old-file.txt -ot e ]
	@rm e

```

## `test_dont_modify_big`

```Makefile
// ...
	test_dont_modify \
	test_dont_modify_big \
// ...
test_dont_modify_big:
	@cp old-big.txt e
	@cat e | ../lazy old-big.txt
	@[ old-big.txt -ot e ]
	@rm e

```
