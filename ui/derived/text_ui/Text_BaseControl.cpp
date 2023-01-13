#include "Text_BaseControl.hpp"
#include "Text_Drawgroup.hpp"

using namespace CORE;

const POINT_INT& Text_BaseControl::getDrawGroupPosition() {
	return _drawGroupPosition;
}

void Text_BaseControl::setDrawGroupPosition(const POINT_INT& drawGroupPosition) {
	_drawGroupPosition = drawGroupPosition;
}

std::shared_ptr<Text_Drawgroup> Text_BaseControl::getDrawGroup() {
	return _drawGroup;
}

std::shared_ptr<Text_Drawgroup> Text_BaseControl::addDrawgroup() {

	_drawGroup = std::make_shared<Text_Drawgroup>();
	_drawGroup->setParent(dynamic_pointer_cast<Text_BaseControl>(shared_from_this()));

	update();

	return _drawGroup;
}