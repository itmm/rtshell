# Programm bauen

## Makefile

Im `./Makefile` werden die Grundlagen gelegt, um

```Makefile
include ../Makefile.base
include Makefile.lib

test: liblog.a
    # done

clean:
	$(RM) liblog.a log.o
```

Es gibt ausnahmsweise keine Testfälle für das Loggen: da es ständig verwendet
wird, kann es en passant mitgetestet werden.


## Makefile.lib

Ich baue eine statische Bibliothek. Um in anderen Makefiles diese zu verwenden,
kann die Datei `Makefile.lib` eingebunden werden:

```Makefile
vpath log.% ../log
vpath liblog.a ../log

liblog.a: log.o

include ../log/log.d

LIBS += liblog.a
```

