#include "ttsv.h"


#include "log/log.h"

namespace ttsv {
	void Writer::write_cell(const std::string& value) {
		static const char* digits = "0123456789abcdef";

		out_ << cell_prefix_; cell_prefix_ = "\t";
		for (char ch : value) {
			if (ch >= ' ') { out_.put(ch); continue; }
			out_.put('\\');
			out_.put(digits[(ch >> 4) & 0xf]);
			out_.put(digits[ch & 0xf]);
		}
	}

	void Writer::close_line() {
		out_.put('\n'); cell_prefix_.clear();
	}
}
