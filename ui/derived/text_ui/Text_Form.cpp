#include "Text_Form.hpp"

#include "../../interfaces/UI_BaseForm.hpp"

using namespace CORE;

Text_Form::Text_Form(const std::string& name) : UI_BaseDragBar(name){

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_TEXT;
	_flags.setFlag(E_UI_FLAGS::UI_PINNED);
}

Text_Form::~Text_Form() {


}

void Text_Form::render() {

	UI_BaseDragBar::render();

	const auto& position = getPosition();

	if (!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY))) {

		// nothing atm because we rendered with UI_BaseDragBar 
	}
	else if (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED)) {

		UI_RENDER::drawString(position._x, position._y, UI_FONTS::TEXT_UI_FONT, UI_COLORS::WHITE, "[  ]", E_FONT_FLAGS::FONT_OUTLINE);
		UI_RENDER::drawString(position._x + 25, position._y, UI_FONTS::TEXT_UI_FONT, UI_COLORS::WHITE, getName(), E_FONT_FLAGS::FONT_OUTLINE);

		if (_expanded) {

			UI_RENDER::drawRectFill(position._x + 8, position._y + 5, 2, 6, UI_COLORS::GREEN);
			UI_RENDER::drawRect(position._x + 8, position._y + 5, 2, 6, UI_COLORS::BLACK);
		}
		else {

			UI_RENDER::drawRectFill(position._x + 6, position._y + 7, 6, 2, UI_COLORS::WHITE);
			UI_RENDER::drawRect(position._x + 6, position._y + 7, 6, 2, UI_COLORS::BLACK);
		}
	}

	if ((!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY)) || (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED))) && _expanded) {

		if (getDrawGroup()) {
			getDrawGroup()->render();
		}
	}
}

void Text_Form::update() {

	UI_BaseDragBar::update();

	const auto tmpPos = POINT_INT(_position._x + 25, _position._y + UI_TEXTUI::TITLE_SIZE._y);

	if (getDrawGroup()) {

		// position is where the items will be drawn from :(
		getDrawGroup()->setPosition(tmpPos);
		getDrawGroup()->setDrawGroupPosition(tmpPos);

		getDrawGroup()->update();
	}	
}

void Text_Form::input() {

	UI_BaseDragBar::input();

	if (!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY)) || (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED))) {

		if (UI_INPUT::isPressed(UI_KEYS::K_EXPAND_TEXTUI)) {
			_expanded = !_expanded;
		}
		else if (_expanded && getDrawGroup()) {
			getDrawGroup()->input();
		}	
	}
}

std::shared_ptr<Text_Drawgroup> Text_Form::addDrawgroup() {

	_drawGroup = std::make_shared<Text_Drawgroup>();
	_drawGroup->setParent(dynamic_pointer_cast<UI_BaseControl>(shared_from_this())); // allowed as we inherit UI_BaseControl

	_drawGroup->getFlags().setFlag(E_UI_FLAGS::UI_DRAWGROUP_ACTIVE);

	update();

	return _drawGroup;
}

std::shared_ptr<Text_Drawgroup> Text_Form::getDrawGroup() {
	return _drawGroup;
}