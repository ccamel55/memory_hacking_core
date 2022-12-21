#include "UI.hpp"

using namespace CORE;

UI_MainForm::UI_MainForm() : UI_FormElement() {

	_textUI;

	_pos.x = 0;
	_pos.y = 0;

	_open = false;
}

UI_MainForm::~UI_MainForm() {

}

void UI_MainForm::onRender(bool open) {

	for (auto it = _children.rbegin(); it != _children.rend(); it++) {
		auto c = *it;
		c->onRender(_open);
	}
}

void UI_MainForm::onUpdate() {

	const auto& focusedPos = _focused->getPos();
	const auto& focusedSize = _focused->getSize();

	if (_open) {
		
		// do normal click gui shit when we are open
		if (CONTROL::mouseInBounds(focusedPos.x, focusedPos.y, focusedSize.x, focusedSize.y) || _focused->isBlocking()) {
			// only every update our main form if its open or if we have it blocking every other form
			_focused->onUpdate();
		}
		else if (CONTROL::isPressed(VK_LBUTTON)) {

			// get focused window
			for (auto it = _children.begin() + 1; it != _children.end(); it++) {

				auto c = *it;

				const auto& pos = c->getPos();
				const auto& size = c->getSize();

				// bring to focus
				if (CONTROL::mouseInBounds(pos.x, pos.y, size.x, size.y)) {

					// move to front
					std::rotate(_children.begin(), it, it + 1);

					// unfocus last element
					_focused->setIsFocused(false);
				
					// focus new element
					c->setIsFocused(true);
					_focused = c;

					return;
				}
			}
		}
	}
	else {

		// process the elements in our textUI
		_textUI->processKeys();
	}
}

void* UI_MainForm::getDataBuffer() {
	// pointer to our buffer
	return &_dataBuffer;
}

void UI_MainForm::addChild(const std::shared_ptr<UI_BaseElement>& c) {

	c->setParent(shared_from_this());

	if (_children.empty()) {
		c->setIsFocused(true);
		_focused = c;
	}

	_children.push_back(c);
}

bool UI_MainForm::getOpen() {
	return _open;
}

void UI_MainForm::setOpen(bool b) {
	_open = b;
}

void UI_MainForm::addTextUI(const std::shared_ptr<UI_TextElement>& t) {

	addChild(t);
	_textUI = t;

	// force update on textUI pos
	_textUI->setDrawPos(_textUI->getPos());
	_textUI->setControlPos(_textUI->getPos());
}

C_UI::C_UI() {

}

C_UI::~C_UI() {

}

std::shared_ptr<UI_MainForm> C_UI::createMainForm() {

	if (!_mainForm) {
		_mainForm = std::make_shared<UI_MainForm>();
	}
	
	return _mainForm;
}

void C_UI::draw() {
	_mainForm->onRender(false);
}

void C_UI::input() {
	
	if (CONTROL::isPressed(CONTROL::K_EXPAND_FORM)) {
		_mainForm->setOpen(!_mainForm->getOpen());
	}

	_mainForm->onUpdate();
}

bool C_UI::isOpen() {
	return _mainForm->getOpen();
}

T_UI_Data* C_UI::getDataBuffer() {
	return static_cast<T_UI_Data*>(_mainForm->getDataBuffer());
}