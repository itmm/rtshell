#pragma once

#include <iostream>
#include <string>

namespace ta {
	
	class Reader {
			std::istream& in_;
			int cur_ = '\n';
			int next_ = '\n';
			int last_ = '\n';

			int get_ch_();
			std::string read_command();

		public:
			Reader(std::istream& in): in_ { in } { get_ch_(); get_ch_(); }
			bool open_next_file(std::string& name);
			int next_ch();
	};
		
	class Writer {
			std::ostream& out_;
			int last_ = '\n';

		public:
			Writer(std::ostream& out): out_ { out } { }
			void put_ch(int ch);
			void open_next_file(const std::string& name);
	};
};

