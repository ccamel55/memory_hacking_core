#pragma once

#include <limits>
#include <cmath>

#include "Vector2D.hpp"

namespace CORE {

	class Vector3D {
	public:

		Vector3D() {
			_x = 0.f;
			_y = 0.f;
			_z = 0.f;
		}

		Vector3D(float x, float y, float z) {
			_x = x;
			_y = y;
			_z = z;
		}

		Vector3D operator+(const Vector3D& in) const {
			return Vector3D(
				_x + in._x,
				_y + in._y,
				_z + in._z
			);
		}

		constexpr Vector3D& operator+=(const Vector3D& in) {

			this->_x += in._x;
			this->_y += in._y;
			this->_z += in._z;

			return *this;
		}

		Vector3D operator+(float in) const {
			return Vector3D(
				_x + in,
				_y + in,
				_z + in
			);
		}

		constexpr Vector3D& operator+=(float in) {

			this->_x += in;
			this->_y += in;
			this->_z += in;

			return *this;
		}

		Vector3D operator-(const Vector3D& in) const {
			return Vector3D(
				_x - in._x,
				_y - in._y,
				_z - in._z
			);
		}

		constexpr Vector3D& operator-=(const Vector3D& in) {

			this->_x -= in._x;
			this->_y -= in._y;
			this->_z -= in._z;

			return *this;
		}

		Vector3D operator-(float in) const {
			return Vector3D(
				_x - in,
				_y - in,
				_z - in
			);
		}

		constexpr Vector3D& operator-=(float in) {

			this->_x -= in;
			this->_y -= in;
			this->_z -= in;

			return *this;
		}

		Vector3D operator*(const Vector3D& in) const {
			return Vector3D(
				_x * in._x,
				_y * in._y,
				_z * in._z
			);
		}

		constexpr Vector3D& operator*=(const Vector3D& in) {

			this->_x *= in._x;
			this->_y *= in._y;
			this->_z *= in._z;

			return *this;
		}

		Vector3D operator*(float in) const {
			return Vector3D(
				_x * in,
				_y * in,
				_z * in
			);
		}

		constexpr Vector3D& operator*=(float in) {

			this->_x *= in;
			this->_y *= in;
			this->_z *= in;

			return *this;
		}

		Vector3D operator/(const Vector3D& in) const {
			return Vector3D(
				_x / in._x,
				_y / in._y,
				_z / in._z
			);
		}

		constexpr Vector3D& operator/=(const Vector3D& in) {

			this->_x /= in._x;
			this->_y /= in._y;
			this->_z /= in._z;

			return *this;
		}

		Vector3D operator/(float in) const {
			return Vector3D(
				_x / in,
				_y / in,
				_z / in
			);
		}

		constexpr Vector3D& operator/=(float in) {

			this->_x /= in;
			this->_y /= in;
			this->_z /= in;

			return *this;
		}

		bool operator==(const Vector3D& vecBase) const {
			return this->IsEqual(vecBase);
		}

		bool operator!=(const Vector3D& vecBase) const {
			return !this->IsEqual(vecBase);
		}

		constexpr Vector3D& operator=(const Vector3D& vecBase) {
			this->_x = vecBase._x; this->_y = vecBase._y; this->_z = vecBase._z;
			return *this;
		}

		constexpr Vector3D& operator=(const Vector2D& vecBase2D) {
			this->_x = vecBase2D._x; this->_y = vecBase2D._y; this->_z = 0.0f;
			return *this;
		}

		bool IsEqual(const Vector3D& vecEqual, const float flErrorMargin = std::numeric_limits<float>::epsilon()) const {

			return 
				(std::fabsf(this->_x - vecEqual._x) < flErrorMargin &&
				std::fabsf(this->_y - vecEqual._y) < flErrorMargin &&
				std::fabsf(this->_z - vecEqual._z) < flErrorMargin);
		}

		float length() const {

			__m256 v{};
			v.m256_f32[0] = _x * _x + _y * _y + _z * _z;

			return C_AVXMath::sqrt(v).m256_f32[0];
		}

		float length2D() const {

			__m256 v{};
			v.m256_f32[0] = _x * _x + _y * _y;

			return C_AVXMath::sqrt(v).m256_f32[0];
		}

		float lengthSqr() const {
			return (_x * _x + _y * _y + _z * _z);
		}

		float length2DSqr() const {
			return (_x * _x + _y * _y);
		}

		Vector3D normalize() const {

			auto out = *this;
			const auto length = out.length();

			if (length != 0.f) {
				out = out / length;
			}
			else {
				out._x = out._y = out._z = 0;
			}
			
			return out;
		}

		float dist(const Vector3D& in) const {
			return Vector3D(_x - in._x, _y - in._y, _z - in._z).length();
		}

		float dot(const Vector3D& in) const {
			return (_x * in._x + _y * in._y + _z * in._z);
		}

		Vector3D cross(const Vector3D& in) const {
			return {
				this->_y * in._z - this->_z * in._y,
				this->_z * in._x - this->_x * in._z,
				this->_x * in._y - this->_y * in._x,
			};
		}

	public:
		float _x{};
		float _y{};
		float _z{};
	};
}