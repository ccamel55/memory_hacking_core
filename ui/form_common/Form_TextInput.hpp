#pragma once

#include <functional>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

    constexpr std::string_view VIRTUAL_KEYCODES[223] = { "INVALID", "MOUSE1", "MOUSE2", "", "MOUSE3", "MOUSE4", "MOUSE5", "",
                                                        "BACKSPACE", "TAB", "", "", "", "ENTER", "", "", "SHIFT", "CONTROL", "ALT",
                                                        "PAUSE", "CAPSLOCK", "", "", "", "", "", "", "ESC", "", "", "", "",
                                                        "SPACE", "PAGEUP", "PAGEDOWN", "END", "HOME", "LEFT", "UP", "RIGHT",
                                                        "DOWN", "", "", "", "", "INS", "DEL", "", "0", "1", "2", "3",
                                                        "4", "5", "6", "7", "8", "9", "", "", "", "", "", "", "", "a",
                                                        "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n",
                                                        "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z", "LWIN",
                                                        "RWIN", "", "", "", "NUM0", "NUM1", "NUM2", "NUM3", "NUM4", "NUM5",
                                                        "NUM6", "NUM7", "NUM8", "NUM9", "*", "+", "_", "-", ".", "/", "F1",
                                                        "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "F10", "F11", "F12",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "SCROLL", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "LSHIFT", "RSHIFT", "LCONTROL", "RCONTROL", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", ";", "+", ",", "-", ".", "/?", "~", "", "", "", "", "",
                                                        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
                                                        "", "", "", "", "{", "\\", "}", "/" };

	class Form_TextInput : public UI_BaseControl {
	public:
        Form_TextInput(std::string* data, size_t maxLength = 30);
        ~Form_TextInput();

		void render();
		void update();
		void input();
	protected:
        int _inputPos{};
        size_t _maxLength{};

		POINT_INT _absolutePosition{};
		std::string* _data{};
	};
}