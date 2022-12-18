#include "UI_TextElement.hpp"

using namespace CORE;

UI_TextElement::UI_TextElement() : UI_BaseElement() {

	m_bHasControl = false;
	m_sTitle = "";

	m_pActive = NULL;
	m_aChildren;
}

UI_TextElement::~UI_TextElement() {

}

// empty function
void* UI_TextElement::getDataBuffer() {
	throw std::exception("no data buffer for text ui");
}

bool UI_TextElement::hasControl() {
	return m_bHasControl;
}

void UI_TextElement::enableControl() {
	m_bHasControl = true;
}

void UI_TextElement::disableControl() {
	m_bHasControl = false;
}

std::string& UI_TextElement::getTitle() {
	return m_sTitle;
}

void UI_TextElement::setTitle(const std::string& s) {
	m_sTitle = s;
}

std::shared_ptr<UI_TextElement>& UI_TextElement::getActive() {
	return m_pActive;
}

void UI_TextElement::setActive(const std::shared_ptr<UI_TextElement>& a) {
	m_pActive = a;
}

std::vector<std::shared_ptr<UI_TextElement>>& UI_TextElement::getChildren() {
	return m_aChildren;
}