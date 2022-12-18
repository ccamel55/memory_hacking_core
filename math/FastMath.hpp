#pragma once

#include <xmmintrin.h>
#include <math.h>

namespace CORE {

	// regularly used definitions here
	constexpr float PI = 3.1415927f;
	constexpr float PI_2 = PI * 2.f;
	constexpr float PI_HALF = PI * 0.5f;

	class C_FastMath {
	public:
		static float sqrt(float i);
		static float sin(float i);
		static float cos(float i);
		static float cos52s(float i);
		static void sincos(float i, float& s, float& c);
	};
}