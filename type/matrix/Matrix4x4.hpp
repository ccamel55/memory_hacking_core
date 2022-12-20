#pragma once

#include "Matrix3x4.hpp"

namespace CORE {

	class Matrix4x4 {
	public:

		Matrix4x4() = default;

		constexpr Matrix4x4(
			const float m00, const float m01, const float m02, const float m03,
			const float m10, const float m11, const float m12, const float m13,
			const float m20, const float m21, const float m22, const float m23,
			const float m30, const float m31, const float m32, const float m33) {
			_data[0][0] = m00; _data[0][1] = m01; _data[0][2] = m02; _data[0][3] = m03;
			_data[1][0] = m10; _data[1][1] = m11; _data[1][2] = m12; _data[1][3] = m13;
			_data[2][0] = m20; _data[2][1] = m21; _data[2][2] = m22; _data[2][3] = m23;
			_data[3][0] = m30; _data[3][1] = m31; _data[3][2] = m32; _data[3][3] = m33;
		}

		constexpr void identity() {

			for (int i = 0; i < 4; i++) {

				for (int n = 0; n < 4; n++) {
					this->_data[i][n] = i == n ? 1.0f : 0.0f;
				}	
			}
		}

		Matrix3x4& as3x4() {
			return *reinterpret_cast<Matrix3x4*>(this);
		}

		float _data[4][4]{};
	};
}