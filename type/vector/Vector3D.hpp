#pragma once

#include <xmmintrin.h>

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

		const Vector3D operator+(const Vector3D& in) const {
			return Vector3D(
				_x + in._x,
				_y + in._y,
				_z + in._z
			);
		}

		const Vector3D operator+(float in) const {
			return Vector3D(
				_x + in,
				_y + in,
				_z + in
			);
		}

		const Vector3D operator-(const Vector3D& in) const {
			return Vector3D(
				_x - in._x,
				_y - in._y,
				_z - in._z
			);
		}

		const Vector3D operator-(float in) const {
			return Vector3D(
				_x - in,
				_y - in,
				_z - in
			);
		}

		const Vector3D operator*(const Vector3D& in) const {
			return Vector3D(
				_x * in._x,
				_y * in._y,
				_z * in._z
			);
		}

		const Vector3D operator*(float in) const {
			return Vector3D(
				_x * in,
				_y * in,
				_z * in
			);
		}

		const Vector3D operator/(const Vector3D& in) const {
			return Vector3D(
				_x / in._x,
				_y / in._y,
				_z / in._z
			);
		}

		const Vector3D operator/(float in) const {
			return Vector3D(
				_x / in,
				_y / in,
				_z / in
			);
		}

		float length() const {
			return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_x * _x + _y * _y + _z * _z)));
		}

		float lengthSqr() const {
			return (_x * _x + _y * _y + _z * _z);
		}

		const Vector3D normalize() const {

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

	public:
		float _x;
		float _y;
		float _z;
	};
}