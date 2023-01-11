#pragma once

#include <vector>
#include <string>

namespace CORE {

	namespace MEMORY {

		template <typename T = void*>
		constexpr T GET_VIRTUAL_FN(void* thisptr, size_t nIndex) {
			return (*static_cast<T**>(thisptr))[nIndex];
		}

		template <typename T, typename ... Args_t>
		constexpr T CALL_VIRTUAL_FN(void* thisptr, size_t nIndex, Args_t... argList)
		{
			using VirtualFn = T(__thiscall*)(void*, decltype(argList)...);
			return (*static_cast<VirtualFn**>(thisptr))[nIndex](thisptr, argList...);
		}

		template <typename T, typename ... Args_t>
		constexpr T CALL_FN(void* thisptr, uintptr_t offset, Args_t... argList)
		{
			using Fn = T(__thiscall*)(void*, decltype(argList)...);
			return reinterpret_cast<Fn>(offset)(thisptr, argList...);
		}

		inline uintptr_t GET_RELATIVE(uintptr_t address) {

			if (address == NULL) {
				return NULL;
			}

			const auto new_address = address + 0x1;
			const auto relative_offset = *(int*)new_address; // int must be 4 bytes

			return new_address + sizeof(uintptr_t) + relative_offset;
		}
	};

	namespace ARRAY {

		template <typename T, size_t S>
		inline std::vector<T> FILLED_VECTOR(const T& fill) {

			std::vector<T> ret(S);
			std::fill(ret.begin(), ret.begin() + S, fill);

			return ret;
		}
	}

	namespace STRING {

		static std::string TRUNCATE(const std::string& str, size_t maxLength, bool show_ellipsis = true) {

			if (str.length() > maxLength) {

				if (show_ellipsis) {
					return str.substr(0, maxLength) + "...";
				}
				else {
					return str.substr(0, maxLength);
				}		
			}
				
			return str;
		}


	}
};


