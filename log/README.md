# Ein einfaches Log-Konzept

## Wer soll sich um Log-Dateien kümmern?

Die Programme loggen alle über die Standard-Fehlerausgabe. Das System, welches
die Programme aufruft, muss sicherstellen, dass die Ausgabe in Dateien
archiviert wird. Und ebenso, dass diese Dateien nicht zu groß werden.


## Basisfunktion

Im Header `log.h` wird zunächst die Basisfunktion definiert, um eine einzige
Nachricht zu loggen und das Programm zu beenden:

```c
#if !defined(log_h)
#define log_h

	void log_fatal(const char* message, const char* reason);

#endif
```

Eine Log-Nachricht besteht aus der eigentlichen Nachricht und einem Grund.
Fangen wir mit der Implementierung in `log.c` an. Beide Parameter können leer
bleiben, um die Funktion robuster zu machen:

```c
#include "log.h"

void log_fatal(const char* message, const char* reason) {
	if (! message) { message = "NULL"; }
	if (! reason) { reason = "NULL"; }
}
```

Die Ausgabe erfolgt erst einmal ganz einfach über den Fehler-Kanal:

```c
// ...

#include <stdio.h>

// ...
void log_fatal(const char* message, const char* reason) {
	// ...
	if (! reason) { reason = "NULL"; }
	fprintf(stderr, "%s: %s\n", message, reason);
// ...
}
// ...
```

Zusätzlich wird nach der Ausgabe das Programm beendet:

```c
// ...
#include <stdio.h>
#include <stdlib.h>
// ...
void log_fatal(const char* message, const char* reason) {
	// ...
	fprintf(stderr, "%s: %s\n", message, reason);
	exit(EXIT_FAILURE);
// ...
}
// ...
```

Damit ist ein rudimentäres Logging umgesetzt.


## Systemfehler loggen

Oft liefern Systemfunktionen bei einem Fehler eine spezifische Fehlernummer
in der globalen Variable `errno`. Diese kann für die Angabe eines Grundes
herangezogen werden.

Daher kommt eine weitere Funktion in `log.h` hinzu:

```c
// ...
	void log_fatal(const char* message, const char* reason);
	void log_fatal_errno(const char* message);
// ...
```

In `log.c` kann diese hinzugezogen werden, um die Begründung zu liefern.

```c
// ...

#include <errno.h>
// ...
#include <stdlib.h>
#include <string.h>
// ...2

void log_fatal_errno(const char* message) {
	log_fatal(message, strerror(errno));
}
```


## Programm bauen

### Makefile

Im `./Makefile` werden die Grundlagen gelegt, um

```Makefile
include ../Makefile.base
include Makefile.deps

../log/liblog.a: ../log/log.o
	@echo building $@
	@$(AR) -rc $@ $^

test: ../log/liblog.a

clean:
	@rm -f liblog.a log.o
```

Es gibt ausnahmsweise keine Testfälle für das Loggen: da es ständig verwendet
wird, kann es en passant mitgetestet werden.


### Makefile.lib

Ich baue eine statische Bibliothek. Um in anderen Makefiles diese zu verwenden,
kann die Datei `Makefile.lib` eingebunden werden:

```Makefile
../log/liblog.a: ../log/log.o
	$(MAKE) --directory=../log liblog.a

include ../log/Makefile.deps
```


### Makefile.deps

In der Datei `Makefile.deps` werden die Abhängigkeiten verwaltet. Da diese
sowohl vom `Makefile`, als auch in `Makefile.lib` verwendet wird, muss
`Makefile.deps` die Pfade über das Modul-Verzeichnis auflösen.

```Makefile
../log/log.o: ../log/log.h
```
