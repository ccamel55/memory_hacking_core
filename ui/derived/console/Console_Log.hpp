#pragma once

#include "../../interfaces/UI_BaseControl.hpp"

namespace CORE {

	struct T_ConsoleVar;

	struct T_ConsoleLog {
		DWORD _col{};
		std::string _log{};
	};

	enum E_CONSOLE_LOG_TYPE {
		LOG_NORMAL,
		LOG_ERROR,
		LOG_INFO,
	};

	class Console_Log : public UI_BaseControl {
	public:
		Console_Log();
		~Console_Log();

		void render();
		void update();
		void input();

		void addToLog(const std::string& log, E_CONSOLE_LOG_TYPE type = LOG_NORMAL);
		void clearLog();
	protected:
		std::vector<T_ConsoleLog> _consoleLog{};
	};
}