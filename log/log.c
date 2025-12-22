#line 22 "README.md"
#include "log.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void log_fatal(const char* message, const char* reason) {
	if (! message) { message = "NULL"; }
	if (! reason) { reason = "NULL"; }
	fprintf(stderr, "%s: %s\n", message, reason);
	exit(10);
}

void log_fatal_errno(const char* message) {
	log_fatal(message, strerror(errno));
}
