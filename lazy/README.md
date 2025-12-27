# lazy Schreiben in Dateien

Die Bau-Umgebung ist in [build.md](build.md) beschrieben.

Die eigentliche Funktionalität ist in eine Bibliothek gepackt. Das eigentliche
Programm in `main.cpp` wird dadurch sehr übersichtlich:

```c++
#include "lazy.h"
#include "log/log.h"

int main(int argc, const char* argv[]) {
	try {
		if (argc != 2) { log_fatal("Syntax", "lazy <file path>"); }
		Lazy lazy { std::cin, argv[1] };
		lazy();
		return EXIT_SUCCESS;
	} catch (const terminate_exception& ex) {
		return EXIT_FAILURE;
	}
}
```

Der Header zur Bibliothek in `lazy.h` exportiert eine Klasse mit einer
öffentlichen Methode:

```c++
#if !defined(lazy_h)
#define lazy_h

	#include <iostream>
	#include <string>

	class Lazy {
		public:
			Lazy(std::istream& in, const std::string& out_path);
			void operator()();
	};

#endif
```

Übergeben werden im Konstruktor der Eingabestrom, aus dem die Eingaben gelesen
werden und der Pfad der Datei, in welche die Eingaben geschrieben werden
sollen.

Die eigentliche Methode führt mehrere Schritte aus, die als private
Methoden in `lazy.h` deklariert werden:

```c++
// ...
	class Lazy {
			bool open_file_();
			void match_prefix_();
			int next_ch_();
			void overwrite_rest_();
			void truncate_file_();
// ...
	};
// ...
```

In `lazy.cpp` werden die Schritte erst einmal leer implementiert:

```c++
#include "lazy.h"
#include "log/log.h"

Lazy::Lazy(std::istream& in, const std::string& out_path)
{ }

bool Lazy::open_file_() {
	return false;
}

int Lazy::next_ch_() {
	return EOF;
}

void Lazy::match_prefix_() {
}

void Lazy::overwrite_rest_() {
}

void Lazy::truncate_file_() {
}

void Lazy::operator()() {
	try {
		if (open_file_()) {
			match_prefix_();
		} else {
			next_ch_();
		}
		overwrite_rest_();
		truncate_file_();
	} catch (const std::ios_base::failure& ex) {
		log_fatal("Lazy Fehler", ex.what());
	}
}
```

Die Argumente des Konstruktors werden in Attributen gespeichert, damit die
Instanz-Methoden auf sie zugreifen können. Dazu definiere ich in `lazy.h`
die Attribute:

```c++
// ...
	class Lazy {
			std::istream& in_;
			const std::string out_path_;

// ...
	};
// ...
```

Und ich erweitere den Konstruktor in `lazy.cpp`, um die Attribute zu speichern:

```c++
// ...
Lazy::Lazy(std::istream& in, const std::string& out_path)
	: in_ { in }, out_path_ { out_path }
// ...
```

In `lazy.h`:

```c++
// ...

	#include <cstdint>
	#include <fstream>
// ...
	class Lazy {
			// ...
			const std::string out_path_;
			std::fstream out_;
			int ch_ { ' ' };
			std::uintmax_t offset_ { 0 };
// ...
	};
// ...
```

Aber dahinter verbergen sich in `lazy.cpp` mehrere Schritte:

```c++
// ...

#include <filesystem>

// ...
bool Lazy::open_file_() {
	if (std::filesystem::exists(out_path_)) {
		out_.open(out_path_.c_str(), std::ios_base::in | std::ios_base::out | std::ios_base::binary);
		out_.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		return true;
	} else {
		out_.open(out_path_.c_str(), std::ios_base::out | std::ios_base::binary);
		out_.exceptions(std::ios_base::failbit | std::ios_base::badbit);
		return false;
	}
	#if 0
// ...
	return false;
	#endif
// ...
}
// ...
int Lazy::next_ch_() {
	if (ch_ >= 0) {
		ch_ = in_.get();
	}
	return ch_;
	#if 0
// ...
	return EOF;
	#endif
// ...
}
// ...
void Lazy::match_prefix_() {
	for (;;) {
		ch_ = next_ch_();
		if (ch_ < 0) { break; }
		int should = out_.get();
		if (should != ch_) { break; }
		++offset_;
	}
// ...
}
// ...
void Lazy::overwrite_rest_() {
	out_.seekp(offset_);
	for (;;) {
		if (ch_ < 0) { break; }
		out_.put(ch_);
		++offset_;
		ch_ = next_ch_();
	}
// ...
}
// ...
void Lazy::truncate_file_() {
	out_.close();
	auto cur { std::filesystem::file_size(out_path_) };
	if (cur != offset_) {
		std::filesystem::resize_file(out_path_, offset_);
	}
// ...
}
// ...
```

