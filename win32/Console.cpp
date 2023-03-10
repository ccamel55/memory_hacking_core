#include "Console.hpp"

using namespace CORE;

void C_Console::attatch(const std::string& title) {

#ifdef MEMORY_CORE_LOGGING

	if (!AllocConsole()) {
		return;
	}

	// map stdin, stdout and stderr to our console
	freopen_s(reinterpret_cast<_iobuf**>(stdin), "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<_iobuf**>(stdout), "CONOUT$", "w", stdout);
	freopen_s(reinterpret_cast<_iobuf**>(stderr), "CONOUT$", "w", stderr);

	_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// set console attribtes
	SetConsoleTitleA(title.c_str());

#endif // MEMORY_CORE_LOGGING

}

void C_Console::detatch() {

#ifdef MEMORY_CORE_LOGGING

	// unmap stdin, stdout, stderr from console
	fclose(static_cast<_iobuf*>(stdin));
	fclose(static_cast<_iobuf*>(stdout));
	fclose(static_cast<_iobuf*>(stderr));

	FreeConsole();

#endif // MEMORY_CORE_LOGGING
}

void C_Console::println(const std::string& str) {

#ifdef MEMORY_CORE_LOGGING

	// just print with new line
	std::cout << str << "\n";

#endif // MEMORY_CORE_LOGGING
}