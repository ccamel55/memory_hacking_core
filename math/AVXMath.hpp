#pragma once

#include <immintrin.h>
#include <math.h>

#ifndef __AVX2__
#error AVX2 Instructions must be enabled!
#endif // !__AVX2__

namespace CORE {

	namespace
	{
		const float invtwopi = 0.1591549f;
		const float twopi = 6.283185f;
		const float threehalfpi = 4.7123889f;
		const float pi = 3.141593f;
		const float halfpi = 1.570796f;

		const __m256 signmask = _mm256_castsi256_ps(_mm256_set1_epi32(0x80000000));
	}

	class C_AVXMath {
	public:	

		// defined in header because we shouldnt really be inlining static functions, and compiler knows that :P

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
			x = _mm256_sub_ps(x, _mm256_mul_ps(_mm256_cvtepi32_ps(_mm256_cvttps_epi32(_mm256_mul_ps(x, _mm256_set1_ps(invtwopi)))), _mm256_set1_ps(twopi)));

			auto cosangle = x;
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(halfpi), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(pi), x))));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(pi), 29), signmask));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(threehalfpi), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(twopi), x))));

			auto result = cos52(cosangle);
			result = _mm256_xor_ps(result, _mm256_and_ps(_mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(halfpi), 29), _mm256_cmp_ps(x, _mm256_set1_ps(threehalfpi), 17)), signmask));

			return result;
		}

		__forceinline static __m256 sin(__m256 x) {
			return cos(_mm256_sub_ps(_mm256_set1_ps(halfpi), x));
		}

		__forceinline static void sincos(__m256 x, __m256& s, __m256& c) {

			const auto anglesign = _mm256_or_ps(_mm256_set1_ps(1.f), _mm256_and_ps(signmask, x));

			x = _mm256_andnot_ps(signmask, x);
			x = _mm256_sub_ps(x, _mm256_mul_ps(_mm256_cvtepi32_ps(_mm256_cvttps_epi32(_mm256_mul_ps(x, _mm256_set1_ps(invtwopi)))), _mm256_set1_ps(twopi)));

			auto cosangle = x;
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(halfpi), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(pi), x))));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(pi), 29), signmask));
			cosangle = _mm256_xor_ps(cosangle, _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(threehalfpi), 29), _mm256_xor_ps(cosangle, _mm256_sub_ps(_mm256_set1_ps(twopi), x))));

			auto result = cos52(cosangle);
			c = result = _mm256_xor_ps(result, _mm256_and_ps(_mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(halfpi), 29), _mm256_cmp_ps(x, _mm256_set1_ps(threehalfpi), 17)), signmask));

			const auto sinmultiplier = _mm256_mul_ps(anglesign, _mm256_or_ps(_mm256_set1_ps(1.f), _mm256_and_ps(_mm256_cmp_ps(x, _mm256_set1_ps(pi), 30), signmask)));
			s = _mm256_mul_ps(sinmultiplier, sqrt(_mm256_sub_ps(_mm256_set1_ps(1.f), _mm256_mul_ps(result, result))));
		}
	};
}