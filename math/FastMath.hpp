#pragma once

#include <xmmintrin.h>
#include <math.h>

namespace CORE {

	class C_FastMath {
	public:
		static float sqrt(float i);
		static float sin(float i);
		static float cos(float i);
		static float cos52s(float i);
		static void sincos(float i, float& s, float& c);
	};
}