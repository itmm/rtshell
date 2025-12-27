#include "csv.h"

#include "log/log.h"

namespace csv {

	bool Reader::read_next_cell_in_line(std::string& value) {
		if (ch_ < 0 || ch_ == '\n') { return false; }

		value.clear();
		bool quoting { false };
		for (;;) {
			if (ch_ == '"' && ! quoting) {
				quoting = true;
				ch_ = in_.get();
			}
			if (ch_ == '"' /* && state->quoting */) {
				ch_ = in_.get();
				if (ch_ >= 0 && ch_ != '"') { quoting = false; }
			}
			if (ch_ < 0) {
				if (quoting) { log_fatal("Offener CSV String", ""); }
				break;
			}
			if (! quoting) {
				if (ch_ == '\r') {
					ch_ = in_.get();
					if (ch_ != '\n') { log_fatal("Falsches Zeilenende", ""); }
				}
				if (ch_ < 0 || ch_ == '\n' || ch_ == SEPARATOR) { break; }
			}

			value.push_back(ch_);
			ch_ = in_.get();
		}
		if (ch_ == SEPARATOR) { ch_ = in_.get(); }
		return true;
	}

	bool Reader::goto_next_line() {
		while (ch_ != '\n' && ch_ >= 0) { ch_ = in_.get(); }
		if (ch_ == '\n') { ch_ = in_.get(); return true; }
		return false;
	}
}
