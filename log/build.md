# Programm bauen

## Makefile

Im `./Makefile` werden die Grundlagen gelegt, um

```Makefile
GENERATED = Makefile inc.mk log.h log.cpp

include ../with-mdp.mk
include lib.mk

test: $(LIB)
    # done

include log.d

$(LIB): $(LIB)(log.o)

clean:
	$(RM) $(LIB) log.o
```

Es gibt ausnahmsweise keine Testfälle für das Loggen: da es ständig verwendet
wird, kann es en passant mitgetestet werden.


## Makefile.lib

Ich baue eine statische Bibliothek. Um in anderen Makefiles diese zu verwenden,
kann die Datei `lib.mk` eingebunden werden:

```Makefile
DIR = ../log
LIB = liblog.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/README.md
	$(MAKE) -C $(DIR) $(LIB)

LIBS += $(FULL_LIB)
```

