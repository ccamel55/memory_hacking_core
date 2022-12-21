#include "../../interfaces/UI_TextElement.hpp"
#include "TextUI_DrawGroup.hpp"

using namespace CORE;

TextUI_DrawGroup::TextUI_DrawGroup(int x, int y) : UI_TextElement() {

	_cursor = 0;
	_scroll = 0;

	_controlPos = { 0, 0 };
	_controlOffset = { 0, 0 };

	_hasControl = true;

	_drawPos;

	// m_cPos is now used as an offset (relative position) rather than absolute position
	_pos.x = x;
	_pos.y = y;
}

TextUI_DrawGroup::~TextUI_DrawGroup() {

}

void TextUI_DrawGroup::onRender(bool open) {

	// draw controls
	for (size_t i = _scroll; i < std::min<size_t>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT + _scroll, _children.size()); i++) {
		_children.at(i)->onRender(true);
	}

	// draw drawGroup if our current element has one
	if (_active && _active->getActive()) {
		_active->getActive()->onRender(true);
	}

	const auto& pos = getDrawPos();

	// if we can control this drawGroup, show selection cursor
	if (!_children.empty() && hasControl()) {

		//draw active indicator
		const auto cursorOffsetY = UI_TEXT_CONSTANTS::CONTROL_SPACING.y * (_cursor - _scroll);

		RENDER::drawRectFilled(pos.x - 8, pos.y + cursorOffsetY + 1, 3, 13, COLORS::LIGHT_BLUE);
		RENDER::drawRect(pos.x - 8, pos.y + cursorOffsetY + 1, 3, 13, COLORS::BLACK);
	}

	// element counter
	const auto drawStr = std::string("[" + std::to_string(_cursor + 1) + "/" + std::to_string(_children.size()) + "]");
	RENDER::drawText(pos.x + UI_TEXT_CONSTANTS::CONTROL_SPACING.x, pos.y + (UI_TEXT_CONSTANTS::CONTROL_SPACING.y * std::min<size_t>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT, _children.size())), FONTS::TEXT_UI_FONT, COLORS::LIGHT_BLUE, drawStr, DX9::ALIGN_R | DX9::OUTLINE);
}

void TextUI_DrawGroup::onUpdate() {
	// nope! nothing atm
}

void TextUI_DrawGroup::processKeys() {

	// when we want to go to the next drawGroup, set m_has_control to false on this group
	//		and stop all control passing on our control element, only pass controls to drawGroup

	if (_children.size() > 1 && hasControl()) {

		if (CONTROL::isPressed(CONTROL::K_UP)) {

			if (_cursor <= 0) {
				_cursor = _children.size() - 1;
			}
			else {
				_cursor -= 1;
			}

			_active = _children.at(_cursor);

			// check if we need to change scrollStart
			if (_children.size() > UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT) {

				if (_cursor > _scroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2))) {
					_scroll = std::min<int>(_children.size() - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT, _cursor - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2)));
				}
				else if (_cursor < _scroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING)) {
					_scroll = std::max<int>(0, _cursor - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING);
				}	
			}

			return;
		}

		if (CONTROL::isPressed(CONTROL::K_DOWN)) {

			if (_cursor >= static_cast<int>(_children.size() - 1))
				_cursor = 0;
			else
				_cursor += 1;

			_active = _children.at(_cursor);

			// check if we need to change scrollStart
			if (_children.size() > UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT) {

				if (_cursor > _scroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2))) {
					_scroll = std::min<int>(_children.size() - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT, _cursor - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_COUNT - (UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING * 2)));
				}
				else if (_cursor < _scroll + static_cast<int>(UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING)) {
					_scroll = std::max<int>(0, _cursor - UI_TEXT_CONSTANTS::DRAWGROUP_ITEM_SCROLL_PADDING);
				}
			}

			return;
		}
	}

	// check if current control has a drawGroup
	if (_active->getActive()) {

		if (CONTROL::isPressed(CONTROL::K_RIGHT) && hasControl()) {

			// pass control to other drawGroup
			_active->getActive()->enableControl();
			disableControl();

			return;
		}

		if (CONTROL::isPressed(CONTROL::K_LEFT) && _active->getActive()->hasControl()) {

			// pass control to other drawGroup
			_active->getActive()->disableControl();
			enableControl();

			return;
		}

		_active->getActive()->processKeys();
	}

	// process input only on our current control
	_active->processKeys();
}

void TextUI_DrawGroup::addChild(const std::shared_ptr<UI_TextElement>& c) {

	c->setParent(shared_from_this());

	// have at least 1 thing active
	if (_active == NULL) {
		_active = c;
	}

	// controls also use relative position!
	c->setPos(_controlOffset);
	_children.push_back(c);

	_controlOffset.y += UI_TEXT_CONSTANTS::CONTROL_SPACING.y;
}

POINT_INT& TextUI_DrawGroup::getDrawPos() {
	return _drawPos;
}

void TextUI_DrawGroup::setDrawPos(POINT_INT& p) {

	_drawPos = { p.x + _pos.x, p.y + _pos.y };

	for (const auto& c : _children) {
		c->setDrawPos(_drawPos);
	}
}

POINT_INT& TextUI_DrawGroup::getControlPos() {
	return _controlPos;
}

void TextUI_DrawGroup::setControlPos(POINT_INT& p) {

	_controlPos = { p.x + _pos.x, p.y + _pos.y - (UI_TEXT_CONSTANTS::CONTROL_SPACING.y * _scroll) };

	for (const auto& c : _children) {
		c->setControlPos(_drawPos);
	}
}