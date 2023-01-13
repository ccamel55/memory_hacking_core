#include "UI_BaseForm.hpp"

#include <algorithm>

using namespace CORE;

UI_BaseForm::UI_BaseForm(const std::string& name, const POINT_INT& size) {

	_name = name;
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_FORM;

	_size = size;
	_position = { 50, 50 }; // default position
}

void UI_BaseForm::render() {

	const auto& size = getSize();
	const auto& position = getPosition();

	if (!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY))) {

		// draw main form
		UI_RENDER::drawRectFill(position._x, position._y, size._x, size._y, UI_COLORS::FORM_BORDER);

		// draw gradient bar for the title
		UI_RENDER::drawRectFillGradientV(position._x, position._y, size._x, UI_FORM::TITLE_SIZE._y, UI_COLORS::FORM_BORDER_GRADIENT, UI_COLORS::FORM_BORDER);

		// draw control render regin
		UI_RENDER::drawRectFill(_controlPosition._x, _controlPosition._y, _controlSize._x, _controlSize._y, UI_COLORS::FORM_CONTENTS);

		// form name pinned box
		UI_RENDER::drawString(position._x + UI_FORM::PINNED_OFFSET._x + UI_FORM::CONTENT_POS._x + 4, position._y + (UI_FORM::CONTENT_POS._y / 2), UI_FONTS::WINDOW_FONT, UI_COLORS::FORM_TEXT_LABEL, getName(), E_FONT_FLAGS::FONT_CENTER_Y);

		// draw pinned circle
		UI_RENDER::drawCircleFillGradient(position._x + UI_FORM::PINNED_OFFSET._x, position._y + UI_FORM::PINNED_OFFSET._y, 4, (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED)) ? UI_COLORS::GREEN : UI_COLORS::RED, UI_COLORS::WHITE);

		// draw groupbox selection
		if (_groupboxes.size() > 1) {

			// left and right arrow
			UI_RENDER::drawTriangleFill(_leftPosition._x - UI_FORM::SELECTOR_RADIUS._x, _leftPosition._y, _leftPosition._x, _leftPosition._y + UI_FORM::SELECTOR_RADIUS._y, _leftPosition._x, _leftPosition._y - UI_FORM::SELECTOR_RADIUS._y, _focusedIdx == 0 ? UI_COLORS::CONFIG_TAB_FILL2 : UI_COLORS::CONFIG_TAB_FILL1);
			UI_RENDER::drawTriangleFill(_rightPosition._x + UI_FORM::SELECTOR_RADIUS._x, _rightPosition._y, _rightPosition._x, _rightPosition._y + UI_FORM::SELECTOR_RADIUS._y, _rightPosition._x, _rightPosition._y - UI_FORM::SELECTOR_RADIUS._y, _focusedIdx == _groupboxes.size() - 1 ? UI_COLORS::CONFIG_TAB_FILL2 : UI_COLORS::CONFIG_TAB_FILL1);

			// name of current tab
			UI_RENDER::drawString(_leftPosition._x + (UI_FORM::SELECTOR_SPACING._x / 2), _leftPosition._y, UI_FONTS::TAB_FONT, UI_COLORS::WHITE, _groupboxNames.at(_focusedIdx), E_FONT_FLAGS::FONT_CENTER_X | E_FONT_FLAGS::FONT_CENTER_Y);
		}
	}
	else if (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED)) {

		// draw control region but with less background alpha!
		UI_RENDER::drawRectFill(_controlPosition._x, _controlPosition._y, _controlSize._x, _controlSize._y, UI_COLORS::FORM_CONTENTS_PINNED);
	}

	if (getFocused()) {
		getFocused()->render();
	}
}

