# Programm bauen

## Makefile

Im `./Makefile` werden die Grundlagen gelegt, um

```Makefile
include ../Makefile.base
include Makefile.lib

test: $(LIB)
    # done

include log.d

library: $(LIB)

$(LIB): $(LIB)(log.o)

clean:
	$(RM) $(LIB) log.o
```

Es gibt ausnahmsweise keine Testfälle für das Loggen: da es ständig verwendet
wird, kann es en passant mitgetestet werden.


## Makefile.lib

Ich baue eine statische Bibliothek. Um in anderen Makefiles diese zu verwenden,
kann die Datei `Makefile.lib` eingebunden werden:

```Makefile
DIR = ../log
LIB = liblog.a
FULL_LIB = $(DIR)/$(LIB)

$(FULL_LIB): $(DIR)/README.md
	$(MAKE) -C $(DIR) lib

LIBS += $(FULL_LIB)
```

