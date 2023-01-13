#include "Text_Drawgroup.hpp"

using namespace CORE;

Text_Drawgroup::Text_Drawgroup() {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;

	_cursor = 0;
	_scroll = 0;
}

Text_Drawgroup::~Text_Drawgroup() {


}

void Text_Drawgroup::render() {

	const auto& pos = getDrawGroupPosition();

	// draw controls
	for (size_t i = _scroll; i < std::min<size_t>(UI_TEXTUI::DRAWGROUP_ITEM_COUNT + _scroll, _controls.size()); i++) {
		_controls.at(i)->render();
	}

	// if we can control this drawGroup, show selection cursor
	if (!_controls.empty() && (getFlags().hasFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE))) {

		//draw active indicator
		const auto cursorOffsetY = UI_TEXTUI::CONTROL_SPACING._y * (_cursor - _scroll);

		UI_RENDER::drawRectFill(pos._x - 8, pos._y + cursorOffsetY + 1, 3, 13, UI_COLORS::LIGHT_BLUE);
		UI_RENDER::drawRect(pos._x - 8, pos._y + cursorOffsetY + 1, 3, 13, UI_COLORS::BLACK);
	}

	// element counter
	const auto drawStr = std::string("[" + std::to_string(_cursor + 1) + "/" + std::to_string(_controls.size()) + "]");
	UI_RENDER::drawString(pos._x + UI_TEXTUI::CONTROL_SPACING._x, pos._y + (UI_TEXTUI::CONTROL_SPACING._y * std::min<size_t>(UI_TEXTUI::DRAWGROUP_ITEM_COUNT, _controls.size())), UI_FONTS::TEXT_UI_FONT, UI_COLORS::LIGHT_BLUE, drawStr, E_FONT_FLAGS::FONT_ALIGN_R | E_FONT_FLAGS::FONT_OUTLINE);
}

void Text_Drawgroup::update() {
	
	const auto currentDrawGroupPos = POINT_INT(_drawGroupPosition._x, _drawGroupPosition._y - (UI_TEXTUI::CONTROL_SPACING._y * _scroll));
	setPosition(currentDrawGroupPos);

	for (size_t i = _scroll; i < std::min<size_t>(UI_TEXTUI::DRAWGROUP_ITEM_COUNT + _scroll, _controls.size()); i++) {

		// we only need to update the currently drawn items
		_controls.at(i)->setDrawGroupPosition(_drawGroupPosition);
		_controls.at(i)->update();
	}
}

void Text_Drawgroup::input() {

	if (getFlags().hasFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE)) {

		if (UI_INPUT::isPressed(UI_KEYS::K_UP)) {

			_active->getFlags().removeFlag(E_UI_FLAGS::UI_ACTIVE);

			if (_cursor <= 0) {
				_cursor = _controls.size() - 1;
			}
			else {
				_cursor -= 1;
			}

			_active = _controls.at(_cursor);
			_active->getFlags().setFlag(E_UI_FLAGS::UI_ACTIVE);

			// check if we need to change scrollStart
			if (_controls.size() > UI_TEXTUI::DRAWGROUP_ITEM_COUNT) {

				if (_cursor > _scroll + static_cast<int>(UI_TEXTUI::DRAWGROUP_ITEM_COUNT - (UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING * 2))) {
					_scroll = std::min<int>(_controls.size() - UI_TEXTUI::DRAWGROUP_ITEM_COUNT, _cursor - (UI_TEXTUI::DRAWGROUP_ITEM_COUNT - (UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING * 2)));
				}
				else if (_cursor < _scroll + static_cast<int>(UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING)) {
					_scroll = std::max<int>(0, _cursor - UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING);
				}
			}

			update();
			return;
		}
		else if (UI_INPUT::isPressed(UI_KEYS::K_DOWN)) {

			_active->getFlags().removeFlag(E_UI_FLAGS::UI_ACTIVE);

			if (_cursor >= static_cast<int>(_controls.size() - 1)) {
				_cursor = 0;
			}
			else {
				_cursor += 1;
			}

			_active = _controls.at(_cursor);
			_active->getFlags().setFlag(E_UI_FLAGS::UI_ACTIVE);

			// check if we need to change scrollStart
			if (_controls.size() > UI_TEXTUI::DRAWGROUP_ITEM_COUNT) {

				if (_cursor > _scroll + static_cast<int>(UI_TEXTUI::DRAWGROUP_ITEM_COUNT - (UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING * 2))) {
					_scroll = std::min<int>(_controls.size() - UI_TEXTUI::DRAWGROUP_ITEM_COUNT, _cursor - (UI_TEXTUI::DRAWGROUP_ITEM_COUNT - (UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING * 2)));
				}
				else if (_cursor < _scroll + static_cast<int>(UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING)) {
					_scroll = std::max<int>(0, _cursor - UI_TEXTUI::DRAWGROUP_ITEM_SCROLL_PADDING);
				}
			}

			update();
			return;
		}
		else if (UI_INPUT::isPressed(UI_KEYS::K_LEFT)) {

			// if we are not the parent drawgroup go back
			if (getParent()->getType() != E_UI_ELEMENT_TYPE::UI_ELEMENT_TEXT && getParent()->getParent()) {

				getFlags().removeFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE);
				getParent()->getParent()->getFlags().setFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE);
			}

			return;
		}
		else if (UI_INPUT::isPressed(UI_KEYS::K_RIGHT)) {

			// if we are not the end drawgroup go right
			if (_active->getDrawGroup()) {

				getFlags().removeFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE);
				_active->getDrawGroup()->getFlags().setFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE);
			}

			return;
		}
	}

	// process input only on our current control
	_active->input();
}