void UI_BaseForm::update() {

	_controlPosition._x = _position._x + UI_FORM::CONTENT_POS._x;
	_controlPosition._y = _position._y + UI_FORM::CONTENT_POS._y;

	_controlSize._x = _size._x + UI_FORM::CONTENT_SIZE._x;
	_controlSize._y = _size._y + UI_FORM::CONTENT_SIZE._y;

	_rightPosition = POINT_INT(_position._x + _size._x + UI_FORM::SELECTOR_OFFSET._x, _position._y + (UI_FORM::CONTENT_POS._y / 2));
	_leftPosition = POINT_INT(_rightPosition._x - UI_FORM::SELECTOR_SPACING._x, _rightPosition._y);

	const auto tmpPos = POINT_INT(_controlPosition._x + UI_CONTROL::GROUPBOX_PADDING._x, _controlPosition._y + UI_CONTROL::GROUPBOX_PADDING._y);

	if (_focused) {
		_focused->setPosition(tmpPos);
		_focused->update();
	}
}

void UI_BaseForm::input() {

	const auto& pos = getPosition();
	const auto& size = getSize();

	if (UI_INPUT::isPressed(VK_LBUTTON)) {

		// draw groupbox selection
		if (_groupboxes.size() > 1 && UI_INPUT::mouseInBounds(_leftPosition._x - UI_FORM::SELECTOR_RADIUS._x, _leftPosition._y - UI_FORM::SELECTOR_RADIUS._y, UI_FORM::SELECTOR_RADIUS._x, UI_FORM::SELECTOR_RADIUS._y * 2)) {

			if (_focusedIdx > 0) {
				_focused = _groupboxes.at(--_focusedIdx);
				update();
			}

			return;
		}
		else if (_groupboxes.size() > 1 && UI_INPUT::mouseInBounds(_rightPosition._x, _rightPosition._y - UI_FORM::SELECTOR_RADIUS._y, UI_FORM::SELECTOR_RADIUS._x, UI_FORM::SELECTOR_RADIUS._y * 2)) {

			if (_focusedIdx < _groupboxes.size() - 1) {
				_focused = _groupboxes.at(++_focusedIdx);
				update();
			}

			return;
		}
		else if (UI_INPUT::mouseInBounds(pos._x + UI_FORM::PINNED_OFFSET._x - 5, pos._y + UI_FORM::PINNED_OFFSET._y - 5, 10, 10)) {

			// pinned stuff here
			getFlags().toggleFlag(E_UI_FLAGS::UI_PINNED);

			return;
		}
		else if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, UI_FORM::TITLE_SIZE._y)) {

			_dragging = true;
			getFlags().setFlag(E_UI_FLAGS::UI_BLOCKED);

			return;
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

		return;
	}

	if (getFocused()) {

		getFocused()->input();

		if (getFocused()->getFlags().hasFlag(E_UI_FLAGS::UI_BLOCKED)) {
			getFlags().setFlag(E_UI_FLAGS::UI_BLOCKED);
		}
		else {
			getFlags().removeFlag(E_UI_FLAGS::UI_BLOCKED);
		}
	}
}

std::shared_ptr<Form_Groupbox> UI_BaseForm::getFocused() {
	return _focused;
}

void UI_BaseForm::setFocused(std::shared_ptr<Form_Groupbox> focused) {
	_focused = focused;
}

std::shared_ptr<Form_Groupbox> UI_BaseForm::addGroupbox(const std::string& name) {

	auto groupbox = _groupboxes.emplace_back(std::make_shared<Form_Groupbox>());
	_groupboxNames.emplace_back(name);

	groupbox->setParent(dynamic_pointer_cast<UI_BaseControl>(shared_from_this()));

	const auto groupboxSize = POINT_INT(_controlSize._x - (UI_CONTROL::GROUPBOX_PADDING._x * 2), _controlSize._y - (UI_CONTROL::GROUPBOX_PADDING._y * 2));
	groupbox->setSize(groupboxSize);

	const auto groupboxPos = POINT_INT(_controlPosition._x + UI_CONTROL::GROUPBOX_PADDING._x, _controlPosition._y + UI_CONTROL::GROUPBOX_PADDING._y);
	groupbox->setPosition(groupboxPos);

	if (_groupboxes.size() == 1) {
		_focusedIdx = 0;
		_focused = groupbox;
	}

	groupbox->update();
	return groupbox;
}