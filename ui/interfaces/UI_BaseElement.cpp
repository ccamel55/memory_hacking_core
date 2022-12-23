#include "UI_BaseElement.hpp"

using namespace CORE;

void UI_BaseElement::setName(const std::string& name) {
	_name = name;
}

const std::string& UI_BaseElement::getName() const {
	return _name;
}

void UI_BaseElement::setType(size_t type) {
	_type = type;
}

size_t UI_BaseElement::getType() {
	return _type;
}

void UI_BaseElement::setSize(const POINT_INT& size) {
	_size = size;
}

const POINT_INT& UI_BaseElement::getSize() const {
	return _size;
}

void UI_BaseElement::setPosition(const POINT_INT& position) {
	_position = position;
}

const POINT_INT& UI_BaseElement::getPosition() const {
	return _position;
}

size_t& UI_BaseElement::getFlags() {
	return _flags;
}