#include "Console_Form.hpp"

#include "../../../config/Config.hpp"

#define FMT_HEADER_ONLY
#include "../../../deps/fmt/include/fmt/core.h"

#include <sstream>
#include <algorithm> 
#include <cctype>
#include <locale>

using namespace CORE;

Console_Form::Console_Form() : UI_BaseForm("Console", UI_CONSOLE::FORM_SIZE) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONSOLE;
	
	_inputBox = std::make_shared<Console_Input>(&_commands);
	_logBox = std::make_shared<Console_Log>();

	addCommand("help", "prints out all commands");
	setData("help", [&, this]() { for (const auto& c : _commands) {
		
		switch (c.second._type)
		{
		case E_CONSOLE_VAR_TYPE::VAR_INT:
			_logBox->addToLog(fmt::format("{} : {} (min: {}, max {})", c.first.data(), c.second._description.data(), c.second._data._int._min, c.second._data._int._max));
			break;
		case E_CONSOLE_VAR_TYPE::VAR_FLOAT:
			_logBox->addToLog(fmt::format("{} : {} (min: {}, max{})", c.first.data(), c.second._description.data(), c.second._data._float._min, c.second._data._float._max));
			break;
		default:
			_logBox->addToLog(fmt::format("{} : {}", c.first.data(), c.second._description.data()));
			break;
		}

	} });

	addCommand("clear", "prints out all commands");
	setData("clear", [&, this]() { _logBox->clearLog(); });
}

Console_Form::~Console_Form() {

}

void Console_Form::render() {

	UI_BaseForm::render();

	_inputBox->render();
	_logBox->render();
}

void Console_Form::update() {

	UI_BaseForm::update();

	const auto controlPos = POINT_INT(_controlPosition._x + UI_CONTROL::GROUPBOX_PADDING._x, _controlPosition._y + UI_CONTROL::GROUPBOX_PADDING._y);
	const auto controlSize = POINT_INT(_controlSize._x - (UI_CONTROL::GROUPBOX_PADDING._x * 2), _controlSize._y - (UI_CONTROL::GROUPBOX_PADDING._y * 2));

	// set size and position of input and logger
	_logBox->setPosition(controlPos);
	_logBox->setSize(POINT_INT(controlSize._x, controlSize._y - UI_CONSOLE::INPUT_BOX_SIZE._y - UI_CONTROL::GROUPBOX_PADDING._y));
	_logBox->update();

	_inputBox->setPosition(POINT_INT(controlPos._x, controlPos._y + controlSize._y - UI_CONSOLE::INPUT_BOX_SIZE._y));
	_inputBox->setSize(POINT_INT(controlSize._x, UI_CONSOLE::INPUT_BOX_SIZE._y));
	_inputBox->update();
}

void Console_Form::input() {

	UI_BaseForm::input();

	_inputBox->input();
	_logBox->input();

	if (_inputBox->getFlags().hasFlag(E_UI_FLAGS::UI_BLOCKED)) {

		// if input we have entered a command 
		if (UI_INPUT::isPressed(VK_RETURN)) {

			auto cmd = _inputBox->getInput();
			STRING::TRIM(cmd);

			if (cmd.size() > 0) {

				// handle input here
				_logBox->addToLog("] " + cmd);
	
				const auto stringSplit = STRING::SPLIT_STRING(cmd);

				if (_commands.count(stringSplit.at(0)) > 0) {

					const auto& cmd = _commands.at(stringSplit.at(0));

					switch (cmd._type)
					{
					case VAR_INTERNAL:
					case VAR_CALLBACK:

						if (cmd._callback) {
							cmd._callback();
						}

						break;
					case VAR_FLOAT:

						if (stringSplit.size() > 1) {

							try {
								const auto val = std::stof(stringSplit.at(1));

								if (val >= cmd._data._float._min && val <= cmd._data._float._max) {
									*cmd._data._float._data = val;
								}
								else {
									_logBox->addToLog(fmt::format("out of range (min: {}, max{})", cmd._data._float._min, cmd._data._float._max), E_CONSOLE_LOG_TYPE::LOG_ERROR);
								}
							}
							catch (...) {
								_logBox->addToLog("invalid type (expected float)", E_CONSOLE_LOG_TYPE::LOG_ERROR);
							}
						}
						else if (stringSplit.size() == 1) {
							_logBox->addToLog(fmt::format("current state = {} : {} (min: {}, max{})", *cmd._data._float._data, cmd._description.data(), cmd._data._float._min, cmd._data._float._max));
						}

						break;
					case VAR_INT:

						if (stringSplit.size() > 1) {

							try {
								const auto val = std::stoi(stringSplit.at(1));

								if (val >= cmd._data._int._min && val <= cmd._data._int._max) {
									*cmd._data._int._data = val;
								}
								else {
									_logBox->addToLog(fmt::format("out of range (min: {}, max{})", cmd._data._int._min, cmd._data._int._max), E_CONSOLE_LOG_TYPE::LOG_ERROR);
								}
							}
							catch (...) {
								_logBox->addToLog("invalid type (expected int)", E_CONSOLE_LOG_TYPE::LOG_ERROR);
							}				
						}
						else if (stringSplit.size() == 1) {
							_logBox->addToLog(fmt::format("current state = {} : {} (min: {}, max{})", *cmd._data._int._data, cmd._description.data(), cmd._data._int._min, cmd._data._int._max));
						}

						break;
					default:
						break;
					}

				}
				else {
					_logBox->addToLog("could not find command", E_CONSOLE_LOG_TYPE::LOG_ERROR);
				}
			}

			_inputBox->clear();
		}
	}
}

void Console_Form::addCommand(std::string_view name, std::string_view description) {

	if (_commands.count(name) > 0) {
		throw std::exception("command already exists");
	}

	T_ConsoleVar newVar{};

	newVar._name = name;
	newVar._description = description;

	_commands.insert({ name, std::move(newVar) });
}

void Console_Form::setData(std::string_view name, uint32_t var, float min, float max) {

	if (_commands.count(name) == 0) {
		throw std::exception("invalid data for command");
	}

	auto& command = _commands.at(name);
	command._type = E_CONSOLE_VAR_TYPE::VAR_FLOAT;

	command._data._float._data = &C_Config::get().getVar<float>(var);
	command._data._float._min = min;
	command._data._float._max = max;
}

void Console_Form::setData(std::string_view name, uint32_t var, int min, int max) {

	if (_commands.count(name) == 0) {
		throw std::exception("invalid data for command");
	}

	auto& command = _commands.at(name);
	command._type = E_CONSOLE_VAR_TYPE::VAR_INT;

	command._data._int._data = &C_Config::get().getVar<int>(var);
	command._data._int._min = min;
	command._data._int._max = max;
}

void Console_Form::setData(std::string_view name, std::function<void()> callback) {

	if (_commands.count(name) == 0 || (_commands.at(name)._type != E_CONSOLE_VAR_TYPE::VAR_CALLBACK && _commands.at(name)._type != E_CONSOLE_VAR_TYPE::VAR_INTERNAL)) {
		throw std::exception("invalid data for command");
	}

	auto& command = _commands.at(name);

	command._type = E_CONSOLE_VAR_TYPE::VAR_CALLBACK;
	command._callback = std::move(callback);
}