#pragma once

namespace CORE {

	// regularly used definitions here
	constexpr float PI = 3.1415927f;
	constexpr float PI_2 = PI * 2.f;
	constexpr float PI_INV_2 = 0.1591549f;
	constexpr float PI_HALF = PI * 0.5f;
	constexpr float PI_3_2 = PI * 1.5f;

	class C_MathLib {
	public:	
		static float degreeToRadian(float degree);
		static float radianToDegree(float radian);
	};
}