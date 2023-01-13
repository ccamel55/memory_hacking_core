#pragma once

namespace CORE {

	class POINT_INT {
	public:
		constexpr POINT_INT() : _x(0), _y(0) {

		}

		constexpr POINT_INT(int x, int y) : _x(x), _y(y) {

		}

		const POINT_INT operator+(const POINT_INT& in) const {
			return POINT_INT(
				_x + in._x,
				_y + in._y
			);
		}

		const POINT_INT operator-(const POINT_INT& in) const {
			return POINT_INT(
				_x - in._x,
				_y - in._y
			);
		}

		constexpr POINT_INT& operator=(const POINT_INT& in) {
			this->_x = in._x; this->_y = in._y;
			return *this;
		}

		int _x{};
		int _y{};
	};
}