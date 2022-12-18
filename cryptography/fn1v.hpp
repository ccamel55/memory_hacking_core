#pragma once

#include <iostream>

namespace CORE {

	// 32 bit only!
  
    using hash_t = unsigned int;

    class C_FN1V {
    public:
		// compile time hash
		constexpr static hash_t get_ct(const char* szString, const hash_t uValue = OFFSET_BASIS) noexcept {
			return (szString[0] == '\0') ? uValue : get_ct(&szString[1], (uValue ^ hash_t(szString[0])) * FNV_PRIME);
		}

		// runtime hash
		inline static hash_t get(const char* szString) {

			hash_t uHashed = OFFSET_BASIS;

			for (std::size_t i = 0U; i < strlen(szString); ++i) {
				uHashed ^= szString[i];
				uHashed *= FNV_PRIME;
			}

			return uHashed;
		}

    private:
        static const hash_t FNV_PRIME = 16777619u;
        static const hash_t OFFSET_BASIS = 2166136261u;
    };
}