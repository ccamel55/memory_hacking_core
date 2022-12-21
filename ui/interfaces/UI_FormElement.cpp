#include "UI_FormElement.hpp"

using namespace CORE;

UI_FormElement::UI_FormElement() : UI_BaseElement() {

	_title = "EMPTY";

	_pinned = false;
	_dragging = false;

	_focused = NULL;
	_children;

	// weezers!! make sure to update everytime we change our position!
	_controlPos;
	_controlSize;
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

		onRenderFinish(true);
	}
	else if (getPinned()) {

		// draw control region but with less background alpha!
		RENDER::drawRectFilled(controlPos.x, controlPos.y, controlSize.x, controlSize.y, COLORS::FORM_CONTENTS_PINNED);
	}
}

void UI_FormElement::onRenderFinish(bool open) {

	const auto& pos = getPos();
	const auto& size = getSize();

	if (open && !isFocused()) {
		RENDER::drawRectFilled(pos.x, pos.y, size.x, size.y, COLORS::FORM_UNFOCUS);
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
		_dragging = true;
		setBlocking(true);
	}

	if (_dragging && CONTROL::isDown(VK_LBUTTON)) {

		// move current form and children
		const auto& mouseDelta = CONTROL::mouseDelta();
		const auto& screenSize = RENDER::screenSize();

		POINT_INT formPos = {
			std::clamp<int>(pos.x + mouseDelta.x, 0, screenSize.x - _size.x) ,
			std::clamp<int>(pos.y + mouseDelta.y, 0, screenSize.y - _size.y) };

		setPos(formPos);
		setControlPos();

		return;
	}
	else if (_dragging) {

		// reset
		_dragging = false;
		setBlocking(false);

		return;
	}
}

bool UI_FormElement::getPinned() {
	return _pinned;
}

void UI_FormElement::setPinned(bool b) {
	_pinned = b;
}

POINT_INT& UI_FormElement::getControlPos() {
	return _controlPos;
}

void UI_FormElement::setControlPos() {

	// make sure to call everytime we change position
	_controlPos.x = _pos.x + UI_FORM_CONSTANTS::CONTENT_POS.x;
	_controlPos.y = _pos.y + UI_FORM_CONSTANTS::CONTENT_POS.y;
}

POINT_INT& UI_FormElement::getControlSize() {
	return _controlSize;
}

void UI_FormElement::setControlSize() {

	_controlSize.x = _size.x + UI_FORM_CONSTANTS::CONTENT_SIZE.x;
	_controlSize.y = _size.y + UI_FORM_CONSTANTS::CONTENT_SIZE.y;
}

std::string& UI_FormElement::getTitle() {
	return _title;
}

void UI_FormElement::setTitle(const std::string& s) {
	_title = s;
}

std::shared_ptr<UI_BaseElement>& UI_FormElement::getFocused() {
	return _focused;
}

void UI_FormElement::setFocused(std::shared_ptr<UI_BaseElement>& f) {
	_focused = f;
}

std::vector<std::shared_ptr<UI_BaseElement>>& UI_FormElement::getChildren() {
	return _children;
}

