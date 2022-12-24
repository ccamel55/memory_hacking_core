#include "UI.hpp"

#include <algorithm>

using namespace CORE;

void C_UI::render() {

	for (auto it = _windows.rbegin(); it != _windows.rend(); it++) {

		auto w = *it;

		if (!_blockInput) {

			if ((w->getType() == E_UI_ELEMENT_TYPE::UI_ELEMENT_TEXT) || (w->getFlags() & E_UI_FLAGS::UI_PINNED)) {

				// setting as not opened will draw without window elements
				w->getFlags() |= E_UI_FLAGS::UI_INPUT_ONLY;
				w->render();
			}

			continue;
		}

		w->getFlags() &= ~E_UI_FLAGS::UI_INPUT_ONLY;
		w->render();

		// draw overlay if not in focus
		if (w != _focused) {
			UI_RenderFactory::get().getImpl()->drawRectFill(w->getPosition()._x, w->getPosition()._y, w->getSize()._x, w->getSize()._y, UI_COLORS::FORM_UNFOCUS);
		}
	}
}

void C_UI::input() {

	if (UI_INPUT::isPressed(UI_KEYS::K_EXPAND_CONFIG)) {
		_blockInput = !_blockInput;
	}

	if (_blockInput) {

		const auto& focusedSize = _focused->getSize();
		const auto& focusedPosition = _focused->getPosition();

		if (_focused->getFlags() & E_UI_FLAGS::UI_BLOCKED || UI_INPUT::mouseInBounds(focusedPosition._x, focusedPosition._y, focusedSize._x, focusedSize._y)) {

			// if our window has control or is hovered do that!!
			_focused->input();
		}
		else if (UI_INPUT::isPressed(VK_LBUTTON)) {

			for (auto it = _windows.begin() + 1; it != _windows.end(); it++) {

				auto c = *it;

				const auto& pos = c->getPosition();
				const auto& size = c->getSize();

				// bring to focus
				if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, size._y)) {

					// move to front
					std::rotate(_windows.begin(), it, it + 1);
					_focused = c;

					break;
				}
			}
		}
	}
	else {

		for (const auto& w : _windows) {

			// handle input for text menu.
			if (w->getType() == E_UI_ELEMENT_TYPE::UI_ELEMENT_TEXT) {
				w->input();
			}
		}
	}
}

bool C_UI::shouldBlockInput() {
	return _blockInput;
}

void C_UI::registerFonts() {

	// register UI fonts, must be called after setting implementation
	CORE::UI_RenderFactory::get().getImpl()->addFont(CORE::UI_FONTS::CONSOLE_FONT, "Tahoma", 12, 40);
	CORE::UI_RenderFactory::get().getImpl()->addFont(CORE::UI_FONTS::TEXT_UI_FONT, "Tahoma", 14, 800);
	CORE::UI_RenderFactory::get().getImpl()->addFont(CORE::UI_FONTS::WINDOW_FONT, "Tahoma", 14, 800);
	CORE::UI_RenderFactory::get().getImpl()->addFont(CORE::UI_FONTS::CONTROL_FONT, "Tahoma", 12, 800);
	CORE::UI_RenderFactory::get().getImpl()->addFont(CORE::UI_FONTS::TAB_FONT, "Tahoma", 12, 400);
}