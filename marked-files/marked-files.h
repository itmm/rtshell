#pragma once

#include <iostream>
#include <optional>
#include <string>

#include "../log/log.h"

namespace marked_files {
	
	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_istream:
		private std::basic_streambuf<CharT, Traits>,
		public std::basic_istream<CharT, Traits>
	{
			std::basic_istream<CharT, Traits>& source_;
			char ch_ = '\n';
			bool in_command_ { false };

			Traits::int_type underflow() override {
				bool last_was_newline { ch_ == '\n' };
				if (in_command_ || ! source_.get(ch_)) { return Traits::eof(); }
				if (last_was_newline && ch_ == '%') {
					in_command_ = true;
					if ((! source_.get(ch_)) || ch_ != '%') {
						return Traits::eof();
					}
					in_command_ = false;
				}
				this->setg(&ch_, &ch_, &ch_ + 1);
				return Traits::to_int_type(0);
			}

		public:
			basic_istream(std::basic_istream<CharT, Traits>& source):
				std::basic_istream<CharT, Traits>(this),
				source_ { source }
			{
				this->setg(&ch_, &ch_ + 1, &ch_ + 1);
			}

			struct Command {
				std::string name;
				std::string args;

				Command(const std::string& name, const std::string& args):
					name { name }, args { args }
				{ }
			};

			std::optional<Command> read_next_command() {
				while (*this) { this->get(); }
				if (! in_command_) { return { }; }
				in_command_ = false;
				auto ch = ch_;
				this->clear();
				std::string line;
				if (! std::getline(*this, line)) { return { }; }
				line = ch + line;
				auto idx { line.find(' ') };
				if (idx != std::string::npos) {
					return Command { line.substr(0, idx), line.substr(idx + 1) };
				}
				return Command { line, std::string { } };
			}
	};

	using istream = basic_istream<char>;


	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_ostream:
		private std::basic_streambuf<CharT, Traits>,
		public std::basic_ostream<CharT, Traits>
	{
			std::basic_ostream<CharT, Traits>& forward_;
			CharT last_ = '\n';

			Traits::int_type overflow(Traits::int_type ch) override {
				if (Traits::eq_int_type(ch, Traits::eof())) { return ch; }
				CharT c { Traits::to_char_type(ch) };
				if (c == '%' && last_ == '\n') {
					if (! forward_.put(ch)) { return Traits::eof(); }
				}
				if (! forward_.put(c)) { return Traits::eof(); }
				last_ = c;
				return Traits::to_int_type(0);
			}

		public:
			basic_ostream<CharT, Traits>(
				std::basic_ostream<CharT, Traits>& forward
			):
				std::basic_ostream<CharT, Traits> { this }, forward_ { forward }
			{ }

			void send_command(const std::string& name, const std::string& args) {
				if (last_ != '\n') { this->put('\n'); }
				forward_ << '%' << name;
				if (! args.empty()) { forward_ << ' ' << args; }
				forward_ << '\n';
			}
	};

	using ostream = basic_ostream<char>;
};

