#include "Form_Splitter.hpp"
#include "Form_Groupbox.hpp"

using namespace CORE;

Form_Splitter::Form_Splitter(const std::string& name) {

	_name = name;
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_size = { 0, 16 };
}

Form_Splitter::~Form_Splitter() {

}

void Form_Splitter::render() {

	// draw heheh
	UI_RENDER::drawString(_absolutePosition._x, _absolutePosition._y - 2, UI_FONTS::TAB_FONT, UI_COLORS::WHITE, getName());
	UI_RENDER::drawRectFill(_absolutePosition._x, _absolutePosition._y + 14, _drawSize._x, _drawSize._y, UI_COLORS::CONTROL_FILL_2);
}

void Form_Splitter::update() {

	auto parent = dynamic_pointer_cast<Form_Groupbox>(getParent());

	_absolutePosition = parent->getControlPosition() + getPosition();
	_drawSize = POINT_INT(getSize()._x, 1);
}

void Form_Splitter::input() {

}