#pragma once 

namespace CORE {

	class POINT_FLOAT {
	public:
		constexpr POINT_FLOAT() : _x(0.f), _y(0.f) {

		}

		constexpr POINT_FLOAT(float x, float y) : _x(x), _y(y) {

		}

		POINT_FLOAT operator+(const POINT_FLOAT& in) const {
			return POINT_FLOAT(
				_x + in._x,
				_y + in._y
			);
		}

		POINT_FLOAT operator-(const POINT_FLOAT& in) const {
			return POINT_FLOAT(
				_x - in._x,
				_y - in._y
			);
		}

		constexpr POINT_FLOAT& operator=(const POINT_FLOAT& in) {
			this->_x = in._x; this->_y = in._y;
			return *this;
		}

		float _x{};
		float _y{};
	};
}