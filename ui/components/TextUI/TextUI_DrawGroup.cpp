#include "../../interfaces/UI_TextElement.hpp"
#include "TextUI_DrawGroup.hpp"

using namespace CORE;

TextUI_DrawGroup::TextUI_DrawGroup(int x, int y) : UI_TextElement() {

	m_iCursor = 0;
	m_iScroll = 0;

	m_cControlPos = { 0, 0 };
	m_cControlOffset = { 0, 0 };

	m_bHasControl = true;

	m_cDrawPos;

	// m_cPos is now used as an offset (relative position) rather than absolute position
	m_cPos.x = x;
	m_cPos.y = y;
}

TextUI_DrawGroup::~TextUI_DrawGroup() {

}

void TextUI_DrawGroup::onRender(bool open) {

	// draw controls
	for (size_t i = m_iScroll; i < std::min<size_t>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT + m_iScroll, m_aChildren.size()); i++) {
		m_aChildren.at(i)->onRender(true);
	}

	// draw drawGroup if our current element has one
	if (m_pActive && m_pActive->getActive()) {
		m_pActive->getActive()->onRender(true);
	}

	const auto& pos = getDrawPos();

	// if we can control this drawGroup, show selection cursor
	if (!m_aChildren.empty() && hasControl()) {

		//draw active indicator
		const auto cursorOffsetY = UI_TEXT_CONSTANTS::CONTROL_SPACING.y * (m_iCursor - m_iScroll);

		RENDER::drawRectFilled(pos.x - 8, pos.y + cursorOffsetY + 1, 3, 13, COLORS::LIGHT_BLUE);
		RENDER::drawRect(pos.x - 8, pos.y + cursorOffsetY + 1, 3, 13, COLORS::BLACK);
	}

	// element counter
	const auto drawStr = std::string("[" + std::to_string(m_iCursor + 1) + "/" + std::to_string(m_aChildren.size()) + "]");
	RENDER::drawText(pos.x + UI_TEXT_CONSTANTS::CONTROL_SPACING.x, pos.y + (UI_TEXT_CONSTANTS::CONTROL_SPACING.y * std::min<size_t>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT, m_aChildren.size())), FONTS::TEXT_UI_FONT, COLORS::LIGHT_BLUE, drawStr, DX9::ALIGN_R | DX9::OUTLINE);
}

void TextUI_DrawGroup::onUpdate() {
	// nope! nothing atm
}

void TextUI_DrawGroup::processKeys() {

	// when we want to go to the next drawGroup, set m_has_control to false on this group
	//		and stop all control passing on our control element, only pass controls to drawGroup

	if (m_aChildren.size() > 1 && hasControl()) {

		if (CONTROL::isPressed(CONTROL::K_UP)) {

			if (m_iCursor <= 0) {
				m_iCursor = m_aChildren.size() - 1;
			}
			else {
				m_iCursor -= 1;
			}

			m_pActive = m_aChildren.at(m_iCursor);

			// check if we need to change scrollStart
			if (m_aChildren.size() > UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT) {

				if (m_iCursor > m_iScroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2))) {
					m_iScroll = std::min<int>(m_aChildren.size() - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT, m_iCursor - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2)));
				}
				else if (m_iCursor < m_iScroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING)) {
					m_iScroll = std::max<int>(0, m_iCursor - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING);
				}	
			}

			return;
		}

		if (CONTROL::isPressed(CONTROL::K_DOWN)) {

			if (m_iCursor >= static_cast<int>(m_aChildren.size() - 1))
				m_iCursor = 0;
			else
				m_iCursor += 1;

			m_pActive = m_aChildren.at(m_iCursor);

			// check if we need to change scrollStart
			if (m_aChildren.size() > UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT) {

				if (m_iCursor > m_iScroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2))) {
					m_iScroll = std::min<int>(m_aChildren.size() - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT, m_iCursor - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2)));
				}
				else if (m_iCursor < m_iScroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING)) {
					m_iScroll = std::max<int>(0, m_iCursor - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING);
				}
			}

			return;
		}
	}

	// check if current control has a drawGroup
	if (m_pActive->getActive()) {

		if (CONTROL::isPressed(CONTROL::K_RIGHT) && hasControl()) {

			// pass control to other drawGroup
			m_pActive->getActive()->enableControl();
			disableControl();

			return;
		}

		if (CONTROL::isPressed(CONTROL::K_LEFT) && m_pActive->getActive()->hasControl()) {

			// pass control to other drawGroup
			m_pActive->getActive()->disableControl();
			enableControl();

			return;
		}

		m_pActive->getActive()->processKeys();
	}

	// process input only on our current control
	m_pActive->processKeys();
}

void TextUI_DrawGroup::addChild(const std::shared_ptr<UI_TextElement>& c) {

	c->setParent(shared_from_this());

	// have at least 1 thing active
	if (m_pActive == NULL) {
		m_pActive = c;
	}

	// controls also use relative position!
	c->setPos(m_cControlOffset);
	m_aChildren.push_back(c);

	m_cControlOffset.y += UI_TEXT_CONSTANTS::CONTROL_SPACING.y;
}

POINT_INT& TextUI_DrawGroup::getDrawPos() {
	return m_cDrawPos;
}

void TextUI_DrawGroup::setDrawPos(POINT_INT& p) {
	m_cDrawPos = { p.x + m_cPos.x, p.y + m_cPos.y };

	for (const auto& c : m_aChildren) {
		c->setDrawPos(m_cDrawPos);
	}
}

POINT_INT& TextUI_DrawGroup::getControlPos() {
	return m_cControlPos;
}

void TextUI_DrawGroup::setControlPos(POINT_INT& p) {

	m_cControlPos = { p.x + m_cPos.x, p.y + m_cPos.y - (UI_TEXT_CONSTANTS::CONTROL_SPACING.y * m_iScroll) };

	for (const auto& c : m_aChildren) {
		c->setControlPos(m_cDrawPos);
	}
}