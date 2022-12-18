#pragma once

#include <Windows.h>

#include <string>
#include <vector>

namespace CORE {

	class C_PatternScanner {
	public:
		static uintptr_t addressFromPattern(HMODULE baseAddress, const std::string& pattern);
	private:
		static std::vector<unsigned long> patternToBytes(const std::string& pattern);
	};
}