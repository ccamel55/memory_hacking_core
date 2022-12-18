#include "Console_Form.hpp"

using namespace CORE;

Console_Form::Console_Form(int w, int h) {

	m_cPos.x = 40;
	m_cPos.y = 40;

	m_cSize.x = w;
	m_cSize.y = h;

	m_sTitle = "Console";

	// update with current values
	setControlPos();
	setControlSize();
}

Console_Form::~Console_Form() {

}

void Console_Form::onRender(bool open) {

	// draws basic form
	UI_FormElement::onRender(open);



}

void Console_Form::onUpdate() {

	// sets position and updates children if needed to be
	UI_FormElement::onUpdate();


}

void Console_Form::addChild(const std::shared_ptr<UI_BaseElement>& c) {
	throw std::exception("console has no children!");
}

void* Console_Form::getDataBuffer() {
	throw std::exception("console has not acces to data buffer!");
}