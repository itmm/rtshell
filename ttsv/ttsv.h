#pragma once

#include <iostream>
#include <string>

#include "log/log.h"

namespace ttsv {
	
	template<class CharT, class Traits = std::char_traits<char>>
	class basic_ostream:
		private std::basic_streambuf<CharT, Traits>,
		public std::basic_ostream<CharT, Traits>
	{
			std::basic_ostream<CharT, Traits>& forward_;

			Traits::int_type overflow(Traits::int_type ch) override {
				static const char* digits = "0123456789abcdef";

				if (Traits::eq_int_type(ch, Traits::eof())) { return ch; }
				CharT c = Traits::to_char_type(ch);

				if (c >= ' ' && c != '\\') {
					forward_.put(c);
				} else {
					forward_ << '\\' << digits[(c >> 4) & 0xf] << digits[c & 0xf];
				}
				return 0;
			}

		public:
			basic_ostream(std::basic_ostream<CharT, Traits>& forward):
				std::basic_ostream<CharT, Traits> { this }, forward_ { forward }
			{ }

			void close_cell() { forward_.put('\t'); }
			void close_line() { forward_.put('\n'); }
	};
		
	using ostream = basic_ostream<char>;

	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_istream:
		private std::basic_streambuf<CharT, Traits>,
		public std::basic_istream<CharT, Traits>
	{
			std::basic_istream<CharT, Traits>& source_;
			CharT ch_;
			bool eof_ { false };
			bool was_escaped_ { false };

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

			int digit() {
				if (ch_ >= '0' && ch_ <= '9') {
					return ch_ - '0';
				} else if (ch_ >= 'a' && ch_ <= 'f') {
					return ch_ + 10 - 'a';
				}
				log_fatal("falsche Sequenz", "");
				return 0;
			}

			Traits::int_type process_next_ch() {
				next_ch();
				if (eof_) { return Traits::eof(); }
				was_escaped_ = false;
				if (ch_ == '\\') {
					next_ch();
					if (eof_) { log_fatal("unvollständige Sequenz", ""); }
					int c = digit() << 4;
					next_ch();
					if (eof_) { log_fatal("unvollständige Sequenz", ""); }
					c += digit();
					ch_ = c;
					was_escaped_ = true;
				}
				if ((! was_escaped_) && (ch_ == '\t' || ch_ == '\n')) {
					return Traits::eof();
				}
				this->setg(&ch_, &ch_, &ch_ + 1);
				return Traits::to_int_type(ch_);
			}

			Traits::int_type underflow() override {
				if (eof_) { return Traits::eof(); }
				if ((! was_escaped_) && (ch_ == '\n' || ch_ == '\t')) {
					return Traits::eof();
				}
				return process_next_ch();
			}

		public:
			basic_istream(std::basic_istream<CharT, Traits>& source):
				std::basic_istream<CharT, Traits> { this }, source_ { source }
			{
				this->setg(&ch_, &ch_ + 1, &ch_ + 1);
			}


			bool next_cell() {
				while (this->get() >= 0) { }
				if (! eof_ && ch_ == '\t') {
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
};

