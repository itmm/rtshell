#pragma once

#include <iostream>

namespace csv {

	class Reader {
			std::istream& in_;
			int ch_;

		public:
			static const char SEPARATOR = ',';

			Reader(std::istream& in): in_ { in }, ch_ { in_.get() } { }
			
			bool read_next_cell_in_line(std::string& value);
			bool goto_next_line();
	};

}
