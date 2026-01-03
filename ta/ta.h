#pragma once

#include <iostream>
#include <optional>
#include <string>

#include "../log/log.h"
#include "../marked-files/marked-files.h"

namespace ta {
	
	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_istream: public marked_files::basic_istream<CharT, Traits> {
		public:
			basic_istream(std::basic_istream<CharT, Traits>& source):
				marked_files::basic_istream<CharT, Traits>(source)
			{ }

			std::optional<std::string> open_next_file() {
				if (auto command = this->read_next_command()) {
					if (command->name != "file") {
						log_fatal("unbekannter Befehl", command->name.c_str());
					}
					return command->args;
				}
				return { };
			}
	};

	using istream = basic_istream<char>;


	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_ostream: public marked_files::basic_ostream<CharT, Traits> {
		public:
			basic_ostream<CharT, Traits>(
				std::basic_ostream<CharT, Traits>& forward
			):
				marked_files::basic_ostream<CharT, Traits> { forward }
			{ }

			void open_next_file(const std::string& name) {
				this->send_command("file", name);
			}
	};

	using ostream = basic_ostream<char>;
};

