#include "Form_Combobox.hpp"
#include "Form_Groupbox.hpp"

#include "../../config/Config.hpp"

using namespace CORE;

Form_Combobox::Form_Combobox(const std::string& name, uint32_t var, std::vector<std::string>* comboItems) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_size = { 0, 20 };

	_name = name;
	_var = &C_Config::get().getVar<int>(var);

	_comboItems = comboItems;
}

Form_Combobox::~Form_Combobox() {

}

void Form_Combobox::render() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	UI_RENDER::drawRectFill(pos._x, pos._y, size._x, size._y, UI_COLORS::CONTROL_FILL);
	UI_RENDER::drawRect(pos._x, pos._y, size._x, size._y, UI_COLORS::GRAY);

	if (_curItem > 0) {
		UI_RENDER::drawTriangleFill(_leftPosition._x - UI_CONTROL::COMBO_SELECTOR_RADIUS._x, _leftPosition._y, _leftPosition._x, _leftPosition._y + UI_CONTROL::COMBO_SELECTOR_RADIUS._y, _leftPosition._x, _leftPosition._y - UI_CONTROL::COMBO_SELECTOR_RADIUS._y, UI_COLORS::CONFIG_TAB_FILL1);
	}

	if (_curItem < _comboItems->size() - 1) {
		UI_RENDER::drawTriangleFill(_rightPosition._x + UI_CONTROL::COMBO_SELECTOR_RADIUS._x, _rightPosition._y, _rightPosition._x, _rightPosition._y + UI_CONTROL::COMBO_SELECTOR_RADIUS._y, _rightPosition._x, _rightPosition._y - UI_CONTROL::COMBO_SELECTOR_RADIUS._y, UI_COLORS::CONFIG_TAB_FILL1);
	}

	// changes depending on hover etc
	UI_RENDER::drawString(pos._x + (size._x / 2), pos._y + (size._y / 2), UI_FONTS::CONTROL_FONT, UI_COLORS::WHITE, _hovered ? _comboItems->at(_curItem) : getName(), E_FONT_FLAGS::FONT_CENTER_X | E_FONT_FLAGS::FONT_CENTER_Y);
}

void Form_Combobox::update() {

	auto parent = dynamic_pointer_cast<Form_Groupbox>(getParent());
	_absolutePosition = parent->getControlPosition() + getPosition();

	_leftPosition = POINT_INT(_absolutePosition._x + UI_CONTROL::COMBO_SELECTOR_OFFSET._x, _absolutePosition._y + (_size._y / 2));
	_rightPosition = POINT_INT(_absolutePosition._x + _size._x - UI_CONTROL::COMBO_SELECTOR_OFFSET._x, _leftPosition._y);
}

void Form_Combobox::input() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {

		_hovered = true;

		if (UI_INPUT::isPressed(VK_LBUTTON) && UI_INPUT::mouseInBounds(_leftPosition._x - UI_CONTROL::COMBO_SELECTOR_RADIUS._x, _leftPosition._y - UI_CONTROL::COMBO_SELECTOR_RADIUS._y, UI_CONTROL::COMBO_SELECTOR_RADIUS._x, UI_CONTROL::COMBO_SELECTOR_RADIUS._y * 2)) {

			if (_curItem > 0) {
				_curItem--;
			}

			return;
		}
		else if (UI_INPUT::isPressed(VK_LBUTTON) && UI_INPUT::mouseInBounds(_rightPosition._x, _rightPosition._y - UI_CONTROL::COMBO_SELECTOR_RADIUS._y, UI_CONTROL::COMBO_SELECTOR_RADIUS._x, UI_CONTROL::COMBO_SELECTOR_RADIUS._y * 2)) {

			if (_curItem < _comboItems->size() - 1) {
				_curItem++;
			}

			return;
		}
	}
	else {
		_hovered = false;
	}
}