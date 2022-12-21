#include "TextUI_Bool.hpp"

#include "../../../config/Config.hpp"

using namespace CORE;

TextUI_Bool::TextUI_Bool(const std::string& name, uint32_t var, const BOOL_CONTROL_TEXT& displayText) {

	_var = &C_Config::get().getVar<bool>(var);
	_title = name;

	_drawPos;
	_controlPos;

	_displayText = displayText;
}

TextUI_Bool::~TextUI_Bool() {


}

void TextUI_Bool::onRender(bool open) {

	const auto& pos = getControlPos();
	const auto controlIdx = static_cast<int>(*_var);

	// only text lol
	RENDER::drawText(pos.x, pos.y, FONTS::TEXT_UI_FONT, COLORS::WHITE, _title, DX9::OUTLINE);
	RENDER::drawText(pos.x + UI_TEXT_CONSTANTS::CONTROL_SPACING.x, pos.y, FONTS::TEXT_UI_FONT, _displayText.at(controlIdx)._color, _displayText.at(controlIdx)._name, DX9::ALIGN_R | DX9::OUTLINE);
}

void TextUI_Bool::onUpdate() {
	// nuff
}

void TextUI_Bool::processKeys() {

	const auto parent = dynamic_pointer_cast<UI_TextElement>(getParent());

	// toggle
	if (parent->hasControl() && CONTROL::isPressed(CONTROL::K_SELECT)) {
		*_var ^= 1;
	}
}

POINT_INT& TextUI_Bool::getDrawPos() {
	return _drawPos;
}

void TextUI_Bool::setDrawPos(POINT_INT& pos) {
	_drawPos = pos;

	if (_active) {
		_active->setDrawPos(_drawPos);
	}
}

POINT_INT& TextUI_Bool::getControlPos() {
	return _controlPos;
}

void TextUI_Bool::setControlPos(POINT_INT& pos) {
	_controlPos = { pos.x, pos.y + _pos.y };

	if (_active) {
		_active->setControlPos(_drawPos);
	}
}

void TextUI_Bool::addChild(const std::shared_ptr<UI_TextElement>& c) {

	c->setParent(shared_from_this());
	c->disableControl();

	_active = c;
}
