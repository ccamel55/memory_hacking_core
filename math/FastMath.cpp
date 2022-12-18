#include "FastMath.hpp"

using namespace CORE;

float C_FastMath::sqrt(float i) {
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(i)));
}

float C_FastMath::sin(float i) {
    return cos(PI_HALF - i);
}

float C_FastMath::cos(float i) {

    constexpr float c1 = PI * 1.5f;
    constexpr float c2 = 0.1591549f;

    i = i - floorf(i * c2) * PI_2;
    i = i > 0.f ? i : -i;

    if (i < PI_HALF)
        return cos52s(i);

    if (i < PI)
        return -cos52s(PI - i);

    if (i < c1)
        return -cos52s(i - PI);

    return cos52s(PI_2 - i);
}

float C_FastMath::cos52s(float i) {

    constexpr float c1 = 0.9999932946f;
    constexpr float c2 = -0.4999124376f;
    constexpr float c3 = 0.0414877472f;
    constexpr float c4 = -0.0012712095f;

    const float x2 = i * i;

    return (c1 + x2 * (c2 + x2 * (c3 + c4 * x2)));
}

void C_FastMath::sincos(float i, float& s, float& c) {

    constexpr float c1 = PI * 1.5f;
    constexpr float c2 = 0.1591549f;

    i = i - floorf(i * c2) * PI_2;
    i = i > 0.f ? i : -i;

    const float sinmultiplier = i > 0.f && i < PI ? 1.f : -1.f;

    if (i < PI_HALF)
    {
        c = cos52s(i);
        s = sinmultiplier * sqrt(1.f - c * c);
        return;
    }

    if (i < PI)
    {
        c = -cos52s(PI - i);
        s = sinmultiplier * sqrt(1.f - c * c);
        return;
    }

    if (i < c1)
    {
        c = -cos52s(i - PI);
        s = sinmultiplier * sqrt(1.f - c * c);
        return;
    }

    c = cos52s(PI_2 - i);
    s = sinmultiplier * sqrt(1.f - c * c);
}
