#pragma once

#include "../singleton.hpp"

#include <memory>
#include <unordered_map>

namespace CORE {

	class C_MEM_PROC
	{
	public:
		C_MEM_PROC(LPVOID address, uint32_t size, DWORD flags) : _address(address), _size(size), _flags(0)
		{
			VirtualProtect(_address, _size, flags, &_flags);
		}

		~C_MEM_PROC()
		{
			VirtualProtect(_address, _size, _flags, &_flags);
		}

	public:
		uint32_t _size{};
		DWORD _flags{};
		LPVOID _address{};
	};

	struct T_VirtualClass {
		void hookIndex(size_t index, void* func);
		void unhookIndex(size_t index);
		void unhookAll();
		size_t getVirtualClassSize();

		template <typename T>
		T getOriginal(size_t index) {
			return reinterpret_cast<T>(_orig[index]);
		}

		uintptr_t* _orig{};
		uintptr_t** _vTable{};

		uintptr_t _vTableLength{};
		std::unique_ptr<uintptr_t[]> _replace{};
	};

	class C_VirtualFnHookManager : public Singleton<C_VirtualFnHookManager> {
	public:
		T_VirtualClass* attatchVirtualClass(size_t id, void* base);
		T_VirtualClass* getVirtualClass(size_t id);
		void unhookAll();
	private:
		std::unordered_map<size_t, T_VirtualClass> _hookedFunctions{};
	};
}