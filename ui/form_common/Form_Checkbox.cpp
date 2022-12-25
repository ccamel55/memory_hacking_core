#include "Form_Checkbox.hpp"
#include "Form_Groupbox.hpp"

#include "../../config/Config.hpp"

using namespace CORE;

Form_Checkbox::Form_Checkbox(const std::string& name, uint32_t var) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_size = { 0, 12 };

	_name = name;
	_var = &C_Config::get().getVar<bool>(var);
}

Form_Checkbox::~Form_Checkbox() {

}

void Form_Checkbox::render() {

	const auto& pos = _absolutePosition;
	const auto& size = _drawSize;

	UI_RENDER::drawRectFill(_boxPosition._x, _boxPosition._y, size._x, size._y, UI_COLORS::CONTROL_FILL);
	UI_RENDER::drawRectFill(_boxPosition._x + 2, _boxPosition._y + 2, size._x - 3, size._y - 3, *_var ? UI_COLORS::GREEN : UI_COLORS::RED);

	UI_RENDER::drawString(pos._x, pos._y - 1, UI_FONTS::CONTROL_FONT, UI_COLORS::WHITE, getName());
	UI_RENDER::drawRect(_boxPosition._x, _boxPosition._y, size._x, size._y, UI_COLORS::GRAY);
}

void Form_Checkbox::update() {

	auto parent = dynamic_pointer_cast<Form_Groupbox>(getParent());
	_drawSize = POINT_INT(10, 10);

	_absolutePosition = parent->getControlPosition() + getPosition();
	_boxPosition = _absolutePosition + POINT_INT(getSize()._x - _drawSize._x, 0);
}

void Form_Checkbox::input() {

	const auto& pos = _boxPosition;
	const auto& size = _drawSize;

	if (UI_INPUT::isPressed(VK_LBUTTON) && UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {
		*_var ^= 1;
	}
}