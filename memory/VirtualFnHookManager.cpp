#include "VirtualFnHookManager.hpp"

using namespace CORE;

T_VirtualClass* C_VirtualFnHookManager::attatchVirtualClass(size_t id, void* base) {
	
	T_VirtualClass curClass{};
	
	//copy current vtable over 
	curClass._vTable = (uintptr_t**)base;
	curClass._orig = *curClass._vTable;

	auto protect = C_MEM_PROC(curClass._vTable, sizeof(uintptr_t), PAGE_READWRITE);

	//create new vtable 2 replace
	curClass._vTableLength = curClass.getVirtualClassSize();
	curClass._replace = std::make_unique<uintptr_t[]>(curClass._vTableLength + 1);

	//copy over new table to old table pos in memory
	std::copy(curClass._orig - 1, curClass._orig + curClass._vTableLength, curClass._replace.get());
	*curClass._vTable = &curClass._replace[1];

	_hookedFunctions.insert({ id, std::move(curClass) });

	return &_hookedFunctions.at(id);
}

T_VirtualClass* C_VirtualFnHookManager::getVirtualClass(size_t id) {
	return &_hookedFunctions.at(id);
}

void C_VirtualFnHookManager::unhookAll() {

	for (auto& vmt : _hookedFunctions) {

		if (!vmt.second._orig) {
			continue;
		}
	
		auto protect = C_MEM_PROC(vmt.second._vTable, sizeof(uintptr_t), PAGE_READWRITE);

		//replace new table with old table
		*vmt.second._vTable = vmt.second._orig;
	}
}

void T_VirtualClass::hookIndex(size_t index, void* func)
{
	if (index < 0 || index > _vTableLength) {
		return;
	}
		
	//swap function in new replacement table with our own
	_replace[index + 1] = (uintptr_t)(func);
}

void T_VirtualClass::unhookIndex(size_t index) {

	if (index < 0 || index > _vTableLength) {
		return;
	}

	//replace a sepcific function in new table with original
	_replace[index + 1] = _orig[index];
}

void T_VirtualClass::unhookAll() {

	if (!_orig) {
		return;
	}

	auto protect = C_MEM_PROC(_vTable, sizeof(uintptr_t), PAGE_READWRITE);

	//replace new table with old table
	*_vTable = _orig;
}

size_t T_VirtualClass::getVirtualClassSize()
{
	size_t length = 0;

	for (length = 0; _orig[length]; length++) {

		if (IS_INTRESOURCE(_orig[length])) {
			break;
		}
	}

	return length;
}