#include "UI_BaseDragBar.hpp"
#include "UI_BaseForm.hpp"

using namespace CORE;

UI_BaseDragBar::UI_BaseDragBar(const std::string& name) {

	_name = name;

	_size = { 150, UI_FORM::TITLE_SIZE._y };
	_position = { 50, 50 }; 
}

UI_BaseDragBar::~UI_BaseDragBar() {

}

void UI_BaseDragBar::render() {

	const auto& size = getSize();
	const auto& position = getPosition();

	if (!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY))) {

		// draw main form
		UI_RENDER::drawRectFill(position._x, position._y, size._x, size._y, UI_COLORS::FORM_BORDER);

		// draw gradient bar for the title
		UI_RENDER::drawRectFillGradientV(position._x, position._y, size._x, UI_FORM::TITLE_SIZE._y, UI_COLORS::FORM_BORDER_GRADIENT, UI_COLORS::FORM_BORDER);

		// form name pinned box
		UI_RENDER::drawString(position._x + UI_FORM::PINNED_OFFSET._x + UI_FORM::CONTENT_POS._x + 8, position._y + (UI_FORM::CONTENT_POS._y / 2), UI_FONTS::WINDOW_FONT, UI_COLORS::FORM_TEXT_LABEL, getName(), E_FONT_FLAGS::FONT_CENTER_Y);

		// draw pinned circle
		UI_RENDER::drawCircleFillGradient(position._x + UI_FORM::PINNED_OFFSET._x, position._y + UI_FORM::PINNED_OFFSET._y, 4, (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED)) ? UI_COLORS::GREEN : UI_COLORS::RED, UI_COLORS::WHITE);
	}
}

void UI_BaseDragBar::update() {

}

void UI_BaseDragBar::input() {

	const auto& pos = getPosition();
	const auto& size = getSize();

	if (!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY))) {

		if (UI_INPUT::isPressed(VK_LBUTTON)) {

			if (UI_INPUT::mouseInBounds(pos._x + UI_FORM::PINNED_OFFSET._x - 5, pos._y + UI_FORM::PINNED_OFFSET._y - 5, 10, 10)) {

				// pinned stuff here
				getFlags().toggleFlag(E_UI_FLAGS::UI_PINNED);
			}
			else if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, UI_FORM::TITLE_SIZE._y)) {

				_dragging = true;
				getFlags().setFlag(E_UI_FLAGS::UI_BLOCKED);
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
				getFlags().removeFlag(E_UI_FLAGS::UI_BLOCKED);
			}
		}
	}
}