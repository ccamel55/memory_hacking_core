#include "MathLib.hpp"
#include "FastMath.hpp"

using namespace CORE;

float C_MathLib::degreeToRadian(float degree)
{
	return degree * (PI / 180.f);
}

float C_MathLib::radianToDegree(float radian)
{
	return radian * (180.f / PI);
}
