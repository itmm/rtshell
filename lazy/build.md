In `./Makefile`:

```Makefile
GENERATED := Makefile lib.mk lazy.h lazy.cpp
include ../with-mdp.mk
include ../log/lib.mk
include lib.mk

include main.d

lazy: main.o $(LIBS)

$(LIB): $(LIB)(lazy.o)

test: lazy
	$(MAKE) sub_test

clean:
	$(RM) lazy liblazy.a lazy.o main.o
	$(MAKE) sub_test_clean
```

In `lib.mk`:

```Makefile
DIR = ../lazy
LIB = liblazy.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/README.md
	$(MAKE) -C $(DIR) $(LIB)

LIBS += $(FULL_LIB)
```

