#include "Text_Bool.hpp"
#include "../../../config/Config.hpp"

using namespace CORE;

Text_Bool::Text_Bool(const std::string& name, uint32_t var, const BOOL_CONTROL_TEXT& displayText) {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONTROL;
	_name = name;

	_var = &C_Config::get().getVar<bool>(var);
	_displayText = displayText;
}

Text_Bool::~Text_Bool() {

}

void Text_Bool::render() {

	const auto& pos = _drawPosition;
	const auto controlIdx = static_cast<int>(*_var);

	// only text lol
	UI_RENDER::drawString(pos._x, pos._y, UI_FONTS::TEXT_UI_FONT, UI_COLORS::WHITE, getName(), E_FONT_FLAGS::FONT_OUTLINE);
	UI_RENDER::drawString(pos._x + UI_TEXTUI::CONTROL_SPACING._x, pos._y, UI_FONTS::TEXT_UI_FONT, _displayText.at(controlIdx)._color, _displayText.at(controlIdx)._name, E_FONT_FLAGS::FONT_ALIGN_R | E_FONT_FLAGS::FONT_OUTLINE);

	if ((getFlags() & E_UI_FLAGS::UI_ACTIVE) && getDrawGroup()) {
		getDrawGroup()->render();
	}
}

void Text_Bool::update() {
	
	auto parent = dynamic_pointer_cast<UI_BaseText>(getParent());
	_drawPosition = parent->getPosition() + getPosition();

	if ((getFlags() & E_UI_FLAGS::UI_ACTIVE) && getDrawGroup()) {

		const auto tmpPos = POINT_INT(_drawGroupPosition._x + UI_TEXTUI::DRAWGROUP_SPACING._x, _drawGroupPosition._y);

		// position is where the items will be drawn from :(
		getDrawGroup()->setPosition(tmpPos);
		getDrawGroup()->setDrawGroupPosition(tmpPos);

		getDrawGroup()->update();
	}
}

void Text_Bool::input() {

	if (getParent()->getFlags() & E_UI_FLAGS::UI_DRAWGROUP_ACTIVE) {

		// toggle
		if (UI_INPUT::isPressed(UI_KEYS::K_SELECT)) {
			*_var ^= 1;
		}
	}
	else if ((getFlags() & E_UI_FLAGS::UI_ACTIVE) && getDrawGroup()) {
		getDrawGroup()->input();
	}
}