#pragma once

#include <immintrin.h>
#include <math.h>

#include "MathLib.hpp"

#ifndef __AVX2__
#error AVX2 Instructions must be enabled!
#endif // !__AVX2__

// fast but not very accuary trig functions
// https://github.com/peihunglin/TSVC_benchmark/blob/master/rosesimd.c

namespace CORE {

	namespace {
		const __m256 signmask = _mm256_castsi256_ps(_mm256_set1_epi32(0x80000000));
	}

	class C_AVXMath {
	public:	

		__forceinline static __m256 sqrt(__m256 x) {
			return _mm256_sqrt_ps(x);
		}

		__forceinline static __m256 cos52(__m256 x) {

			const auto c1 = _mm256_set1_ps(0.9999932946f);
			const auto c2 = _mm256_set1_ps(-0.4999124376f);
			const auto c3 = _mm256_set1_ps(0.0414877472f);
			const auto c4 = _mm256_set1_ps(-0.0012712095f);
			const auto x2 = _mm256_mul_ps(x, x);

			return _mm256_add_ps(c1, _mm256_mul_ps(x2, _mm256_add_ps(c2, _mm256_mul_ps(x2, _mm256_add_ps(c3, _mm256_mul_ps(c4, x2))))));
		}

		__forceinline static __m256 cos(__m256 x) {

			x = _mm256_andnot_ps(signmask, x);
			x = _mm256_sub_ps(x, _mm256_mul_ps(_mm256_cvtepi32_ps(_mm256_cvttps_epi32(_mm256_mul_ps(x, _mm256_set1_ps(PI_INV_2)))), _mm256_set1_ps(PI_2)));

			auto cosangle = x;
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI_HALF), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(PI), x))));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI), 29), signmask));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI_3_2), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(PI_2), x))));

			auto result = cos52(cosangle);
			result = _mm256_xor_ps(result, _mm256_and_ps(_mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI_HALF), 29), _mm256_cmp_ps(x, _mm256_set1_ps(PI_3_2), 17)), signmask));

			return result;
		}

		__forceinline static __m256 sin(__m256 x) {
			return cos(_mm256_sub_ps(_mm256_set1_ps(PI_HALF), x));
		}

		__forceinline static void sincos(__m256 x, __m256& s, __m256& c) {

			const auto anglesign = _mm256_or_ps(_mm256_set1_ps(1.f), _mm256_and_ps(signmask, x));

			x = _mm256_andnot_ps(signmask, x);
			x = _mm256_sub_ps(x, _mm256_mul_ps(_mm256_cvtepi32_ps(_mm256_cvttps_epi32(_mm256_mul_ps(x, _mm256_set1_ps(PI_INV_2)))), _mm256_set1_ps(PI_2)));

			auto cosangle = x;
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI_HALF), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(PI), x))));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI), 29), signmask));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI_3_2), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(PI_2), x))));

			auto result = cos52(cosangle);
			c = result = _mm256_xor_ps(result, _mm256_and_ps(_mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI_HALF), 29), _mm256_cmp_ps(x, _mm256_set1_ps(PI_3_2), 17)), signmask));

			const auto sinmultiplier = _mm256_mul_ps(anglesign, _mm256_or_ps(_mm256_set1_ps(1.f), _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(PI), 30), signmask)));
			s = _mm256_mul_ps(sinmultiplier, sqrt(_mm256_sub_ps(_mm256_set1_ps(1.f), _mm256_mul_ps(result, result))));
		}
	};
}