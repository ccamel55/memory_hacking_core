#pragma once

#include <iostream>

// https://gist.github.com/ruby0x1/81308642d0325fd386237cfa3b44785c

namespace CORE {

#if _WIN32

	using hash_t = uint32_t;

	class C_FN1V {
	public:
		// compile time hash
		constexpr static hash_t getCT(const char* szString, const hash_t uValue = OFFSET_BASIS) noexcept {
			return (szString[0] == '\0') ? uValue : getCT(&szString[1], (uValue ^ hash_t(szString[0])) * FNV_PRIME);
		}

		// runtime hash
		inline static hash_t get(const char* szString) {

			hash_t uHashed = OFFSET_BASIS;

			for (std::size_t i = 0U; i < strlen(szString); i++) {

				uHashed ^= szString[i];
				uHashed *= FNV_PRIME;
			}

			return uHashed;
		}

	private:
		static constexpr hash_t FNV_PRIME = 0x1000193;
		static constexpr hash_t OFFSET_BASIS = 0x811c9dc5;
	};

#else

	using hash_t = uint64_t;

	class C_FN1V {
	public:
		// compile time hash
		constexpr static hash_t getCT(const char* szString, const hash_t uValue = OFFSET_BASIS) noexcept {
			return (szString[0] == '\0') ? uValue : getCT(&szString[1], (uValue ^ hash_t(szString[0])) * FNV_PRIME);
		}

		// runtime hash
		inline static hash_t get(const char* szString) {

			hash_t uHashed = OFFSET_BASIS;

			for (std::size_t i = 0U; i < strlen(szString); i++) {

				uHashed ^= szString[i];
				uHashed *= FNV_PRIME;
			}

			return uHashed;
		}

	private:
		static constexpr hash_t FNV_PRIME = 0x1000193;
		static constexpr hash_t OFFSET_BASIS = 0x811c9dc5;
	};

#endif
}