#include "Config_Form.hpp"

using namespace CORE;

Config_Form::Config_Form() : UI_FormElement() {

	_pos.x = 50;
	_pos.y = 50;

	_size.x = 500;
	_size.y = 350;

	_title = "Settings";

	// update with current values
	setControlPos();
	setControlSize();
}

Config_Form::~Config_Form() {

}

void Config_Form::onRender(bool open) {

	// draws basic form
	UI_FormElement::onRender(open);

	const auto& pos = getPos();
	const auto& size = getSize();

	if (!_groupboxes.empty()) {

		if (open) {

			const auto RSelPos = POINT_INT(pos.x + size.x + UI_FORM_CONSTANTS::PINNED_OFFSET.x + UI_CONFIG_CONSTANTS::SELECTOR_OFFSET.x, pos.y + (UI_FORM_CONSTANTS::CONTENT_POS.y / 2));
			const auto LSelPos = POINT_INT(RSelPos.x - UI_CONFIG_CONSTANTS::SELECTOR_SPACING.x, RSelPos.y);

			// left and right arrow
			RENDER::drawTriangleFilled(LSelPos.x - UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.x, LSelPos.y, LSelPos.x, LSelPos.y + UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y, LSelPos.x, LSelPos.y - UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y, _curGroupbox == 0 ? COLORS::CONFIG_TAB_FILL2 : COLORS::CONFIG_TAB_FILL1);
			RENDER::drawTriangleFilled(RSelPos.x + UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.x, RSelPos.y, RSelPos.x, RSelPos.y + UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y, RSelPos.x, RSelPos.y - UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y, _curGroupbox == _groupboxes.size() - 1 ? COLORS::CONFIG_TAB_FILL2 : COLORS::CONFIG_TAB_FILL1);

			// name of current tab
			RENDER::drawText(LSelPos.x + (UI_CONFIG_CONSTANTS::SELECTOR_SPACING.x / 2), LSelPos.y, FONTS::TAB_FONT, COLORS::WHITE, _groupboxes.at(_curGroupbox), DX9::CENTER_X | DX9::CENTER_Y);
		}
		 
		if (open || getPinned()) {	
			_children.at(_curGroupbox)->onRender(true);
		}

		UI_FormElement::onRenderFinish(open);
	}
}

void Config_Form::onUpdate() {

	// sets position and updates children if needed to be
	const auto& pos = getPos();
	const auto& size = getSize();

	const auto RSelPos = POINT_INT(pos.x + size.x + UI_FORM_CONSTANTS::PINNED_OFFSET.x + UI_CONFIG_CONSTANTS::SELECTOR_OFFSET.x, pos.y + (UI_FORM_CONSTANTS::CONTENT_POS.y / 2));
	const auto LSelPos = POINT_INT(RSelPos.x - UI_CONFIG_CONSTANTS::SELECTOR_SPACING.x, RSelPos.y);

	if (CONTROL::isPressed(VK_LBUTTON)) {

		if (CONTROL::mouseInBounds(LSelPos.x - UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.x, LSelPos.y - UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y, UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.x, UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y * 2)) {

			if (_curGroupbox > 0) {
				_curGroupbox -= 1;
			}

			return;
		}
		else if (CONTROL::mouseInBounds(RSelPos.x, RSelPos.y - UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y, UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.x, UI_CONFIG_CONSTANTS::SELECTOR_RADIUS.y * 2)) {

			if (_curGroupbox < _groupboxes.size() - 1) {
				_curGroupbox += 1;
			}

			return;
		}
	}

	UI_FormElement::onUpdate();
	_children.at(_curGroupbox)->onUpdate();
}

void Config_Form::addGroupbox(const std::string& name, const std::shared_ptr<Common_GroupBox>& c) {

	POINT_INT tmp_size{};

	tmp_size.x = getControlSize().x - (UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.x * 2);
	tmp_size.y = getControlSize().y - (UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.y * 2);

	c->setParent(shared_from_this());
	c->setSize(tmp_size);

	_children.push_back(c);
	_groupboxes.push_back(name);

	// update position of child
	setControlPos();
}

void Config_Form::addChild(const std::shared_ptr<UI_BaseElement>& c) {
	throw std::exception("use add group not addChild for config");
}

void* Config_Form::getDataBuffer() {
	throw std::exception("config has not acces to data buffer!");
}

void Config_Form::setControlPos() {

	// make sure to call everytime we change position
	_controlPos.x = _pos.x + UI_FORM_CONSTANTS::CONTENT_POS.x;
	_controlPos.y = _pos.y + UI_FORM_CONSTANTS::CONTENT_POS.y;

	for (const auto& c : _children) {

		auto child = dynamic_pointer_cast<UI_ControlElement>(c);

		child->setDrawPos(_controlPos);
		child->setControlPos(_controlPos);
	}
}