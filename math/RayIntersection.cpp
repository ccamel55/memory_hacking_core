#include "RayIntersection.hpp"

using namespace CORE;

bool C_RayIntersection::rayIntersectAABB(const Vector3D& origin, const Vector3D& direction, const Vector3D& min, const Vector3D& max) {

	float tmin = 0.f;
	float tmax = 0.f;

	// ray-box intersection
	if (direction._x >= 0){

		tmin = (min._x - origin._x) / direction._x;
		tmax = (max._x - origin._x) / direction._x;
	}
	else{

		tmin = (max._x - origin._x) / direction._x;
		tmax = (min._x - origin._x) / direction._x;
	}

	float tymin = 0.f;
	float tymax = 0.f;

	if (direction._y >= 0) {

		tymin = (min._y - origin._y) / direction._y;
		tymax = (max._y - origin._y) / direction._y;
	}
	else {

		tymin = (max._y - origin._y) / direction._y;
		tymax = (min._y - origin._y) / direction._y;
	}

	if (tmin > tymax || tymin > tmax) {
		return false;
	}

	if (tymin > tmin) {
		tmin = tymin;
	}

	if (tymax < tmax) {
		tmax = tymax;
	}

	float tzmin = 0.f;
	float tzmax = 0.f;

	if (direction._z >= 0) {

		tzmin = (min._z - origin._z) / direction._z;
		tzmax = (max._z - origin._z) / direction._z;
	}
	else {

		tzmin = (max._z - origin._z) / direction._z;
		tzmax = (min._z - origin._z) / direction._z;
	}

	if (tmin > tzmax || tzmin > tmax) {
		return false;
	}
	
	if (tmin < 0 || tmax < 0) {
		return false;
	}

	return true;
}

bool C_RayIntersection::rayIntersectCapsule(const Vector3D& origin, const Vector3D& direction, const Vector3D& min, const Vector3D& max, float radius) {

    // https://www.unknowncheats.me/forum/counterstrike-global-offensive/161306-efficient-ray-capsule-intersection-algorithm.html

    const auto& vecDelta = (max - min).normalize();
    const auto& vecCenter = min;

    // run intersection on each sphere
    if (rayIntersectSphere(origin, direction, min, radius) || 
        rayIntersectSphere(origin, direction, max, radius)) {
        return true;
    }

    for (size_t i = 1; i < std::floor(min.dist(max)); ++i) {

        if (rayIntersectSphere(origin, direction, min + vecDelta * static_cast<float>(i), radius )) {
            return true;
        }
    }

    return false;
}

bool C_RayIntersection::rayIntersectSphere(const Vector3D& origin, const Vector3D& direction, const Vector3D& center, float radius) {

    auto Q = center - origin;
    auto v = Q.dot(direction);
    auto d = (radius * radius) - (Q.lengthSqr() - v * v);

    return d >= FLT_EPSILON;
}