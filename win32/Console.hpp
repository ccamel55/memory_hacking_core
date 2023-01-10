#pragma once

#include "../singleton.hpp"

#include <Windows.h>

#include <iostream>

#include <format>
#include <string>

namespace CORE {

	class C_Console : public Singleton<C_Console> {
	public:
		void attatch(const std::string& title);
		void detatch();
		void println(const std::string& str);
	private:
		HANDLE _handle{};
	};
}