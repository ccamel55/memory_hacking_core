#pragma once

namespace CORE {

	class Vector2D {
	public:

		Vector2D() {
			_x = 0.f;
			_y = 0.f;
		}

		Vector2D(float x, float y) {
			_x = x;
			_y = y;
		}

		float length() const {
			return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(_x * _x + _y * _y)));
		}

		float lengthSqr() const {
			return (_x * _x + _y * _y);
		}

	public:
		float _x;
		float _y;
	};
}