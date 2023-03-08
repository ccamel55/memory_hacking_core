#pragma once

#include "../vector/Vector3D.hpp"

namespace CORE {

	class Matrix3x4 {
	public:

		Matrix3x4() = default;

		constexpr Matrix3x4(
			const float m00, const float m01, const float m02, const float m03,
			const float m10, const float m11, const float m12, const float m13,
			const float m20, const float m21, const float m22, const float m23) {

			_data[0][0] = m00; _data[0][1] = m01; _data[0][2] = m02; _data[0][3] = m03;
			_data[1][0] = m10; _data[1][1] = m11; _data[1][2] = m12; _data[1][3] = m13;
			_data[2][0] = m20; _data[2][1] = m21; _data[2][2] = m22; _data[2][3] = m23;
		}

		constexpr Matrix3x4(const Vector3D& xAxis, const Vector3D& yAxis, const Vector3D& zAxis, const Vector3D& vecOrigin) {
			Init(xAxis, yAxis, zAxis, vecOrigin);
		}

		constexpr void Init(const Vector3D& vecForward, const Vector3D& vecLeft, const Vector3D& vecUp, const Vector3D& vecOrigin) {

			setForward(vecForward);
			setLeft(vecLeft);
			setUp(vecUp);
			setOrigin(vecOrigin);
		}

		constexpr void setForward(const Vector3D& vecForward) {

			this->_data[0][0] = vecForward._x;
			this->_data[1][0] = vecForward._y;
			this->_data[2][0] = vecForward._z;
		}

		constexpr void setLeft(const Vector3D& vecLeft) {

			this->_data[0][1] = vecLeft._x;
			this->_data[1][1] = vecLeft._y;
			this->_data[2][1] = vecLeft._z;
		}

		constexpr void setUp(const Vector3D& vecUp) {

			this->_data[0][2] = vecUp._x;
			this->_data[1][2] = vecUp._y;
			this->_data[2][2] = vecUp._z;
		}

		constexpr void setOrigin(const Vector3D& vecOrigin) {

			this->_data[0][3] = vecOrigin._x;
			this->_data[1][3] = vecOrigin._y;
			this->_data[2][3] = vecOrigin._z;
		}

		constexpr void setIdentity() {

			// reset matrix to identity matrix
			_data[0][0] = 1.f;
			_data[0][1] = 0.f;
			_data[0][2] = 0.f;
			_data[0][3] = 0.f;

			_data[1][0] = 0.f;
			_data[1][1] = 1.f;
			_data[1][2] = 0.f;
			_data[1][3] = 0.f;

			_data[2][0] = 0.f;
			_data[2][1] = 0.f;
			_data[2][2] = 1.f;
			_data[2][3] = 0.f;
		}

		Vector3D getOrigin() const {
			return {
				this->_data[0][3],
				this->_data[1][3],
				this->_data[2][3]
			};
		}

		constexpr void invalidate() {

			for (auto& arrSubData : _data) {

				for (auto& flData : arrSubData) {
					flData = std::numeric_limits<float>::infinity();
				}	
			}
		}

		const float* base() const {
			return &_data[0][0];
		}

		float _data[3][4]{};
	};
}