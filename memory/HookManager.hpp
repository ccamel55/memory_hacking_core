#pragma once

#include "../../Singleton.hpp"
#include "../../deps/minhook/include/MinHook.h"

#include <unordered_map>

namespace CORE {

	struct T_HookedFunction {
		void* m_pFunc;
		void* m_pOrig;
	};

	class C_HookManager : public Singleton<C_HookManager> {
	public:
		C_HookManager() {
			m_mHookedFunctions;

			// Initialize MinHook.
			MH_Initialize();
		}

		~C_HookManager() {
			m_mHookedFunctions.clear();

			// destroy the min the hook!!!
			MH_Uninitialize();
		}

		bool hookFunction(size_t id, void* func, void* replace);
		bool unhookFunction(size_t id);
		bool unhookAll();

		template <typename T> 
		T getOriginal(size_t id) {
			return reinterpret_cast<T>(m_mHookedFunctions.at(id).m_pOrig);
		}

	private:
		std::unordered_map<size_t, T_HookedFunction> m_mHookedFunctions;
	};
}