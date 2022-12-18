#pragma once

namespace CORE {

	class Color {
	public:
		Color() {
			_r = 0;
			_g = 0;
			_b = 0;
			_a = 255;
		}

		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255) {
			_r = r;
			_g = g;
			_b = b;
			_a = a;
		}

	public:
		// 8 bits, 0 -> 255
		unsigned char _r;
		unsigned char _g;
		unsigned char _b;
		unsigned char _a;
	};
}