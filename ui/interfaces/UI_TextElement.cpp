#include "UI_TextElement.hpp"

using namespace CORE;

UI_TextElement::UI_TextElement() : UI_BaseElement() {

	_hasControl = false;
	_title = "";

	_active = NULL;
	_children;
}

UI_TextElement::~UI_TextElement() {

}

// empty function
void* UI_TextElement::getDataBuffer() {
	throw std::exception("no data buffer for text ui");
}

bool UI_TextElement::hasControl() {
	return _hasControl;
}

void UI_TextElement::enableControl() {
	_hasControl = true;
}

void UI_TextElement::disableControl() {
	_hasControl = false;
}

std::string& UI_TextElement::getTitle() {
	return _title;
}

void UI_TextElement::setTitle(const std::string& s) {
	_title = s;
}

std::shared_ptr<UI_TextElement>& UI_TextElement::getActive() {
	return _active;
}

void UI_TextElement::setActive(const std::shared_ptr<UI_TextElement>& a) {
	_active = a;
}

std::vector<std::shared_ptr<UI_TextElement>>& UI_TextElement::getChildren() {
	return _children;
}