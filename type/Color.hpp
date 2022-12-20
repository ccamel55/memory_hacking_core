#pragma once

#include <array>

namespace CORE {

	/*
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
	*/

	class Color {
	public:
		Color() {
			_r = 0;
			_g = 0;
			_b = 0;
			_a = 255;
		}

		Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255) {
			_r = r;
			_g = g;
			_b = b;
			_a = a;
		}

		/* convert color to float array w/ alpha (in: 0 - 255, out: 0.0 - 1.0) */
		std::array<float, 4U> baseAlpha() const
		{
			std::array<float, 4U> baseColor{};
			baseColor[0] = (_r / 255.f);
			baseColor[1] = (_g / 255.f);
			baseColor[2] = (_b / 255.f);
			baseColor[3] = (_a / 255.f);

			return baseColor;
		}

	public:
		// should be using chars but games usually use ints :(
		unsigned int _r;
		unsigned int _g;
		unsigned int _b;
		unsigned int _a;
	};
}