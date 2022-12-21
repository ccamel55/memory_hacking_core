#include "Common_GroupBox.hpp"

using namespace CORE;

Common_GroupBox::Common_GroupBox(bool tab) {

	_pos.x = UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.x;
	_pos.y = UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.y;
}

Common_GroupBox::~Common_GroupBox() {

}

void Common_GroupBox::onRender(bool open) {

	if (open) {
		const auto& pos = getDrawPos();
		RENDER::drawRect(pos.x, pos.y, _size.x, _size.y, COLORS::GRAY);
	}
}

void Common_GroupBox::onUpdate() {

}

void* Common_GroupBox::getDataBuffer() {
	throw std::exception("groupbox has not acces to data buffer!");
}

void Common_GroupBox::addChild(const std::shared_ptr<UI_ControlElement>& c) {

	c->setParent(shared_from_this());

	// controls also use relative position!
	c->setPos(_controlOffset);
	_children.emplace_back(c);

	_controlOffset.y += UI_CONTROL_CONSTANTS::CONTROL_SPACING.y;
}