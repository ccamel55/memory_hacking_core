#pragma once

#include "../singleton.hpp"

#include "../deps/minhook/include/MinHook.h"

#include <unordered_map>

namespace CORE {

	struct T_HookedFunction {
		void* _func;
		void* _orig;
	};

	class C_DetourHookManager : public Singleton<C_DetourHookManager> {
	public:
		C_DetourHookManager() {

			// Initialize MinHook.
			MH_Initialize();
		}

		~C_DetourHookManager() {
			_hookedFunctions.clear();

			// destroy the min the hook!!!
			MH_Uninitialize();
		}

		void hookFunction(size_t id, void* func, void* replace);
		void unhookFunction(size_t id);
		void unhookAll();

		template <typename T> 
		T getOriginal(size_t id) {
			return reinterpret_cast<T>(_hookedFunctions.at(id)._orig);
		}

	private:
		std::unordered_map<size_t, T_HookedFunction> _hookedFunctions{};
	};
}