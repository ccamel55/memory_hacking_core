#include "Config_Form.hpp"

using namespace CORE;

Config_Form::Config_Form() : UI_FormElement() {

	_pos.x = 50;
	_pos.y = 50;

	_size.x = 400;
	_size.y = 300;

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



}

void Config_Form::onUpdate() {

	// sets position and updates children if needed to be
	UI_FormElement::onUpdate();


}

void Config_Form::addChild(const std::shared_ptr<UI_BaseElement>& c) {
	
}

void* Config_Form::getDataBuffer() {
	throw std::exception("config has not acces to data buffer!");
}