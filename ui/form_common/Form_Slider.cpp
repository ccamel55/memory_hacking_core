#include "Form_Slider.hpp"
#include "Form_Groupbox.hpp"

#include "../../config/Config.hpp"

using namespace CORE;

Form_Slider::Form_Slider(const std::string& name, uint32_t var, int min, int max) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_size = { 0, 12 };

	_name = name;
	_var = &C_Config::get().getVar<int>(var);

	_min = min;
	_max = max;

	_sliderDelta = static_cast<float>(*_var - _min) / static_cast<float>(_max - _min);
}

Form_Slider::~Form_Slider() {

}

void Form_Slider::render() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	UI_RENDER::drawRectFill(pos._x, pos._y, size._x, size._y, UI_COLORS::CONTROL_FILL);
	UI_RENDER::drawRectFill(pos._x, pos._y, _fillWidth, size._y, UI_COLORS::LIGHT_BLUE);

	// changes depending on hover etc
	UI_RENDER::drawRect(pos._x, pos._y, size._x, size._y, UI_COLORS::GRAY);
	UI_RENDER::drawString(pos._x + (size._x / 2), pos._y + (size._y / 2), UI_FONTS::CONTROL_FONT, UI_COLORS::WHITE, _hovered ? std::format("{}", *_var) : getName(), E_FONT_FLAGS::FONT_CENTER_X | E_FONT_FLAGS::FONT_CENTER_Y);
}

void Form_Slider::update() {

	auto parent = dynamic_pointer_cast<Form_Groupbox>(getParent());
	_absolutePosition = parent->getControlPosition() + getPosition();

	_sliderDelta = static_cast<float>(*_var - _min) / static_cast<float>(_max - _min);
	_fillWidth = static_cast<int>(_sliderDelta * _size._x);
}

void Form_Slider::input() {

	const auto& pos = _absolutePosition;
	const auto& size = getSize();

	if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {

		_hovered = true;

		if (UI_INPUT::isPressed(VK_LBUTTON)) {
			// start dragging
			getFlags() |= E_UI_FLAGS::UI_BLOCKED;
		}
	}
	else {
		_hovered = false;
	}

	if (UI_INPUT::isDown(VK_LBUTTON) && (getFlags() & E_UI_FLAGS::UI_BLOCKED)) {

		// force draw of current value
		_hovered = true;

		// dragging stuff
		const auto slider_mouse_delta = std::clamp<int>(UI_INPUT::mousePos().x - pos._x, 0, (size._x - 1));

		_sliderDelta = slider_mouse_delta / (size._x - 1.f);
		_fillWidth = static_cast<int>(_sliderDelta * size._x);

		*_var = static_cast<int>(_sliderDelta * (_max - _min) + _min);
	}
	else {
		getFlags() &= ~E_UI_FLAGS::UI_BLOCKED;
	}
}