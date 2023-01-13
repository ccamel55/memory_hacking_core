#include "Console_Input.hpp"
#include "Console_Form.hpp"

using namespace CORE;

Console_Input::Console_Input(const std::map<std::string_view, T_ConsoleVar>* cmds) : Form_TextInput(&_curInput, 60) {

	_commandsPtr = cmds;
	_curInput = "";

	_data = &_curInput;
	_inputPos = _data->size();

	_historyIndex = -1;
	_suggestedIndex = -1;
}

Console_Input::~Console_Input() {

}

void Console_Input::render() {

	Form_TextInput::render();
	
	// draw input suggestions
	if (!_useHistory && !_suggestedInputs.empty()) {

		UI_RENDER::drawRectFill(_suggestionPos._x - 2, _suggestionPos._y, getSize()._x / 2, (_suggestedInputs.size() * UI_CONTROL::CONSOLE_LOG_SPACING._y) + 2 + 2, UI_COLORS::CONTROL_FILL);
		UI_RENDER::drawRect(_suggestionPos._x - 2, _suggestionPos._y, getSize()._x / 2, (_suggestedInputs.size() * UI_CONTROL::CONSOLE_LOG_SPACING._y) + 2 + 2, UI_COLORS::GRAY);

		for (size_t i = 0; i < _suggestedInputs.size(); i++) {
			UI_RENDER::drawString(_suggestionPos._x + 5, _suggestionPos._y + (i * UI_CONTROL::CONSOLE_LOG_SPACING._y) + 1, UI_FONTS::CONSOLE_FONT, (i == _suggestedIndex) ? UI_COLORS::LIGHT_BLUE : UI_COLORS::WHITE, _suggestedInputs.at(i));
		}
	}
}

void Console_Input::update() {

	// we just pass the position straight through, no offset bs
	_absolutePosition = getPosition();
	_suggestionPos = _absolutePosition + POINT_INT(0, getSize()._y + UI_CONTROL::CONSOLE_LOG_PADDING._y + 10);
}

void Console_Input::input() {

	Form_TextInput::input();

	const auto lastKey = UI_INPUT::lastKey();

	if ((getFlags().hasFlag(E_UI_FLAGS::UI_BLOCKED)) && lastKey < 223 && lastKey >= 0 && UI_INPUT::isPressed(lastKey)) {

		if (lastKey == VK_UP) {

			if (_curInput.empty()) {
				_useHistory = true;
			}

			if (_useHistory && !_inputHistory.empty()) {
				
				if (_historyIndex <= 0) {
					_historyIndex = _inputHistory.size() - 1;
				}
				else {
					_historyIndex--;
				}

				_curInput = _inputHistory.at(_historyIndex);
				_inputPos = _curInput.size();
			}
			else if (!_useHistory && !_suggestedInputs.empty()) {

				// handle suggested
				if (_suggestedIndex == -1) {
					_suggestedIndex = 0;
				}
				else if (_suggestedIndex > 0) {
					_suggestedIndex--;
				}

				_curInput = _suggestedInputs.at(_suggestedIndex);
				_inputPos = _curInput.size();
			}
		}
		else if (lastKey == VK_DOWN) {

			if (_curInput.empty()) {
				_useHistory = true;
			}

			if (_useHistory) {
		
				if (_historyIndex >= static_cast<int>(_inputHistory.size() - 1)) {
					_historyIndex = 0;
				}
				else {
					_historyIndex++;
				}

				_curInput = _inputHistory.at(_historyIndex);
				_inputPos = _curInput.size();
			}
			else if (!_useHistory && !_suggestedInputs.empty()) {

				// handle suggested
				if (_suggestedIndex < static_cast<int>(_suggestedInputs.size() - 1)) {

					_curInput = _suggestedInputs.at(++_suggestedIndex);
					_inputPos = _curInput.size();
				}
			}
		}
		else {

			// update suggested list
			_suggestedInputs.clear();
			_suggestedIndex = -1;

			_useHistory = false;
			_historyIndex = -1;

			if (!_curInput.empty()) {

				for (const auto& s : *_commandsPtr) {

					if (_suggestedInputs.size() >= UI_CONTROL::CONSOLE_INPUT_COUNT) {
						break;
					}

					// any string that has prefix add!
					if (s.first.rfind(_curInput, 0) == 0) {
						_suggestedInputs.push_back(s.first.data());
					}
				}
			}
		}
	}
}

const std::string& Console_Input::getInput() const {
	return _curInput;
}

void Console_Input::clear() {

	_inputHistory.push_back(_curInput);
	_suggestedInputs.clear();

	_curInput.clear();
	_inputPos = 0;

	_historyIndex = -1;
	_suggestedIndex = -0;
}