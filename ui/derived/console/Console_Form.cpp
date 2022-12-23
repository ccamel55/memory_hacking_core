#include "Console_Form.hpp"

using namespace CORE;

Console_Form::Console_Form() {

	_name = "Console";
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONSOLE;

	_size = UI_CONSOLE::FORM_SIZE;
	_position = { 50, 50 }; // default position

	addCommand( "help", T_ConsoleVar(E_CONSOLE_VAR_TYPE::VAR_INTERNAL, "help", "prints out all commands") );
	addCommand( "clear", T_ConsoleVar(E_CONSOLE_VAR_TYPE::VAR_INTERNAL, "clear", "clears the console") );
}

Console_Form::~Console_Form() {

}

void Console_Form::render() {

	UI_BaseForm::render();

	// info box
	{
		UI_RENDER::drawRectFilled(_logPos._x, _logPos._y, _logSize._x, _logSize._y, UI_COLORS::CONSOLE_FILL);
		UI_RENDER::drawRect(_logPos._x, _logPos._y, _logSize._x, _logSize._y, UI_COLORS::GRAY);

		// testing lol
		int i = 0;

		for (const auto& val : _commands) {

			UI_RENDER::drawText(_logPos._x + 20, _logPos._y + 10 + (i * 20), UI_FONTS::CONSOLE_FONT, UI_COLORS::WHITE, val.first.data());
			UI_RENDER::drawText(_logPos._x + 120, _logPos._y + 10 + (i * 20), UI_FONTS::CONSOLE_FONT, UI_COLORS::WHITE, val.second._description.data());

			i++;
		}
	}

	// text input area
	{
		UI_RENDER::drawRectFilled(_inputPos._x, _inputPos._y, _inputSize._x, _inputSize._y, UI_COLORS::CONSOLE_FILL);
		UI_RENDER::drawRect(_inputPos._x, _inputPos._y, _inputSize._x, _inputSize._y, UI_COLORS::GRAY);
	}
}

void Console_Form::update() {

	UI_BaseForm::update();

	const auto controlSize = POINT_INT(_controlSize._x - (UI_CONTROL::GROUPBOX_PADDING._x * 2), _controlSize._y - (UI_CONTROL::GROUPBOX_PADDING._y * 2));
	const auto controlPos = POINT_INT(_controlPosition._x + UI_CONTROL::GROUPBOX_PADDING._x, _controlPosition._y + UI_CONTROL::GROUPBOX_PADDING._y);

	// set size and position of input and logger
	_logPos = controlPos;
	_logSize = POINT_INT(controlSize._x, controlSize._y - UI_CONSOLE::INPUT_BOX_SIZE._y - UI_CONTROL::GROUPBOX_PADDING._y);

	_inputPos = POINT_INT(controlPos._x, controlPos._y + controlSize._y - UI_CONSOLE::INPUT_BOX_SIZE._y);
	_inputSize = POINT_INT(controlSize._x, UI_CONSOLE::INPUT_BOX_SIZE._y);
}

void Console_Form::input() {

	UI_BaseForm::input();

	
}

void Console_Form::addCommand(std::string_view name, T_ConsoleVar var) {

	if (_commands.count(name) > 0) {
		throw std::exception("command already exists");
	}

	_commands.insert({ name, std::move(var) });
}