#include "Info_Form.hpp"

using namespace CORE;

Info_Form::Info_Form() : UI_FormElement() {

	_pos.x = 50;
	_pos.y = 50;

	_size.x = 400;
	_size.y = 300;

	_title = "Info Log";

	// update with current values
	setControlPos();
	setControlSize();
}

Info_Form::~Info_Form() {

}

void Info_Form::onRender(bool open) {

	// draws basic form
	UI_FormElement::onRender(open);



}

void Info_Form::onUpdate() {

	// sets position and updates children if needed to be
	UI_FormElement::onUpdate();


}

void Info_Form::addChild(const std::shared_ptr<UI_BaseElement>& c) {
	throw std::exception("Info log has no children");
}

void* Info_Form::getDataBuffer() {
	throw std::exception("Info log has no acces to data buffer!");
}