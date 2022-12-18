#pragma once

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

	public:
		float _x;
		float _y;
		float _z;
	};
}