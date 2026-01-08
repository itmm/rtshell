In `./Makefile`:

```Makefile
include ../Makefile.base
include ../log/Makefile.lib
include Makefile.lib

include main.d

lazy: main.o $(LIBS)

library: $(LIB)

$(LIB): $(LIB)(lazy.o)

test: lazy
	$(MAKE) sub_test

clean:
	$(RM) lazy liblazy.a lazy.o main.o
	$(MAKE) sub_test_clean
```

In `Makefile.lib`:

```Makefile
DIR = ../lazy
LIB = liblazy.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/README.md
	$(MAKE) -C $(DIR) lib

LIBS += $(FULL_LIB)
```

