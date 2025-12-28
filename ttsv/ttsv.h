#pragma once

#include <iostream>
#include <string>

namespace ttsv {
	
	class ostream: private std::streambuf, public std::ostream  {
			std::ostream& forward_;

			int overflow(int ch) override;

		public:
			ostream(std::ostream& forward):
				std::ostream { this }, forward_ { forward }
			{ }

			void close_cell();
			void close_line();
	};
		
};

