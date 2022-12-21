#include "Console_Form.hpp"

#include "../../interfaces/UI_ControlElement.hpp"

using namespace CORE;

Console_Form::Console_Form(int w, int h) {

	_pos.x = 40;
	_pos.y = 40;

	_size.x = w;
	_size.y = h;

	_title = "Console";

	// update with current values
	setControlPos();
	setControlSize();

	// register some default commands
	_commands.insert({ "help", T_ConsoleVar(E_CONSOLE_VAR_TYPE::VAR_INTERNAL, "help", "prints out all commands") });
	_commands.insert({ "clear", T_ConsoleVar(E_CONSOLE_VAR_TYPE::VAR_INTERNAL, "clear", "clears the console") });
}

Console_Form::~Console_Form() {

}

void Console_Form::onRender(bool open) {

	// draws basic form
	UI_FormElement::onRender(open);

	if (open || getPinned()) {

		const auto controlPos = POINT_INT(getControlPos().x + UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.x, getControlPos().y + UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.y);
		const auto controlSize = POINT_INT(getControlSize().x - (UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.x * 2), getControlSize().y - (UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.y * 2));

		// info box
		{
			const auto infoSize = POINT_INT(controlSize.x, controlSize.y - CONSOLE_CONSTANTS::INPUT_BOX_SIZE.y - UI_CONTROL_CONSTANTS::GROUPBOX_PADDING.y);
			RENDER::drawRectFilled(controlPos.x, controlPos.y, infoSize.x, infoSize.y, COLORS::CONSOLE_FILL);
			RENDER::drawRect(controlPos.x, controlPos.y, infoSize.x, infoSize.y, COLORS::GRAY);

			// testing lol
			int i = 0;

			for (const auto& val : _commands) {
				RENDER::drawText(controlPos.x + 10, controlPos.y + 20 + (i * 15.f), FONTS::CONSOLE_FONT, COLORS::WHITE, val.first.data());
				RENDER::drawText(controlPos.x + 100, controlPos.y + 20 + (i * 15.f), FONTS::CONSOLE_FONT, COLORS::WHITE, val.second._description.data());
				i++;
			}
		}

		// text input area
		{
			const auto inputPos = POINT_INT(controlPos.x, controlPos.y + controlSize.y - CONSOLE_CONSTANTS::INPUT_BOX_SIZE.y);
			const auto inputSize = POINT_INT(controlSize.x, CONSOLE_CONSTANTS::INPUT_BOX_SIZE.y);

			RENDER::drawRectFilled(inputPos.x, inputPos.y, inputSize.x, inputSize.y, COLORS::CONSOLE_FILL);
			RENDER::drawRect(inputPos.x, inputPos.y, inputSize.x, inputSize.y, COLORS::GRAY);
		}

		// draws grey out area
		UI_FormElement::onRenderFinish(open);
	}
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

void Console_Form::addCommand(std::string_view name, T_ConsoleVar var) {

	if (_commands.count(name) > 0) {
		throw std::exception("command already exists");
	}

	_commands.insert({ name, std::move(var)});
}