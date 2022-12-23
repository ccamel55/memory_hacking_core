#include "Form_Button.hpp"
#include "Form_Groupbox.hpp"

using namespace CORE;

Form_Button::Form_Button(const std::string name, std::function<void()> callback) {

	_name = name;
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;

	_size = {0, 20};
	_callback = callback;
}

Form_Button::~Form_Button() {

}

void Form_Button::render() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();
	
	UI_RENDER::drawRectFilled(pos._x, pos._y, size._x, size._y, _clicked ? UI_COLORS::CONTROL_FILL_2 : UI_COLORS::CONTROL_FILL);
	UI_RENDER::drawRect(pos._x, pos._y, size._x, size._y, UI_COLORS::CONTROL_OUTLINE);

	UI_RENDER::drawText(pos._x + (size._x / 2), pos._y + (size._y / 2), UI_FONTS::CONTROL_FONT, UI_COLORS::WHITE, getName(), E_UI_FONT_FLAGS::UI_FONT_CENTER_X | E_UI_FONT_FLAGS::UI_FONT_CENTER_Y);
}

void Form_Button::update() {

	auto parent = dynamic_pointer_cast<Form_Groupbox>(getParent());
	_absolutePosition = parent->getControlPosition() + getPosition();
}

void Form_Button::input() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	if (UI_INPUT::isPressed(VK_LBUTTON)) {

		if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {
			_clicked = true;
		}	
	}
	else if (UI_INPUT::isReleased(VK_LBUTTON) && _clicked) {

		_clicked = false;

		if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {
			_callback();
		}
	}
}
