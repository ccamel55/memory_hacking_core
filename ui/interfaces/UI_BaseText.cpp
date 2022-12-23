#include "UI_BaseText.hpp"
#include "../derived/text_ui/Text_Drawgroup.hpp"

using namespace CORE;

const POINT_INT& UI_BaseText::getDrawGroupPosition() {
	return _drawGroupPosition;
}

void UI_BaseText::setDrawGroupPosition(const POINT_INT& drawGroupPosition) {
	_drawGroupPosition = drawGroupPosition;
}

std::shared_ptr<Text_Drawgroup> UI_BaseText::getDrawGroup() {
	return _drawGroup;
}

std::shared_ptr<Text_Drawgroup> UI_BaseText::addDrawgroup() {

	_drawGroup = std::make_shared<Text_Drawgroup>();
	_drawGroup->setParent(dynamic_pointer_cast<UI_BaseText>(shared_from_this()));

	update();

	return _drawGroup;
}