#include "md5.h"

namespace md5 {
	void base::init() {
		state_[0] = 0x67452301u;
		state_[1] = 0xefcdab89u;
		state_[2] = 0x98badcfeu;
		state_[3] = 0x10325476u;
		
		count_[0] = count_[1] = 0;
	}

	void base::decode_buffer(unsigned x[16]) {
		for (unsigned i { 0 }, j { 0 } ; i < 16; ++i, j += 4) {
			x[i] = buffer_[j] | (buffer_[j + 1] << 8) |
				(buffer_[j + 2] << 16) | (buffer_[j + 3] << 24);
		}
	}

	void base::encode(
		const unsigned* source, unsigned char* dest, unsigned byte_count
	) {
		unsigned int i, j;

		for (i = 0, j = 0; j < byte_count; i++, j += 4) {
			dest[j] = static_cast<unsigned char>(source[i] & 0xff);
			dest[j+1] = static_cast<unsigned char>((source[i] >> 8) & 0xff);
			dest[j+2] = static_cast<unsigned char>((source[i] >> 16) & 0xff);
			dest[j+3] = static_cast<unsigned char>((source[i] >> 24) & 0xff);
		}
	}

	static constexpr unsigned s11 { 7 };
	static constexpr unsigned s12 { 12 };
	static constexpr unsigned s13 { 17 };
	static constexpr unsigned s14 { 22 };
	static constexpr unsigned s21 { 5 };
	static constexpr unsigned s22 { 9 };
	static constexpr unsigned s23 { 14 };
	static constexpr unsigned s24 { 20 };
	static constexpr unsigned s31 { 4 };
	static constexpr unsigned s32 { 11 };
	static constexpr unsigned s33 { 16 };
	static constexpr unsigned s34 { 23 };
	static constexpr unsigned s41 { 6 };
	static constexpr unsigned s42 { 10 };
	static constexpr unsigned s43 { 15 };
	static constexpr unsigned s44 { 21 };

	static constexpr unsigned f(unsigned x, unsigned y, unsigned z) {
		return (x & y) | ((~x) & z);
	}
	static constexpr unsigned g(unsigned x, unsigned y, unsigned z) {
		return (x & z) | (y & (~z));
	}
	static constexpr unsigned h(unsigned x, unsigned y, unsigned z) {
		return x ^ y ^ z;
	}
	static constexpr unsigned i(unsigned x, unsigned y, unsigned z) {
		return y ^ (x | (~z));
	}

	static constexpr unsigned rotate_left(unsigned x, unsigned n) {
		return (x << n) | (x >> (32 - n));
	}

