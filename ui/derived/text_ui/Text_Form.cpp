#include "Text_Form.hpp"

#include "../../interfaces/UI_BaseForm.hpp"

using namespace CORE;

Text_Form::Text_Form() {

	_name = "Text UI";
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_TEXT;

	_size = { 100, UI_FORM::TITLE_SIZE._y }; // default position
	_position = { 50, 50 }; // default position

	_flags |= E_UI_FLAGS::UI_PINNED;
}

Text_Form::~Text_Form() {


}

void Text_Form::render() {

	const auto& size = getSize();
	const auto& position = getPosition();

	if (!(getFlags() & E_UI_FLAGS::UI_INPUT_ONLY)) {

		// draw main form
		UI_RENDER::drawRectFill(position._x, position._y, size._x, size._y, UI_COLORS::FORM_BORDER);

		// draw gradient bar for the title
		UI_RENDER::drawRectFillGradientV(position._x, position._y, size._x, UI_FORM::TITLE_SIZE._y, UI_COLORS::FORM_BORDER_GRADIENT, UI_COLORS::FORM_BORDER);

		// form name pinned box
		UI_RENDER::drawString(position._x + UI_FORM::PINNED_OFFSET._x + UI_FORM::CONTENT_POS._x + 8, position._y + (UI_FORM::CONTENT_POS._y / 2), UI_FONTS::WINDOW_FONT, UI_COLORS::FORM_TEXT_LABEL, getName(), E_FONT_FLAGS::FONT_CENTER_Y);

		// draw pinned circle
		UI_RENDER::drawCircleFillGradient(position._x + UI_FORM::PINNED_OFFSET._x, position._y + UI_FORM::PINNED_OFFSET._y, 4, (getFlags() & E_UI_FLAGS::UI_PINNED) ? UI_COLORS::GREEN : UI_COLORS::RED, UI_COLORS::WHITE);
	}
	else if (getFlags() & E_UI_FLAGS::UI_PINNED) {

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

	if ((!(getFlags() & E_UI_FLAGS::UI_INPUT_ONLY) || (getFlags() & E_UI_FLAGS::UI_PINNED)) && _expanded) {

		if (getDrawGroup()) {
			getDrawGroup()->render();
		}
	}
}

void Text_Form::update() {

	const auto tmpPos = POINT_INT(_position._x + 25, _position._y + UI_TEXTUI::GRAB_SIZE._y);

	if (getDrawGroup()) {

		// position is where the items will be drawn from :(
		getDrawGroup()->setPosition(tmpPos);
		getDrawGroup()->setDrawGroupPosition(tmpPos);

		getDrawGroup()->update();
	}	
}

void Text_Form::input() {

	const auto& pos = getPosition();
	const auto& size = getSize();

	if (!(getFlags() & E_UI_FLAGS::UI_INPUT_ONLY)) {
	
		if (UI_INPUT::isPressed(VK_LBUTTON)) {

			if (UI_INPUT::mouseInBounds(pos._x + UI_FORM::PINNED_OFFSET._x - 5, pos._y + UI_FORM::PINNED_OFFSET._y - 5, 10, 10)) {

				// pinned stuff here
				getFlags() ^= E_UI_FLAGS::UI_PINNED;
			}
			else if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, UI_FORM::TITLE_SIZE._y)) {

				_dragging = true;
				getFlags() |= E_UI_FLAGS::UI_BLOCKED;
			}
		}
		else if (_dragging) {

			if (UI_INPUT::isDown(VK_LBUTTON)) {

				// move current form and children
				const auto& mouseDelta = UI_INPUT::mouseDelta();
				const auto& screenSize = UI_RENDER::getScreenSize();

				POINT_INT formPos = {
					std::clamp<int>(pos._x + mouseDelta.x, 0, screenSize.x - _size._x) ,
					std::clamp<int>(pos._y + mouseDelta.y, 0, screenSize.y - _size._y) };

				setPosition(formPos);
				update();
			}
			else {

				_dragging = false;
				getFlags() &= ~E_UI_FLAGS::UI_BLOCKED;
			}
		}
	}

	if (!(getFlags() & E_UI_FLAGS::UI_INPUT_ONLY) || (getFlags() & E_UI_FLAGS::UI_PINNED)) {

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
	_drawGroup->setParent(dynamic_pointer_cast<UI_BaseText>(shared_from_this()));

	_drawGroup->getFlags() |= E_UI_FLAGS::UI_DRAWGROUP_ACTIVE;

	update();

	return _drawGroup;
}