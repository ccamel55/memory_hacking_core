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

	public:
		float _x;
		float _y;
	};
}