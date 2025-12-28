#include "ttsv.h"


#include "log/log.h"

namespace ttsv {
	int ostream::overflow(int ch) {
		static const char* digits = "0123456789abcdef";

		if (ch >= ' ') {
			forward_.put(ch);
		} else {
			forward_ << '\\' << digits[(ch >> 4) & 0xf] << digits[ch & 0xf];
		}
		return 0;
	}

	void ostream::close_cell() { forward_.put('\t'); }

	void ostream::close_line() { forward_.put('\n'); }
}
