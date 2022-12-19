#pragma once

#include <Windows.h>

inline uintptr_t GET_VIRTUAL(void* classPtr, size_t index) {
	return static_cast<uintptr_t>((*static_cast<int**>(classPtr))[index]);
}

inline uintptr_t GET_RELATIVE(uintptr_t address) {

	if (address == NULL) {
		return NULL;
	}

	const auto new_address = address + 0x1;
	const auto relative_offset = *(int32_t*)new_address;

	return new_address + sizeof(uintptr_t) + relative_offset;
}

// general purpose macros
#define FUNC_ARGS(...) (this, __VA_ARGS__ ); }
#define OFFSET( type, func, offset ) type& func() { return *reinterpret_cast<type*>( reinterpret_cast<uintptr_t>(this) + offset); }

#define V_FUNC(idx, func, sig) auto func { return reinterpret_cast<sig>((*(uintptr_t**)this)[idx]) FUNC_ARGS
#define P_FUNC(adr, func, sig) auto func { return reinterpret_cast<sig>(adr) FUNC_ARGS