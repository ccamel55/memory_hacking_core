#include "TextUI_Int.hpp"

using namespace CORE;

TextUI_Int::TextUI_Int(const std::string& name, int* var, const INT_CONTROL_TEXT& displayText) {

	_var = var;
	_title = name;

	_drawPos;
	_controlPos;

	_displayText = displayText;
}

TextUI_Int::~TextUI_Int() {

}

void TextUI_Int::onRender(bool open) {

	const auto& pos = getControlPos();

	// only text lol
	RENDER::drawText(pos.x, pos.y, FONTS::TEXT_UI_FONT, COLORS::WHITE, _title, DX9::OUTLINE);
	RENDER::drawText(pos.x + UI_TEXT_CONSTANTS::CONTROL_SPACING.x, pos.y, FONTS::TEXT_UI_FONT, _displayText.at(*_var)._color, _displayText.at(*_var)._name, DX9::ALIGN_R | DX9::OUTLINE);
}

void TextUI_Int::onUpdate() {
	// nuff
}

void TextUI_Int::processKeys() {

	const auto parent = dynamic_pointer_cast<UI_TextElement>(getParent());

	// cycle options
	if (parent->hasControl() && CONTROL::isPressed(CONTROL::K_SELECT)) {

		if (*_var >= static_cast<int>(_displayText.size() - 1)) {
			*_var = 0;
		}	
		else {
			*_var += 1;
		}	
	}
}

POINT_INT& TextUI_Int::getDrawPos() {
	return _drawPos;
}

void TextUI_Int::setDrawPos(POINT_INT& pos) {

	_drawPos = pos;

	if (_active) {
		_active->setDrawPos(_drawPos);
	}
}

POINT_INT& TextUI_Int::getControlPos() {
	return _controlPos;
}

void TextUI_Int::setControlPos(POINT_INT& pos) {

	_controlPos = { pos.x, pos.y + _pos.y };

	if (_active) {
		_active->setControlPos(_drawPos);
	}
}

void TextUI_Int::addChild(const std::shared_ptr<UI_TextElement>& c) {

	c->setParent(shared_from_this());
	c->disableControl();

	_active = c;
}
