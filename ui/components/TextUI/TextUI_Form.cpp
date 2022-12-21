#include "TextUI_Form.hpp"

using namespace CORE;

TextUI_Form::TextUI_Form(int x, int y) : UI_TextElement() {

	_pos.x = x;
	_pos.y = y;

	_drawPos.x = x;
	_drawPos.y = y + UI_TEXT_CONSTANTS::TITLE_SIZE.y + 5;

	_size.x = UI_TEXT_CONSTANTS::TITLE_SIZE.x;
	_size.y = UI_TEXT_CONSTANTS::TITLE_SIZE.y;

	_title = "Text UI";

	_open = false;
	_dragging = false;
	_forceOpen = false;

	_drawGroup = std::make_shared<TextUI_DrawGroup>(30, 20);
}

TextUI_Form::~TextUI_Form() {

}

void TextUI_Form::onRender(bool open) {

	const auto& pos = getPos();
	const auto& size = getSize();

	if (open) {

		// draw drag bar and what ever
		RENDER::drawRectGradientV(pos.x, pos.y, size.x, size.y, COLORS::FORM_BORDER_GRADIENT, COLORS::FORM_BORDER);

		// draw title in the bar thing
		RENDER::drawText(pos.x + 5, pos.y + size.y / 2, FONTS::WINDOW_FONT, COLORS::TEXT_TEXT_LABEL, getTitle(), DX9::CENTER_Y);

		// if unfocused draw an overlay
		if (!isFocused()) {
			RENDER::drawRectFilled(pos.x, pos.y, size.x, size.y, COLORS::FORM_UNFOCUS);
		}
	}

	const auto& drawPos = getDrawPos();
	_forceOpen = open;

	// menu related stuff
	{
		RENDER::drawText(drawPos.x, drawPos.y, FONTS::TEXT_UI_FONT, COLORS::WHITE, "[  ]", DX9::OUTLINE);
		RENDER::drawText(drawPos.x + 25, drawPos.y, FONTS::TEXT_UI_FONT, COLORS::WHITE, getTitle(), DX9::OUTLINE);

		if (_open || _forceOpen) {

			RENDER::drawRectFilled(drawPos.x + 8, drawPos.y + 5, 2, 6, COLORS::GREEN);
			RENDER::drawRect(drawPos.x + 8, drawPos.y + 5, 2, 6, COLORS::BLACK);

			_drawGroup->onRender(true);
		}
		else {

			RENDER::drawRectFilled(drawPos.x + 6, drawPos.y + 7, 6, 2, COLORS::WHITE);
			RENDER::drawRect(drawPos.x + 6, drawPos.y + 7, 6, 2, COLORS::BLACK);
		}
	}
}

void TextUI_Form::onUpdate() {

	const auto& pos = getPos();

	// in draggable area
	if (CONTROL::isPressed(VK_LBUTTON) && CONTROL::mouseInBounds(pos.x, pos.y, _size.x, _size.y)) {
		_dragging = true;
		setBlocking(true);
	}

	if (_dragging && CONTROL::isDown(VK_LBUTTON)) {

		// move location of menu
		const auto& mouseDelta = CONTROL::mouseDelta();
		const auto& screenSize = RENDER::screenSize();

		POINT_INT formPos = {
			std::clamp<int>(pos.x + mouseDelta.x, 0, screenSize.x - _size.x) ,
			std::clamp<int>(pos.y + mouseDelta.y, 0, screenSize.y - _size.y) };

		setPos(formPos);
		setDrawPos(formPos);

		setControlPos(getDrawPos());

		return;
	}
	else if (_dragging) {

		// reset
		_dragging = false;
		setBlocking(false);

		return;
	}

	// call because it doesnt get called on focus normally
	processKeys();
}

void TextUI_Form::processKeys() {

	// where keybinds and shit get processed
	if (CONTROL::isPressed(CONTROL::K_EXPAND_TEXTUI)) {
		_open = !_open;
	}

	if (_open || _forceOpen) {
		_drawGroup->processKeys();
	}
}

void TextUI_Form::addChild(const std::shared_ptr<UI_TextElement>& c) {

	_drawGroup->addChild(c);
}

POINT_INT& TextUI_Form::getDrawPos() {
	return _drawPos;
}

void TextUI_Form::setDrawPos(POINT_INT& p) {

	if (_drawGroup->getParent() == NULL) {
		_drawGroup->setParent(shared_from_this());
	}

	_drawPos = { p.x, p.y + UI_TEXT_CONSTANTS::TITLE_SIZE.y + 5 };
	_drawGroup->setDrawPos(_drawPos);
}

// override draw pos and control pos
POINT_INT& TextUI_Form::getControlPos() {
	throw std::exception("form has not controls!");
}

void TextUI_Form::setControlPos(POINT_INT& p) {
	_drawGroup->setControlPos(p);
}