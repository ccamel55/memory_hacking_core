#pragma once

#include <Windows.h>

template <typename T>
class Singleton {
public:
	static T& get() {

		// make one instance and one instance only
		static T instance;
		return instance;
	}

	// no!! we dont want to accedently create a new instance
	Singleton(const Singleton& s) = delete;
	void operator= (const Singleton&) = delete;
protected:

	// boo
	Singleton() { };
	~Singleton() { };
};

inline static uintptr_t GET_VIRTUAL(void* classPtr, size_t idx) {
	return static_cast<uintptr_t>((*static_cast<int**>(classPtr))[idx]);
}

// general purpose macros
#define FUNC_ARGS(...) (this, __VA_ARGS__ ); }
#define OFFSET( type, func, offset ) type& func() { return *reinterpret_cast<type*>( reinterpret_cast<uintptr_t>(this) + offset); }

#define V_FUNC(idx, func, sig) auto func { return reinterpret_cast<sig>((*(uintptr_t**)this)[idx]) FUNC_ARGS
#define P_FUNC(adr, func, sig) auto func { return reinterpret_cast<sig>(adr) FUNC_ARGS