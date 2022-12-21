#include "PatternScanner.hpp"

using namespace CORE;

std::vector<unsigned long> C_PatternScanner::patternToBytes(const std::string& pattern) {
	
	// convert a pattern string to an array of byte values, using short because we need a sign for "any byte" which is -1
	std::vector<unsigned long> ret{};

	// get start and end of character array
	const auto charStart = pattern.data();
	const auto charEnd = charStart + pattern.length();

	for (char* curChar = const_cast<char*>(charStart); curChar < charEnd; curChar++) {

		// ? means any byte so add -1 and skip
		if (*curChar == '?') {

			ret.push_back(-1);
			curChar++;

			continue;
		}

		// convert from base16 to base 10 and store in array
		ret.push_back(strtoul(curChar, &curChar, 16));
	}

	return ret;
}

uintptr_t C_PatternScanner::addressFromPattern(HMODULE baseAddress, const std::string& pattern) {

	// baseAddress is base address of the module we want to look in
	// basic premise of this is, look through all the bytes of the module, and try match it to our pattern

	const auto& patternByteArray = patternToBytes(pattern);
	const auto curByte = reinterpret_cast<uint8_t*>(baseAddress);

	const auto dosHeaders = reinterpret_cast<PIMAGE_DOS_HEADER>(baseAddress);
	const auto ntHeaders = reinterpret_cast<PIMAGE_NT_HEADERS>(curByte + dosHeaders->e_lfanew);

	for (uintptr_t i = 0; i < ntHeaders->OptionalHeader.SizeOfImage - patternByteArray.size(); i++) {

		bool foundAddress = true;

		// check sequence of bytes stating from current
		for (uintptr_t j = 0; j < patternByteArray.size(); j++) {

			// if pattern isnt "any byte" and current does not equal current pattern leave!
			if (curByte[i + j] != patternByteArray[j] && patternByteArray[j] != -1) {
				foundAddress = false;
				break;
			}
		}

		// oh look we got it yay!!
		if (foundAddress) {
			return reinterpret_cast<uintptr_t>(&curByte[i]);
		}
	}

	return NULL;
}