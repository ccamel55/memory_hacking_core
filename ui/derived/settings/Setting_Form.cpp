#include "Setting_Form.hpp"

using namespace CORE;

Settings_Form::Settings_Form() {

	_name = "Settings";
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_SETTINGS;

	_size = UI_SETTINGS::FORM_SIZE;
	_position = { 50, 50 }; // default position
}

Settings_Form::~Settings_Form() {

}

void Settings_Form::render() {

	UI_BaseForm::render();
}

void Settings_Form::update() {

	UI_BaseForm::update();
}

void Settings_Form::input() {

	UI_BaseForm::input();
}