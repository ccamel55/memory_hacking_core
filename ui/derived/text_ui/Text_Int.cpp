#include "Text_Int.hpp"
#include "../../../config/Config.hpp"

using namespace CORE;

Text_Int::Text_Int(const std::string& name, uint32_t var, const INT_CONTROL_TEXT& displayText) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_name = name;

	_var = &C_Config::get().getVar<int>(var);
	_displayText = displayText;
}

Text_Int::~Text_Int() {

}

void Text_Int::render() {

	const auto& pos = _drawPosition;
	const auto controlIdx = static_cast<int>(*_var);

	// only text lol
	UI_RENDER::drawString(pos._x, pos._y, UI_FONTS::TEXT_UI_FONT, UI_COLORS::WHITE, getName(), E_FONT_FLAGS::FONT_OUTLINE);
	UI_RENDER::drawString(pos._x + UI_TEXTUI::CONTROL_SPACING._x, pos._y, UI_FONTS::TEXT_UI_FONT, _displayText.at(controlIdx)._color, _displayText.at(controlIdx)._name, E_FONT_FLAGS::FONT_ALIGN_R | E_FONT_FLAGS::FONT_OUTLINE);

	if ((getFlags().hasFlag(E_UI_FLAGS::UI_ACTIVE)) && getDrawGroup()) {
		getDrawGroup()->render();
	}
}

void Text_Int::update() {

	auto parent = dynamic_pointer_cast<Text_BaseControl>(getParent());
	_drawPosition = parent->getPosition() + getPosition();

	if ((getFlags().hasFlag(E_UI_FLAGS::UI_ACTIVE)) && getDrawGroup()) {

		const auto tmpPos = POINT_INT(_drawGroupPosition._x + UI_TEXTUI::DRAWGROUP_SPACING._x, _drawGroupPosition._y);

		// position is where the items will be drawn from :(
		getDrawGroup()->setPosition(tmpPos);
		getDrawGroup()->setDrawGroupPosition(tmpPos);

		getDrawGroup()->update();
	}
}

void Text_Int::input() {

	if (getParent()->getFlags().hasFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE)) {

		// cycle options
		if (UI_INPUT::isPressed(UI_KEYS::K_SELECT)) {

			if (*_var >= static_cast<int>(_displayText.size() - 1)) {
				*_var = 0;
			}
			else {
				*_var += 1;
			}
		}
	}
	else if ((getFlags().hasFlag(E_UI_FLAGS::UI_ACTIVE)) && getDrawGroup()) {
		getDrawGroup()->input();
	}
}