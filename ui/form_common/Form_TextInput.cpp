#include "Form_TextInput.hpp"
#include "Form_Groupbox.hpp"

using namespace CORE;

Form_TextInput::Form_TextInput(std::string* data, size_t maxLength) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;

	_data = data;
	_inputPos = _data->size();

	_size = { 0, 26 };
	_maxLength = maxLength;
}

Form_TextInput::~Form_TextInput() {

}

void Form_TextInput::render() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	UI_RENDER::drawRectFill(pos._x, pos._y, size._x, size._y, (getFlags() & E_UI_FLAGS::UI_BLOCKED) ? UI_COLORS::CONTROL_FILL_2 : UI_COLORS::CONTROL_FILL);
	UI_RENDER::drawRect(pos._x, pos._y, size._x, size._y, UI_COLORS::CONTROL_OUTLINE);

	// draw text
	UI_RENDER::drawString(pos._x + 8, pos._y + (size._y / 2), UI_FONTS::CONTROL_FONT, UI_COLORS::WHITE, *_data, E_FONT_FLAGS::FONT_CENTER_Y);

	// draw cursor
	if (getFlags() & E_UI_FLAGS::UI_BLOCKED) {
		
		const auto cursorPos = POINT_INT(pos._x + 8 + UI_RENDER::getStringWidth(UI_FONTS::CONTROL_FONT, _data->substr(0, _inputPos)), pos._y + (size._y / 2) + (UI_RENDER::getStringHeight(UI_FONTS::CONTROL_FONT) / 2));
		UI_RENDER::drawRectFill(cursorPos._x, cursorPos._y, 4, 1, UI_COLORS::LIGHT_GRAY);
	}
}

void Form_TextInput::update() {

	auto parent = dynamic_pointer_cast<Form_Groupbox>(getParent());
	_absolutePosition = parent->getControlPosition() + getPosition();
}

void Form_TextInput::input() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	if (UI_INPUT::isPressed(VK_LBUTTON)) {

		if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {
			getFlags() |= E_UI_FLAGS::UI_BLOCKED;
		}
		else {
			getFlags() &= ~E_UI_FLAGS::UI_BLOCKED;
		}
	}
	else if (getFlags() & E_UI_FLAGS::UI_BLOCKED) {

		// check if last key was pressed?
		const auto lastKey = UI_INPUT::lastKey();

		if (lastKey < 223 && lastKey >= 0 && UI_INPUT::isPressed(lastKey)) {

			std::string curStr = VIRTUAL_KEYCODES[lastKey].data();

			// handle upper case keys
			if (UI_INPUT::isDown(VK_SHIFT) || UI_INPUT::isDown(VK_LSHIFT) || UI_INPUT::isDown(VK_RSHIFT)) {
				std::transform(curStr.begin(), curStr.end(), curStr.begin(), ::toupper);
			}

            if (curStr.length() == 1 && (_data->length() < _maxLength)) {

				_data->insert(_inputPos, curStr);
				_inputPos++;
            }

            if (lastKey == VK_SPACE && _data->length() < _maxLength) {

				_data->insert(_inputPos, " ");
				_inputPos++;
            }

            if (_data->length() > 0) {

                if (lastKey == VK_BACK && (_inputPos > 0)) {

					_inputPos--;
					_data->erase(_inputPos, 1);
                }
				else if (lastKey == VK_LEFT && (_inputPos > 0)) {
					_inputPos--;
				}
				else if (lastKey == VK_RIGHT && (_inputPos < static_cast<int>(_data->size()))) {
					_inputPos++;
				}
            }
		}
	}
}