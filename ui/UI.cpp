#include "UI.hpp"

#include "components/TextUI/TextUI_Form.hpp"
#include "components/TextUI/TextUI_Bool.hpp"
#include "components/TextUI/TextUI_Int.hpp"

#include "components/Console/Console_Form.hpp"
#include "components/Config/Config_Form.hpp"
#include "components/Info/Info_Form.hpp"

using namespace CORE;

UI_MainForm::UI_MainForm() : UI_FormElement() {

	_textUI;

	_pos.x = 0;
	_pos.y = 0;

	_open = false;
}

UI_MainForm::~UI_MainForm() {

}

void UI_MainForm::onRender(bool open) {

	for (auto it = _children.rbegin(); it != _children.rend(); it++) {
		auto c = *it;
		c->onRender(_open);
	}
}

void UI_MainForm::onUpdate() {

	const auto focusedPos = _focused->getPos();
	const auto focusedSize = _focused->getSize();

	if (_open) {
		
		// do normal click gui shit when we are open
		if (CONTROL::mouseInBounds(focusedPos.x, focusedPos.y, focusedSize.x, focusedSize.y) || _focused->isBlocking()) {
			// only every update our main form if its open or if we have it blocking every other form
			_focused->onUpdate();
		}
		else if (CONTROL::isPressed(VK_LBUTTON)) {

			// get focused window
			for (auto it = _children.begin() + 1; it != _children.end(); it++) {

				auto c = *it;

				const auto& pos = c->getPos();
				const auto& size = c->getSize();

				// bring to focus
				if (CONTROL::mouseInBounds(pos.x, pos.y, size.x, size.y)) {

					// move to front
					std::rotate(_children.begin(), it, it + 1);

					// unfocus last element
					_focused->setIsFocused(false);
				
					// focus new element
					c->setIsFocused(true);
					_focused = c;

					return;
				}
			}
		}
	}
	else {

		// process the elements in our textUI
		_textUI->processKeys();
	}
}

void* UI_MainForm::getDataBuffer() {
	// pointer to our buffer
	return &_dataBuffer;
}

void UI_MainForm::addChild(const std::shared_ptr<UI_BaseElement>& c) {

	c->setParent(shared_from_this());

	if (_children.empty()) {
		c->setIsFocused(true);
		_focused = c;
	}

	_children.push_back(c);
}

bool UI_MainForm::getOpen() {
	return _open;
}

void UI_MainForm::setOpen(bool b) {
	_open = b;
}

void UI_MainForm::addTextUI(const std::shared_ptr<UI_TextElement>& t) {

	addChild(t);
	_textUI = t;

	// force update on textUI pos
	_textUI->setDrawPos(_textUI->getPos());
	_textUI->setControlPos(_textUI->getPos());
}

namespace testVar {

	static bool testBool1 = false;
	static bool testBool2 = false;
	static bool testBool3 = true;
	static bool testBool4 = false;
	static bool testBool5 = true;
	static bool testBool6 = false;
	static bool testBool7 = true;
	static bool testBool8 = false;

	static int testInt1 = 0;
	static int testInt2 = 2;
	static int testInt3 = 0;
	static int testInt4 = 1;
}

C_UI::C_UI() {

	BOOL_CONTROL_TEXT boolText = {
		UI_TEXT_CONSTANTS::CONTROL_TEXT("False", COLORS::WHITE),
		UI_TEXT_CONSTANTS::CONTROL_TEXT("True", COLORS::GREEN)
	};

	INT_CONTROL_TEXT intText = {

		UI_TEXT_CONSTANTS::CONTROL_TEXT("1", COLORS::WHITE),
		UI_TEXT_CONSTANTS::CONTROL_TEXT("2", COLORS::YELLOW),
		UI_TEXT_CONSTANTS::CONTROL_TEXT("3", COLORS::GREEN),
		UI_TEXT_CONSTANTS::CONTROL_TEXT("4", COLORS::BLUE)
	};

	auto textUI = std::make_shared<TextUI_Form>(30, 60); {

		const auto boolControl1 = std::make_shared<TextUI_Bool>("Bool 1", &testVar::testBool1, boolText);
		const auto boolControl2 = std::make_shared<TextUI_Bool>("Bool 2", &testVar::testBool2, boolText); {

			const auto drawGroup2 = std::make_shared<TextUI_DrawGroup>(UI_TEXT_CONSTANTS::DRAWGROUP_SPACING.x, UI_TEXT_CONSTANTS::DRAWGROUP_SPACING.y); {

				const auto boolControl3 = std::make_shared<TextUI_Bool>("Bool 3", &testVar::testBool3, boolText);
				const auto boolControl4 = std::make_shared<TextUI_Bool>("Bool 4", &testVar::testBool4, boolText); {

					const auto drawGroup3 = std::make_shared<TextUI_DrawGroup>(UI_TEXT_CONSTANTS::DRAWGROUP_SPACING.x, UI_TEXT_CONSTANTS::DRAWGROUP_SPACING.y); {

						const auto intControl1 = std::make_shared<TextUI_Int>("Int 1", &testVar::testInt1, intText);
						const auto intControl2 = std::make_shared<TextUI_Int>("Int 2", &testVar::testInt2, intText);

						drawGroup3->addChild(intControl1);
						drawGroup3->addChild(intControl2);
					}

					boolControl4->addChild(drawGroup3);
				}

				drawGroup2->addChild(boolControl3);
				drawGroup2->addChild(boolControl4);
			}

			boolControl2->addChild(drawGroup2);
		}

		textUI->addChild(boolControl1);
		textUI->addChild(boolControl2);

		const auto intControl1 = std::make_shared<TextUI_Int>("Int 3", &testVar::testInt3, intText);
		const auto intControl2 = std::make_shared<TextUI_Int>("Int 4", &testVar::testInt4, intText);

		const auto boolControl5 = std::make_shared<TextUI_Bool>("Bool 5", &testVar::testBool5, boolText);
		const auto boolControl6 = std::make_shared<TextUI_Bool>("Bool 6", &testVar::testBool6, boolText);
		const auto boolControl7 = std::make_shared<TextUI_Bool>("Bool 7", &testVar::testBool7, boolText);
		const auto boolControl8 = std::make_shared<TextUI_Bool>("Bool 8", &testVar::testBool8, boolText);

		textUI->addChild(intControl1);
		textUI->addChild(intControl2);

		textUI->addChild(boolControl5);
		textUI->addChild(boolControl6);
		textUI->addChild(boolControl7);
		textUI->addChild(boolControl8);
	}

	// create font for UI
	RENDER::addFont(FONTS::WINDOW_FONT, "Tahoma", 14, 800);
	RENDER::addFont(FONTS::TEXT_UI_FONT, "Tahoma", 14, 800);

	_mainForm = std::make_shared<UI_MainForm>(); {

		_mainForm->addTextUI(textUI);
		_mainForm->addChild(std::make_shared<Console_Form>( 600, 400));
		_mainForm->addChild(std::make_shared<Config_Form>());
		_mainForm->addChild(std::make_shared<Info_Form>());
	}
}

C_UI::~C_UI() {

}

void C_UI::draw() {
	_mainForm->onRender(false);
}

void C_UI::input() {
	
	if (CONTROL::isPressed(VK_HOME)) {
		_mainForm->setOpen(!_mainForm->getOpen());
	}

	_mainForm->onUpdate();
}

bool C_UI::isOpen() {
	return _mainForm->getOpen();
}

T_UI_Data* C_UI::getDataBuffer() {
	return static_cast<T_UI_Data*>(_mainForm->getDataBuffer());
}