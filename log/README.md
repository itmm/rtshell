# Ein einfaches Log-Konzept

## Wer soll sich um Log-Dateien kümmern?

Die Programme loggen alle über die Standard-Fehlerausgabe. Das System, welches
die Programme aufruft, muss sicherstellen, dass die Ausgabe in Dateien
archiviert wird. Und ebenso, dass diese Dateien nicht zu groß werden.


## Basisfunktion

Das Bauen des Programms ist in [build.md](build.md) beschrieben.

Im Header `log.h` wird zunächst die Basisfunktion definiert, um eine einzige
Nachricht zu loggen und das Programm zu beenden:

```c++
#if !defined(log_h)
#define log_h

	class terminate_exception { };

	void log_fatal(const char* message, const char* reason);

#endif
```

Eine Log-Nachricht besteht aus der eigentlichen Nachricht und einem Grund.
Fangen wir mit der Implementierung in `log.cpp` an. Beide Parameter können leer
bleiben, um die Funktion robuster zu machen:

```c++
#include "log.h"

void log_fatal(const char* message, const char* reason) {
	if (! message) { message = "NULL"; }
	if (! reason) { reason = "NULL"; }
}
```

Die Ausgabe erfolgt erst einmal ganz einfach über den Fehler-Kanal:

```c++
// ...

#include <iostream>

// ...
void log_fatal(const char* message, const char* reason) {
	// ...
	if (! reason) { reason = "NULL"; }
	std::cerr << message << ": " << reason << "\n";
// ...
}
// ...
```

Zusätzlich wird nach der Ausgabe das Programm beendet:

```c
// ...
void log_fatal(const char* message, const char* reason) {
	// ...
	std::cerr << message << ": " << reason << "\n";
	throw terminate_exception { };
// ...
}
// ...
```

Damit ist ein rudimentäres Logging umgesetzt.

