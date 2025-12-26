#pragma once

#include <iostream>
#include <string>

namespace ttsv {
	
	class Writer {
			std::ostream& out_;
			std::string cell_prefix_;

		public:
			Writer(std::ostream& out): out_ { out } { }
			void write_cell(const std::string& value);
			void close_line();
			
	};
		
};

