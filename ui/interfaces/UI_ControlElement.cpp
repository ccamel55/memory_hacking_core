#include "UI_ControlElement.hpp"

using namespace CORE;

UI_ControlElement::UI_ControlElement() {

}

UI_ControlElement::~UI_ControlElement() {

}

POINT_INT& UI_ControlElement::getDrawPos() {
	return _drawPos;
}

void UI_ControlElement::setDrawPos(POINT_INT& p) {

	_drawPos = { p.x + _pos.x, p.y + _pos.y };

	for (const auto& c : _children) {
		c->setDrawPos(p);
	}
}

POINT_INT& UI_ControlElement::getControlPos() {
	return _controlPos;
}

void UI_ControlElement::setControlPos(POINT_INT& p) {

	_controlPos = { p.x + _pos.x + UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.x, p.y + _pos.y + UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.y };

	for (const auto& c : _children) {
		c->setControlPos(p);
	}
}