#include "Form_Groupbox.hpp"

using namespace CORE;

Form_Groupbox::Form_Groupbox() {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_CONSOLE;
}

Form_Groupbox::~Form_Groupbox() {

}

void Form_Groupbox::render() {

	const auto& size = getSize();
	const auto& pos = getPosition();

	UI_RENDER::drawRect(pos._x, pos._y, _size._x, _size._y, UI_COLORS::GRAY);

	for (const auto& c : _controls) {
		c->render();
	}
}

void Form_Groupbox::update() {

	_controlPosition._x = _position._x + UI_CONTROL::CONTROL_PADDING._x;
	_controlPosition._y = _position._y + UI_CONTROL::CONTROL_PADDING._y;

	for (const auto& c : _controls) {
		c->update();
	}
}

void Form_Groupbox::input() {

	if (_blocked) {

		_blocked->input();

		// unblocked so lets unlock!
		if (!(_blocked->getFlags() & E_UI_FLAGS::UI_BLOCKED)) {

			getFlags() &= ~E_UI_FLAGS::UI_BLOCKED;
			_blocked = nullptr;

			return;
		}

		return;
	}

	for (const auto& c : _controls) {

		c->input();

		if (c->getFlags() & E_UI_FLAGS::UI_BLOCKED) {
	
			// if our current control is blocking, set
			getFlags() |= E_UI_FLAGS::UI_BLOCKED;
			_blocked = c;

			break;
		}
	}
}

void Form_Groupbox::addControl(std::shared_ptr<UI_BaseControl> control) {

	auto myControl = _controls.emplace_back(control);
	myControl->setParent(dynamic_pointer_cast<UI_BaseControl>(shared_from_this()));

	const auto controlSize = POINT_INT((_size._x - UI_CONTROL::CONTROL_SPACING._x - (UI_CONTROL::CONTROL_PADDING._x * 2)) / 2, myControl->getSize()._y);

	if (_controlOffset._y + controlSize._y > (_size._y - UI_CONTROL::CONTROL_PADDING._y)) {

		_controlOffset._y = 0;
		_controlOffset._x += controlSize._x + UI_CONTROL::CONTROL_SPACING._x;
	}

	myControl->setSize(controlSize);
	myControl->setPosition(_controlOffset);

	_controlOffset._y += UI_CONTROL::CONTROL_SPACING._y + myControl->getSize()._y;

	myControl->update();
}

const POINT_INT& Form_Groupbox::getControlPosition() {
	return _controlPosition;
}