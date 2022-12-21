#pragma once

#include <Windows.h>
#include <vector>

inline uintptr_t GET_VIRTUAL(void* classPtr, size_t index) {
	return static_cast<uintptr_t>((*static_cast<int**>(classPtr))[index]);
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
std::vector<T> FILLED_VECTOR(const T& fill) {

	std::vector<T> ret(S);
	std::fill(ret.begin(), ret.begin() + S, fill);

	return ret;
}

// general purpose macros
#define FUNC_ARGS(...) (this, __VA_ARGS__ ); }
#define OFFSET( type, func, offset ) type& func() { return *reinterpret_cast<type*>( reinterpret_cast<uintptr_t>(this) + offset); }

#define V_FUNC(idx, func, sig) auto func { return reinterpret_cast<sig>((*(uintptr_t**)this)[idx]) FUNC_ARGS
#define P_FUNC(adr, func, sig) auto func { return reinterpret_cast<sig>(adr) FUNC_ARGS