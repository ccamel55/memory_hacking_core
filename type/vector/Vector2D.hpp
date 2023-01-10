#pragma once

#include "../../math/AVXMath.hpp"

namespace CORE {

	class Vector2D {
	public:

		constexpr Vector2D() {
			_x = 0.f;
			_y = 0.f;
		}

		constexpr Vector2D(float x, float y) {
			_x = x;
			_y = y;
		}

		const Vector2D operator+(const Vector2D& in) const {
			return Vector2D(
				_x + in._x,
				_y + in._y
			);
		}

		constexpr Vector2D& operator+=(const Vector2D& in) {

			this->_x += in._x;
			this->_y += in._y;

			return *this;
		}

		const Vector2D operator+(float in) const {
			return Vector2D(
				_x + in,
				_y + in
			);
		}

		constexpr Vector2D& operator+=(float in) {

			this->_x += in;
			this->_y += in;

			return *this;
		}

		const Vector2D operator-(const Vector2D& in) const {
			return Vector2D(
				_x - in._x,
				_y - in._y
			);
		}

		constexpr Vector2D& operator-=(const Vector2D& in) {

			this->_x -= in._x;
			this->_y -= in._y;

			return *this;
		}

		const Vector2D operator-(float in) const {
			return Vector2D(
				_x - in,
				_y - in
			);
		}

		constexpr Vector2D& operator-=(float in) {

			this->_x -= in;
			this->_y -= in;

			return *this;
		}

		const Vector2D operator*(const Vector2D& in) const {
			return Vector2D(
				_x * in._x,
				_y * in._y
			);
		}

		constexpr Vector2D& operator*=(const Vector2D& in) {

			this->_x *= in._x;
			this->_y *= in._y;

			return *this;
		}

		const Vector2D operator*(float in) const {
			return Vector2D(
				_x * in,
				_y * in
			);
		}

		constexpr Vector2D& operator*=(float in) {

			this->_x *= in;
			this->_y *= in;

			return *this;
		}

		const Vector2D operator/(const Vector2D& in) const {
			return Vector2D(
				_x / in._x,
				_y / in._y
			);
		}

		constexpr Vector2D& operator/=(const Vector2D& in) {

			this->_x /= in._x;
			this->_y /= in._y;

			return *this;
		}

		const Vector2D operator/(float in) const {
			return Vector2D(
				_x / in,
				_y / in
			);
		}

		constexpr Vector2D& operator/=(float in) {

			this->_x /= in;
			this->_y /= in;

			return *this;
		}

		bool operator==(const Vector2D& vecBase) const {
			return this->IsEqual(vecBase);
		}

		bool operator!=(const Vector2D& vecBase) const {
			return !this->IsEqual(vecBase);
		}


		bool IsEqual(const Vector2D& vecEqual, const float flErrorMargin = std::numeric_limits<float>::epsilon()) const {

			return
				(std::fabsf(this->_x - vecEqual._x) < flErrorMargin &&
					std::fabsf(this->_y - vecEqual._y) < flErrorMargin);
		}

		float length() const {

			__m256 v{};
			v.m256_f32[0] = _x * _x + _y * _y;

			return C_AVXMath::sqrt(v).m256_f32[0];
		}

		float lengthSqr() const {
			return (_x * _x + _y * _y);
		}

	public:
		float _x{};
		float _y{};
	};
}