#include "UI_Element.hpp"

using namespace CORE;

UI_BaseElement::UI_BaseElement() {

	_pos = { 20, 20 };
	_size = { 200, 100 };

	_parent = NULL;

	_blocking = false;
	_isFocused = false;
}

UI_BaseElement::~UI_BaseElement() {

}

bool UI_BaseElement::isBlocking() {
	return _blocking;
}

void UI_BaseElement::setBlocking(bool b) {
	_blocking = b;
}

bool UI_BaseElement::isFocused() {
	return _isFocused;
}

void UI_BaseElement::setIsFocused(bool b) {
	_isFocused = b;
}

POINT_INT& UI_BaseElement::getPos() {
	return _pos;
}

void UI_BaseElement::setPos(POINT_INT& p) {
	_pos = p;
}

POINT_INT& UI_BaseElement::getSize() {
	return _size;
}

void UI_BaseElement::setSize(POINT_INT& s) {
	_size = s;
}

std::shared_ptr<UI_BaseElement>& UI_BaseElement::getParent() {
	return _parent;
}

void UI_BaseElement::setParent(const std::shared_ptr<UI_BaseElement>& p) {
	_parent = p;
}