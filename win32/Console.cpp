#include "Console.hpp"

using namespace CORE;

void C_Console::attatch() {

	if (!AllocConsole()) {
		return;
	}
	
	// map stdin, stdout and stderr to our console
	freopen_s(reinterpret_cast<_iobuf**>(stdin), "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<_iobuf**>(stdout), "CONOUT$", "w", stdout);
	freopen_s(reinterpret_cast<_iobuf**>(stderr), "CONOUT$", "w", stderr);

	_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// set console attribtes
	SetConsoleTitleA("sdk");
}

void C_Console::detatch() {

	// unmap stdin, stdout, stderr from console
	fclose(static_cast<_iobuf*>(stdin));
	fclose(static_cast<_iobuf*>(stdout));
	fclose(static_cast<_iobuf*>(stderr));

	FreeConsole();
}

void C_Console::println(const std::string& str) {
	// just print with new line
	std::cout << str << "\n";
}