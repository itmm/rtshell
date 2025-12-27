#line 33 "README.md"
#include "log.h"

#line 46
#include <iostream>

#line 35
void log_fatal(const char* message, const char* reason) {
	if (! message) { message = "NULL"; }
	if (! reason) { reason = "NULL"; }
#line 52
	std::cerr << message << ": " << reason << "\n";
#line 65
	throw terminate_exception { };
#line 38
}
