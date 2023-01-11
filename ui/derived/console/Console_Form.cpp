#include "Console_Form.hpp"

#include "../../../config/Config.hpp"

#include <sstream>
#include <algorithm> 
#include <cctype>
#include <locale>

using namespace CORE;

namespace {

	inline void ltrim(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
	}

	// trim from end (in place)
	inline void rtrim(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	inline void trim(std::string& s) {
		rtrim(s);
		ltrim(s);
	}

	inline std::vector<std::string> splitString(const std::string& s) {

		std::stringstream ss(s);

		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end{};

		std::vector<std::string> vstrings(begin, end);
		std::copy(vstrings.begin(), vstrings.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

		return vstrings;
	}
}

Console_Form::Console_Form() {

	_name = "Console";
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONSOLE;

	_size = UI_CONSOLE::FORM_SIZE;
	_position = { 50, 50 }; // default position

	_inputBox = std::make_shared<Console_Input>(&_commands);
	_logBox = std::make_shared<Console_Log>();

	addCommand("help", "prints out all commands");
	setData("help", [&, this]() { for (const auto& c : _commands) { _logBox->addToLog(c.first.data() + std::string(" : ") + c.second._description.data()); } });

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

	if (_inputBox->getFlags() & E_UI_FLAGS::UI_BLOCKED) {

		// if input we have entered a command 
		if (UI_INPUT::isPressed(VK_RETURN)) {

			auto cmd = _inputBox->getInput();
			trim(cmd);

			if (cmd.size() > 0) {

				// handle input here
				_logBox->addToLog("] " + cmd);
	
				const auto& stringSplit = splitString(cmd);

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

							const auto val = std::stof(stringSplit.at(1));

							if (val >= cmd._data._float._min && val <= cmd._data._float._max) {
								*cmd._data._float._data = val;
							}
							else {
								_logBox->addToLog(std::format("out of range (min: {}, max{})", cmd._data._float._min, cmd._data._float._max), E_CONSOLE_LOG_TYPE::LOG_ERROR);
							}
						}

						break;
					case VAR_INT:

						if (stringSplit.size() > 1) {

							const auto val = std::stoi(stringSplit.at(1));

							if (val >= cmd._data._int._min && val <= cmd._data._int._max) {
								*cmd._data._int._data = val;
							}
							else {
								_logBox->addToLog(std::format("out of range (min: {}, max{})", cmd._data._int._min, cmd._data._int._max), E_CONSOLE_LOG_TYPE::LOG_ERROR);
							}
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