	static constexpr unsigned ff(
		unsigned a, unsigned b, unsigned c, unsigned d,
		unsigned x, unsigned s, unsigned ac
	) {
		a += f(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
		return a;
	}

	static constexpr unsigned gg(
		unsigned a, unsigned b, unsigned c, unsigned d,
		unsigned x, unsigned s, unsigned ac
	) {
		a += g(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
		return a;
	}

	static constexpr unsigned hh(
		unsigned a, unsigned b, unsigned c, unsigned d,
		unsigned x, unsigned s, unsigned ac
	) {
		a += h(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
		return a;
	}

	static constexpr unsigned ii(
		unsigned a, unsigned b, unsigned c, unsigned d,
		unsigned x, unsigned s, unsigned ac
	) {
		a += i(b, c, d) + x + ac;
		a = rotate_left(a, s);
		a += b;
		return a;
	}

	void base::process_block() {
		unsigned a { state_[0] }, b { state_[1] };
		unsigned c { state_[2] }, d { state_[3] };
		unsigned x[16];
		decode_buffer(x);

		/* Round 1 */
		a = ff(a, b, c, d, x[0], s11, 0xd76aa478u); /* 1 */
		d = ff(d, a, b, c, x[1], s12, 0xe8c7b756u); /* 2 */
		c = ff(c, d, a, b, x[2], s13, 0x242070dbu); /* 3 */
		b = ff(b, c, d, a, x[3], s14, 0xc1bdceeeu); /* 4 */
		a = ff(a, b, c, d, x[4], s11, 0xf57c0fafu); /* 5 */
		d = ff(d, a, b, c, x[5], s12, 0x4787c62au); /* 6 */
		c = ff(c, d, a, b, x[6], s13, 0xa8304613u); /* 7 */
		b = ff(b, c, d, a, x[7], s14, 0xfd469501u); /* 8 */
		a = ff(a, b, c, d, x[8], s11, 0x698098d8u); /* 9 */
		d = ff(d, a, b, c, x[9], s12, 0x8b44f7afu); /* 10 */
		c = ff(c, d, a, b, x[10], s13, 0xffff5bb1u); /* 11 */
		b = ff(b, c, d, a, x[11], s14, 0x895cd7beu); /* 12 */
		a = ff(a, b, c, d, x[12], s11, 0x6b901122u); /* 13 */
		d = ff(d, a, b, c, x[13], s12, 0xfd987193u); /* 14 */
		c = ff(c, d, a, b, x[14], s13, 0xa679438eu); /* 15 */
		b = ff(b, c, d, a, x[15], s14, 0x49b40821u); /* 16 */

		/* Round 2 */
		a = gg(a, b, c, d, x[1], s21, 0xf61e2562u); /* 17 */
		d = gg(d, a, b, c, x[6], s22, 0xc040b340u); /* 18 */
		c = gg(c, d, a, b, x[11], s23, 0x265e5a51u); /* 19 */
		b = gg(b, c, d, a, x[0], s24, 0xe9b6c7aau); /* 20 */
		a = gg(a, b, c, d, x[5], s21, 0xd62f105du); /* 21 */
		d = gg(d, a, b, c, x[10], s22, 0x2441453u); /* 22 */
		c = gg(c, d, a, b, x[15], s23, 0xd8a1e681u); /* 23 */
		b = gg(b, c, d, a, x[4], s24, 0xe7d3fbc8u); /* 24 */
		a = gg(a, b, c, d, x[9], s21, 0x21e1cde6u); /* 25 */
		d = gg(d, a, b, c, x[14], s22, 0xc33707d6u); /* 26 */
		c = gg(c, d, a, b, x[3], s23, 0xf4d50d87u); /* 27 */
		b = gg(b, c, d, a, x[8], s24, 0x455a14edu); /* 28 */
		a = gg(a, b, c, d, x[13], s21, 0xa9e3e905u); /* 29 */
		d = gg(d, a, b, c, x[2], s22, 0xfcefa3f8u); /* 30 */
		c = gg(c, d, a, b, x[7], s23, 0x676f02d9u); /* 31 */
		b = gg(b, c, d, a, x[12], s24, 0x8d2a4c8au); /* 32 */

		/* Round 3 */
		a = hh(a, b, c, d, x[5], s31, 0xfffa3942u); /* 33 */
		d = hh(d, a, b, c, x[8], s32, 0x8771f681u); /* 34 */
		c = hh(c, d, a, b, x[11], s33, 0x6d9d6122u); /* 35 */
		b = hh(b, c, d, a, x[14], s34, 0xfde5380cu); /* 36 */
		a = hh(a, b, c, d, x[1], s31, 0xa4beea44u); /* 37 */
		d = hh(d, a, b, c, x[4], s32, 0x4bdecfa9u); /* 38 */
		c = hh(c, d, a, b, x[7], s33, 0xf6bb4b60u); /* 39 */
		b = hh(b, c, d, a, x[10], s34, 0xbebfbc70u); /* 40 */
		a = hh(a, b, c, d, x[13], s31, 0x289b7ec6u); /* 41 */
		d = hh(d, a, b, c, x[0], s32, 0xeaa127fau); /* 42 */
		c = hh(c, d, a, b, x[3], s33, 0xd4ef3085u); /* 43 */
		b = hh(b, c, d, a, x[6], s34, 0x4881d05u); /* 44 */
		a = hh(a, b, c, d, x[9], s31, 0xd9d4d039u); /* 45 */
		d = hh(d, a, b, c, x[12], s32, 0xe6db99e5u); /* 46 */
		c = hh(c, d, a, b, x[15], s33, 0x1fa27cf8u); /* 47 */
		b = hh(b, c, d, a, x[2], s34, 0xc4ac5665u); /* 48 */

		/* Round 4 */
		a = ii(a, b, c, d, x[0], s41, 0xf4292244u); /* 49 */
		d = ii(d, a, b, c, x[7], s42, 0x432aff97u); /* 50 */
		c = ii(c, d, a, b, x[14], s43, 0xab9423a7u); /* 51 */
		b = ii(b, c, d, a, x[5], s44, 0xfc93a039u); /* 52 */
		a = ii(a, b, c, d, x[12], s41, 0x655b59c3u); /* 53 */
		d = ii(d, a, b, c, x[3], s42, 0x8f0ccc92u); /* 54 */
		c = ii(c, d, a, b, x[10], s43, 0xffeff47du); /* 55 */
		b = ii(b, c, d, a, x[1], s44, 0x85845dd1u); /* 56 */
		a = ii(a, b, c, d, x[8], s41, 0x6fa87e4fu); /* 57 */
		d = ii(d, a, b, c, x[15], s42, 0xfe2ce6e0u); /* 58 */
		c = ii(c, d, a, b, x[6], s43, 0xa3014314u); /* 59 */
		b = ii(b, c, d, a, x[13], s44, 0x4e0811a1u); /* 60 */
		a = ii(a, b, c, d, x[4], s41, 0xf7537e82u); /* 61 */
		d = ii(d, a, b, c, x[11], s42, 0xbd3af235u); /* 62 */
		c = ii(c, d, a, b, x[2], s43, 0x2ad7d2bbu); /* 63 */
		b = ii(b, c, d, a, x[9], s44, 0xeb86d391u); /* 64 */

		state_[0] += a;
		state_[1] += b;
		state_[2] += c;
		state_[3] += d;
	}

	void base::add_to_hash(unsigned char ch) {
		int index = (count_[0] >> 3) & 63;
		buffer_[index] = ch;
		if ((count_[0] += 8) < 8) { ++count_[1]; }
		if (index == 63) {
			process_block();
		}
	}

	void base::finish(unsigned char digest[16]) {
		unsigned char size[8];
		encode(count_, size, 8);

		add_to_hash(0x80);
		for (;;) {
			int index = (count_[0] >> 3) & 63;
			if (index == 56) { break; }
			add_to_hash(0x00);
		}
		for (int i = 0; i < 8; ++i) { add_to_hash(size[i]); }
		encode(state_, digest, 16);
		base::init();
	}

	std::string base::finish() {
		static const char digits[] = "0123456789abcdef";
		unsigned char raw[16];
		finish(raw);
		std::string digest;
		for (int i = 0; i < 16; ++i) {
			digest += digits[(raw[i] >> 4) & 0xf];
			digest += digits[raw[i] & 0xf];
		}
		return digest;
	}
}
