#include "UI_BaseControl.hpp"

using namespace CORE;

void UI_BaseControl::setParent(std::shared_ptr<UI_BaseControl> parent) {
	_parent = parent;
}

std::shared_ptr<UI_BaseControl> UI_BaseControl::getParent() {
	return _parent;
}