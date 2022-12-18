#include "UI_Element.hpp"

using namespace CORE;

UI_BaseElement::UI_BaseElement() {

	m_cPos = { 20, 20 };
	m_cSize = { 200, 100 };

	m_pParent = NULL;

	m_bBlocking = false;
	m_bIsFocused = false;
}

UI_BaseElement::~UI_BaseElement() {

}

bool UI_BaseElement::isBlocking() {
	return m_bBlocking;
}

void UI_BaseElement::setBlocking(bool b) {
	m_bBlocking = b;
}

bool UI_BaseElement::isFocused() {
	return m_bIsFocused;
}

void UI_BaseElement::setIsFocused(bool b) {
	m_bIsFocused = b;
}

POINT_INT& UI_BaseElement::getPos() {
	return m_cPos;
}

void UI_BaseElement::setPos(POINT_INT& p) {
	m_cPos = p;
}

POINT_INT& UI_BaseElement::getSize() {
	return m_cSize;
}

void UI_BaseElement::setSize(POINT_INT& s) {
	m_cSize = s;
}

std::shared_ptr<UI_BaseElement>& UI_BaseElement::getParent() {
	return m_pParent;
}

void UI_BaseElement::setParent(const std::shared_ptr<UI_BaseElement>& p) {
	m_pParent = p;
}