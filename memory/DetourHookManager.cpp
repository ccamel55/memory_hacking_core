#include "DetourHookManager.hpp"

#include "../macos.hpp"

#include <exception>

using namespace CORE;

void C_DetourHookManager::hookFunction(size_t id, void* func, void* replace) {

	T_HookedFunction curFunc{};
	curFunc._func = func;
	
	if (MH_CreateHook(curFunc._func, replace, reinterpret_cast<void**>(&curFunc._orig)) != MH_OK) {
		throw std::exception("failed to hook.");
	}

	if (MH_EnableHook(curFunc._func) != MH_OK) {
		throw std::exception("failed to enable hook.");
	}

	// move into map
	_hookedFunctions.insert({id, std::move(curFunc)});
}

void C_DetourHookManager::unhookFunction(size_t id) {

	// we havnt hooked the function
	if (_hookedFunctions.count(id) == 0) {
		throw std::exception("could not find function");
	}

	auto& curFunc = _hookedFunctions.at(id);

	if (MH_DisableHook(curFunc._func) != MH_OK) {
		throw std::exception("failed to unhook.");
	}

	curFunc._func = NULL;
	curFunc._orig = NULL;
}

void C_DetourHookManager::unhookAll() {

	// loop all and unhook
	for (auto &curFunc : _hookedFunctions) {

		if (curFunc.second._func != NULL) {

			if (MH_DisableHook(curFunc.second._func) != MH_OK) {
				throw std::exception("failed to unhook all.");
			}

			curFunc.second._func = NULL;
			curFunc.second._orig = NULL;
		}
	}
}