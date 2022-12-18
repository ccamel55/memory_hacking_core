#include "UI_FormElement.hpp"

using namespace CORE;

UI_FormElement::UI_FormElement() : UI_BaseElement() {

	m_sTitle = "EMPTY";

	m_bPinned = false;
	m_bDragging = false;

	m_pFocused = NULL;
	m_aChildren;

	// weezers!! make sure to update everytime we change our position!
	m_cControlPos;
	m_cControlSize;
}

UI_FormElement::~UI_FormElement() {

}

void UI_FormElement::onRender(bool open) {

	const auto& pos = getPos();
	const auto& size = getSize();

	const auto& controlPos = getControlPos();
	const auto& controlSize = getControlSize();

	if (open) {

		// draw main form
		RENDER::drawRectFilled(pos.x, pos.y, size.x, size.y, COLORS::FORM_BORDER);

		// draw gradient bar for the title
		RENDER::drawRectGradientV(pos.x, pos.y, size.x, UI_FORM_CONSTANTS::TITLE_SIZE.y, COLORS::FORM_BORDER_GRADIENT, COLORS::FORM_BORDER);

		// draw control render regin
		RENDER::drawRectFilled(controlPos.x, controlPos.y, controlSize.x, controlSize.y, COLORS::FORM_CONTENTS);

		// form name pinned box
		RENDER::drawText(pos.x + UI_FORM_CONSTANTS::CONTENT_POS.x, pos.y + (UI_FORM_CONSTANTS::CONTENT_POS.y / 2), FONTS::WINDOW_FONT, COLORS::FORM_TEXT_LABEL, getTitle(), DX9::CENTER_Y);

		// draw pinned circle
		RENDER::drawCircleGradient(pos.x + size.x + UI_FORM_CONSTANTS::PINNED_OFFSET.x, pos.y + UI_FORM_CONSTANTS::PINNED_OFFSET.y, 4, COLORS::WHITE, getPinned() ? COLORS::GREEN : COLORS::RED);

		// if unfocused draw an overlay
		if (!isFocused()) {
			RENDER::drawRectFilled(pos.x, pos.y, size.x, size.y, COLORS::FORM_UNFOCUS);
		}
	}
	else if (getPinned()) {

		// draw control region but with less background alpha!
		RENDER::drawRectFilled(controlPos.x, controlPos.y, controlSize.x, controlSize.y, COLORS::FORM_CONTENTS_PINNED);
	}
}

void UI_FormElement::onUpdate() {

	const auto& pos = getPos();
	const auto& size = getSize();

	// pinned stuff here
	if (CONTROL::isPressed(VK_LBUTTON) && CONTROL::mouseInBounds(pos.x + size.x + UI_FORM_CONSTANTS::PINNED_OFFSET.x - 5, pos.y + UI_FORM_CONSTANTS::PINNED_OFFSET.y - 5, 10, 10)) {
		setPinned(!getPinned());
		return;
	}

	// in draggable area
	if (CONTROL::isPressed(VK_LBUTTON) && CONTROL::mouseInBounds(pos.x, pos.y, size.x, UI_FORM_CONSTANTS::TITLE_SIZE.y)) {
		m_bDragging = true;
		setBlocking(true);
	}

	if (m_bDragging && CONTROL::isDown(VK_LBUTTON)) {

		// move current form and children
		const auto& mouseDelta = CONTROL::mouseDelta();
		const auto& screenSize = RENDER::screenSize();

		POINT_INT formPos = {
			std::clamp<int>(pos.x + mouseDelta.x, 0, screenSize.x - m_cSize.x) ,
			std::clamp<int>(pos.y + mouseDelta.y, 0, screenSize.y - m_cSize.y) };

		setPos(formPos);
		setControlPos();

		return;
	}
	else if (m_bDragging) {

		// reset
		m_bDragging = false;
		setBlocking(false);

		return;
	}
}

bool UI_FormElement::getPinned() {
	return m_bPinned;
}

void UI_FormElement::setPinned(bool b) {
	m_bPinned = b;
}

POINT_INT& UI_FormElement::getControlPos() {
	return m_cControlPos;
}

void UI_FormElement::setControlPos() {

	// make sure to call everytime we change position
	m_cControlPos.x = m_cPos.x + UI_FORM_CONSTANTS::CONTENT_POS.x;
	m_cControlPos.y = m_cPos.y + UI_FORM_CONSTANTS::CONTENT_POS.y;
}

POINT_INT& UI_FormElement::getControlSize() {
	return m_cControlSize;
}

void UI_FormElement::setControlSize() {

	m_cControlSize.x = m_cSize.x + UI_FORM_CONSTANTS::CONTENT_SIZE.x;
	m_cControlSize.y = m_cSize.y + UI_FORM_CONSTANTS::CONTENT_SIZE.y;
}

std::string& UI_FormElement::getTitle() {
	return m_sTitle;
}

void UI_FormElement::setTitle(const std::string& s) {
	m_sTitle = s;
}

std::shared_ptr<UI_BaseElement>& UI_FormElement::getFocused() {
	return m_pFocused;
}

void UI_FormElement::setFocused(std::shared_ptr<UI_BaseElement>& f) {
	m_pFocused = f;
}

std::vector<std::shared_ptr<UI_BaseElement>>& UI_FormElement::getChildren() {
	return m_aChildren;
}

