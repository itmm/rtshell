#pragma once

#include <iostream>

#include "log/log.h"

namespace csv {

	const char SEPARATOR = ',';

	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_ostream:
		private std::basic_streambuf<CharT, Traits>,
		public std::basic_ostream<CharT, Traits>
	{
			std::basic_ostream<CharT, Traits>& out_;
			std::string cell_;
			bool needs_escape_ { false };

			Traits::int_type overflow(Traits::int_type ch) override {
				CharT c { Traits::to_char_type(ch) };
				if (c == '"') { cell_ += '"'; }
				cell_ += c;
				if (c < ' ' || c == '"' || c == SEPARATOR) {
					needs_escape_ = true;
				}
				return 0;
			}

			void finish_cell() {
				if (needs_escape_) { out_.put('"'); }
				out_ << cell_;
				if (needs_escape_) { out_.put('"'); }
				cell_.clear();
				needs_escape_ = false;
			}

		public:
			explicit basic_ostream(std::basic_ostream<CharT, Traits>& out):
				std::basic_ostream<CharT, Traits>(this), out_ { out }
			{ }

			void close_cell() { finish_cell(); out_.put(SEPARATOR); }
			void close_line() { finish_cell(); out_ << "\r\n"; }
	};

	using ostream = basic_ostream<char>;

	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_istream:
		private std::basic_streambuf<CharT, Traits>,
		public std::basic_istream<CharT, Traits>
	{
			std::basic_istream<CharT, Traits>& source_;
			CharT ch_ = ' ';
			bool quoting_ { false };
			bool eof_ { false };

			void next_ch() {
				if (! eof_) {
					auto got { source_.get() };
					if (! Traits::eq_int_type(got, Traits::eof())) {
						ch_ = Traits::to_char_type(got);
					} else {
						eof_ = true;
					}
				}
			}

			Traits::int_type process_next_ch() {
				next_ch();

				if (ch_ == '"' && ! quoting_) {
					quoting_ = true;
					next_ch();
				}
				if (ch_ == '"' /* && quoting_ */) {
					next_ch();
					if (eof_  || ch_ != '"') { quoting_ = false; }
				}
				if (eof_) {
					if (quoting_) { log_fatal("Offener CSV String", ""); }
					return Traits::eof();
				} else if (! quoting_) {
					if (ch_ == '\r') {
						next_ch();
						if (ch_ != '\n') { log_fatal("Falsches Zeilenende", ""); }
					}
					if (eof_ || ch_ == '\n' || ch_ == SEPARATOR) {
						return Traits::eof();
					}
				}
				this->setg(&ch_, &ch_, &ch_ + 1);
				return Traits::to_int_type(ch_);
			}

			Traits::int_type underflow() override {
				if (eof_) { return Traits::eof(); }
				if (! quoting_ && (ch_ == '\n' || ch_ == SEPARATOR)) {
					return Traits::eof();
				}
				return process_next_ch();
			}

		public:
			basic_istream(std::istream& source):
				std::basic_istream<CharT, Traits> { this }, source_ { source }
			{
				this->setg(&ch_, &ch_ + 1, &ch_ + 1);
			}
			
			bool next_cell() {
				while (this->get() >= 0) { }
				if (! eof_ && ch_ == SEPARATOR) {
					if (process_next_ch() >= 0) {
						this->clear();
						return true;
					}
				}
				return false;
			}

			bool next_line() {
				while (next_cell()) { }
				if (! eof_ && ch_ == '\n') {
					if (process_next_ch() >= 0) {
						this->clear();
						return true;
					}
				}
				return false;
			}
	};

	using istream = basic_istream<char>;

}
