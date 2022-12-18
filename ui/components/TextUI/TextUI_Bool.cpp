#include "TextUI_Bool.hpp"

using namespace CORE;

TextUI_Bool::TextUI_Bool(const std::string& name, bool* var, const BOOL_CONTROL_TEXT& displayText) {

	m_pVar = var;
	m_sTitle = name;

	m_cDrawPos;
	m_cControlPos;

	m_aDisplayText = displayText;
}

TextUI_Bool::~TextUI_Bool() {


}

void TextUI_Bool::onRender(bool open) {

	const auto& pos = getControlPos();
	const auto controlIdx = static_cast<int>(*m_pVar);

	// only text lol
	RENDER::drawText(pos.x, pos.y, FONTS::TEXT_UI_FONT, COLORS::WHITE, m_sTitle, DX9::OUTLINE);
	RENDER::drawText(pos.x + UI_TEXT_CONSTANTS::CONTROL_SPACING.x, pos.y, FONTS::TEXT_UI_FONT, m_aDisplayText.at(controlIdx).m_iColor, m_aDisplayText.at(controlIdx).m_sName, DX9::ALIGN_R | DX9::OUTLINE);
}

void TextUI_Bool::onUpdate() {
	// nuff
}

void TextUI_Bool::processKeys() {

	const auto parent = dynamic_pointer_cast<UI_TextElement>(getParent());

	// toggle
	if (parent->hasControl() && CONTROL::isPressed(CONTROL::K_SELECT)) {
		*m_pVar ^= 1;
	}
}

POINT_INT& TextUI_Bool::getDrawPos() {
	return m_cDrawPos;
}

void TextUI_Bool::setDrawPos(POINT_INT& pos) {
	m_cDrawPos = pos;

	if (m_pActive) {
		m_pActive->setDrawPos(m_cDrawPos);
	}
}

POINT_INT& TextUI_Bool::getControlPos() {
	return m_cControlPos;
}

void TextUI_Bool::setControlPos(POINT_INT& pos) {
	m_cControlPos = { pos.x, pos.y + m_cPos.y };

	if (m_pActive) {
		m_pActive->setControlPos(m_cDrawPos);
	}
}

void TextUI_Bool::addChild(const std::shared_ptr<UI_TextElement>& c) {

	c->setParent(shared_from_this());
	c->disableControl();

	m_pActive = c;
}
