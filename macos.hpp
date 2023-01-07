#pragma once

#include <vector>

template <typename T = void*>
constexpr T GET_VIRTUAL_FN(void* thisptr, std::size_t nIndex) {
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

template <typename T, std::size_t S>
inline std::vector<T> FILLED_VECTOR(const T& fill) {

	std::vector<T> ret(S);
	std::fill(ret.begin(), ret.begin() + S, fill);

	return ret;
}