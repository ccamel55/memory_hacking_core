#include "Console_Log.hpp"

using namespace CORE;

Console_Log::Console_Log() {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_size = { 0, 100 }; // temporary
}

Console_Log::~Console_Log() {

}

void Console_Log::render() {

	const auto& pos = getPosition();
	const auto& size = getSize();

	UI_RENDER::drawRectFilled(pos._x, pos._y, size._x, size._y, UI_COLORS::CONSOLE_FILL);
	UI_RENDER::drawRect(pos._x, pos._y, size._x, size._y, UI_COLORS::GRAY);

	for (size_t i = 0; i < _consoleLog.size(); i++) {

		auto& val = _consoleLog.at(i);
		UI_RENDER::drawText(pos._x + UI_CONTROL::CONSOLE_LOG_PADDING._x, pos._y + UI_CONTROL::CONSOLE_LOG_PADDING._y + (i * UI_CONTROL::CONSOLE_LOG_SPACING._y), UI_FONTS::CONSOLE_FONT, val._col, val._log);
	}
}

void Console_Log::update() {

}

void Console_Log::input() {

}

void Console_Log::addToLog(const std::string& log, E_CONSOLE_LOG_TYPE type) {

	DWORD col = UI_COLORS::WHITE;

	switch (type)
	{
	case CORE::LOG_ERROR:
		col = UI_COLORS::RED;
		break;
	case CORE::LOG_INFO:
		col = UI_COLORS::LIGHT_BLUE;
		break;
	default:
		break;
	}

	_consoleLog.emplace_back(T_ConsoleLog{ col, log });

	// remove if too many
	while (((UI_CONTROL::CONSOLE_LOG_PADDING._y * 2) + (_consoleLog.size() * UI_CONTROL::CONSOLE_LOG_SPACING._y)) > static_cast<size_t>(getSize()._y)) {
		_consoleLog.erase(_consoleLog.begin());
	}
}

void Console_Log::clearLog() {
	_consoleLog.clear();
}