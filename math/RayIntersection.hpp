#pragma once

#include "../type/vector/Vector3D.hpp"
#include "../type/matrix/Matrix3x4.hpp"

#include <cmath>
#include <vector>

namespace CORE {

	class C_RayIntersection {
	public:
		static bool rayIntersectAABB(const Vector3D& origin, const Vector3D& direction, const Vector3D& min, const Vector3D& max);
		static bool rayIntersectCapsule(const Vector3D& origin, const Vector3D& direction, const Vector3D& min, const Vector3D& max, float radius);
		static bool rayIntersectSphere(const Vector3D& origin, const Vector3D& direction, const Vector3D& center, float radius);
	};
}