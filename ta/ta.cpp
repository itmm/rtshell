#include "ta.h"


#include "log/log.h"

namespace ta {
	int Reader::get_ch_() {
		last_ = cur_; cur_ = next_;
		if (next_ >= 0) { next_ = in_.get(); }
		return cur_;
	}

	std::string Reader::read_command() {
		if (last_ != '\n' || cur_ != '%' || next_ == '%') {
			log_fatal("invalid ta command sequence", "");
		}
		get_ch_();
		std::string result;
		while (cur_ > ' ') { result += (char) cur_; get_ch_(); }
		return result;
	}

	bool Reader::open_next_file(std::string& name) {
		if (cur_ < 0) { return false; }
		auto command { read_command() };
		if (command != "file") {
			log_fatal("invalid ta command", command.c_str());
		}
		if (cur_ != ' ') {
			log_fatal("kein Name nach %file Kommando", "");
		}
		get_ch_();
		name.clear();
		while (cur_ >= ' ') { name += (char) cur_; get_ch_(); }
		get_ch_();

		return true;
	}

	int Reader::next_ch() {
		if (last_ == '\n' && cur_ == '%' && next_ != '%') {
			return EOF;
		}
		int result = cur_;
		if (last_ == '\n' && cur_ == '%' && next_ == '%') {
			get_ch_();
		}
		get_ch_();
		return result;
	}

	void Writer::put_ch(int ch) {
		if (ch < 0) { return; }
		if (ch == '%' && last_ == '\n') { out_.put(ch); }
		out_.put(ch);
		last_ = ch;
	}

	void Writer::open_next_file(const std::string& name) {
		static const std::string command { "%file " };
		if (last_ != '\n') { put_ch('\n'); }
		out_.write(command.c_str(), command.size());
		out_.write(name.c_str(), name.size());
		put_ch('\n');
	}
}
