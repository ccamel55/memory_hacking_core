#pragma once

#include "../singleton.hpp"

#include <Windows.h>

#include <iostream>
#include <format>

namespace CORE {

	class C_Console : public Singleton<C_Console> {
	public:
		C_Console() {
			_handle = nullptr;
		}

		~C_Console() {
			_handle = nullptr;
		}

		void attatch();
		void detatch();
		void println(const std::string& str);
	private:
		HANDLE _handle;
	};
}