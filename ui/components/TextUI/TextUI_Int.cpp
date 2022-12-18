#include "TextUI_Int.hpp"

using namespace CORE;

TextUI_Int::TextUI_Int(const std::string& name, int* var, const INT_CONTROL_TEXT& displayText) {

	m_pVar = var;
	m_sTitle = name;

	m_cDrawPos;
	m_cControlPos;

	m_aDisplayText = displayText;
}

TextUI_Int::~TextUI_Int() {

}

void TextUI_Int::onRender(bool open) {

	const auto& pos = getControlPos();

	// only text lol
	RENDER::drawText(pos.x, pos.y, FONTS::TEXT_UI_FONT, COLORS::WHITE, m_sTitle, DX9::OUTLINE);
	RENDER::drawText(pos.x + UI_TEXT_CONSTANTS::CONTROL_SPACING.x, pos.y, FONTS::TEXT_UI_FONT, m_aDisplayText.at(*m_pVar).m_iColor, m_aDisplayText.at(*m_pVar).m_sName, DX9::ALIGN_R | DX9::OUTLINE);
}

void TextUI_Int::onUpdate() {
	// nuff
}

void TextUI_Int::processKeys() {

	const auto parent = dynamic_pointer_cast<UI_TextElement>(getParent());

	// cycle options
	if (parent->hasControl() && CONTROL::isPressed(CONTROL::K_SELECT)) {

		if (*m_pVar >= static_cast<int>(m_aDisplayText.size() - 1)) {
			*m_pVar = 0;
		}	
		else {
			*m_pVar += 1;
		}	
	}
}

POINT_INT& TextUI_Int::getDrawPos() {
	return m_cDrawPos;
}

void TextUI_Int::setDrawPos(POINT_INT& pos) {

	m_cDrawPos = pos;

	if (m_pActive) {
		m_pActive->setDrawPos(m_cDrawPos);
	}
}

POINT_INT& TextUI_Int::getControlPos() {
	return m_cControlPos;
}

void TextUI_Int::setControlPos(POINT_INT& pos) {

	m_cControlPos = { pos.x, pos.y + m_cPos.y };

	if (m_pActive) {
		m_pActive->setControlPos(m_cDrawPos);
	}
}

void TextUI_Int::addChild(const std::shared_ptr<UI_TextElement>& c) {

	c->setParent(shared_from_this());
	c->disableControl();

	m_pActive = c;
}
