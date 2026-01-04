#pragma once

#include <ostream>
#include <string>

namespace md5 {
	class base {
			unsigned state_[4];
			unsigned count_[2];
			unsigned char buffer_[64];

			void init();

			void decode_buffer(unsigned x[16]);
			void encode(
				const unsigned* source, unsigned char* dest, unsigned byte_count
			);

			void process_block();

		public:
			base() { init(); }
			virtual ~base() = default;

			void add_to_hash(unsigned char ch);

			void finish(unsigned char digest[16]);
			std::string finish();
	};

	template<class CharT, class Traits = std::char_traits<CharT>>
	class basic_ostream: 
		public base,
		private std::basic_streambuf<CharT, Traits>,
		public std::basic_ostream<CharT, Traits>
	{
			std::basic_ostream<CharT, Traits>& forward_;

			Traits::int_type overflow(Traits::int_type ch) override {
				forward_.put(ch);
				add_to_hash(Traits::to_char_type(ch));
				return 0;
			}

		public:
			explicit basic_ostream(std::basic_ostream<CharT, Traits>& forward):
				std::basic_ostream<CharT, Traits> { this }, forward_ { forward }
			{ }

	};

	using ostream = basic_ostream<char>;
}
