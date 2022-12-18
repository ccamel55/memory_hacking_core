#include "HookManager.hpp"

using namespace CORE;

bool C_HookManager::hookFunction(size_t id, void* func, void* replace) {

	T_HookedFunction curFunc;
	curFunc.m_pFunc = func;
	
	if (MH_CreateHook(func, replace, reinterpret_cast<void**>(&curFunc.m_pOrig)) != MH_OK) {
		return false;
	}

	if (MH_EnableHook(func) != MH_OK) {
		return false;
	}

	// move into map
	m_mHookedFunctions.insert({id, std::move(curFunc)});
	return true;
}

bool C_HookManager::unhookFunction(size_t id) {

	// we havnt hooked the function
	if (m_mHookedFunctions.count(id) == 0) {
		return false;
	}

	auto& curFunc = m_mHookedFunctions.at(id);

	if (MH_DisableHook(curFunc.m_pFunc) != MH_OK) {
		return false;
	}

	curFunc.m_pFunc = NULL;
	curFunc.m_pOrig = NULL;

	return true;
}

bool C_HookManager::unhookAll() {

	bool failed = false;

	// loop all and unhook
	for (auto &curFunc : m_mHookedFunctions) {

		if (curFunc.second.m_pFunc != NULL) {

			if (MH_DisableHook(curFunc.second.m_pFunc) != MH_OK) {
				failed = true;
				continue;
			}

			curFunc.second.m_pFunc = NULL;
			curFunc.second.m_pOrig = NULL;
		}
	}

	return !failed;
}