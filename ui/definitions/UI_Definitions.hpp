#pragma once

#include <algorithm>

#include "../../cryptography/fn1v.hpp"
#include "../../rendering/directx9/Directx9Render.hpp"

namespace CORE {

	enum E_UI_FLAGS : uint8_t {
		UI_NONE = 0,
		UI_PINNED = 1 << 0,
		UI_BLOCKED = 1 << 1,
		UI_INPUT_ONLY = 1 << 2,
		UI_ACTIVE = 1 << 3,
		UI_DRAWGROUP_ACTIVE = 1 << 4,
	};

	enum E_UI_FONT_FLAGS : uint8_t {
		UI_FONT_NONE = 0,
		UI_FONT_OUTLINE = 1 << 0,
		UI_FONT_CENTER_X = 1 << 1,
		UI_FONT_CENTER_Y = 1 << 2,
		UI_FONT_RIGHT_ALIGN = 1 << 3,
	};

	enum E_UI_ELEMENT_TYPE : uint8_t {
		UI_ELEMENT_NONE,
		UI_ELEMENT_CONSOLE,
		UI_ELEMENT_SETTINGS,
		UI_ELEMENT_TEXT,
		UI_ELEMENT_CONTROL,
	};

	class POINT_INT {
	public:
		constexpr POINT_INT() : _x(0), _y(0) {

		}

		constexpr POINT_INT(int x, int y) : _x(x), _y(y) {

		}

		const POINT_INT operator+(const POINT_INT& in) const {
			return POINT_INT(
				_x + in._x,
				_y + in._y
			);
		}

		const POINT_INT operator-(const POINT_INT& in) const {
			return POINT_INT(
				_x - in._x,
				_y - in._y
			);
		}

		constexpr POINT_INT& operator=(const POINT_INT& in) {
			this->_x = in._x; this->_y = in._y;
			return *this;
		}

		int _x{};
		int _y{};
	};

	namespace UI_KEYS {

		constexpr size_t K_EXPAND_TEXTUI = VK_INSERT;
		constexpr size_t K_EXPAND_CONFIG = VK_HOME;

		constexpr size_t K_SELECT = VK_DELETE;
		constexpr size_t K_UP = VK_UP;
		constexpr size_t K_DOWN = VK_DOWN;
		constexpr size_t K_LEFT = VK_LEFT;
		constexpr size_t K_RIGHT = VK_RIGHT;
	}

	namespace UI_COLORS {

		constexpr DWORD alpha(DWORD col, unsigned char a) {

			DWORD ret = col;

			// clear the alpha bits
			ret &= ~(0xFF000000);

			// apply our alpha as bits, shift to end of DWORD
			ret |= (a << 24);

			return ret;
		}

		constexpr DWORD WHITE = D3DCOLOR_ARGB(255, 255, 255, 255);
		constexpr DWORD BLUE = D3DCOLOR_ARGB(255, 45, 125, 215);
		constexpr DWORD LIGHT_BLUE = D3DCOLOR_ARGB(255, 95, 160, 250);
		constexpr DWORD GREEN = D3DCOLOR_ARGB(255, 20, 195, 55);
		constexpr DWORD RED = D3DCOLOR_ARGB(255, 215, 40, 25);
		constexpr DWORD YELLOW = D3DCOLOR_ARGB(255, 245, 245, 60);
		constexpr DWORD GRAY = D3DCOLOR_ARGB(255, 90, 90, 90);
		constexpr DWORD LIGHT_GRAY = D3DCOLOR_ARGB(255, 100, 100, 100);
		constexpr DWORD BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);

		// clickable stuff
		constexpr DWORD FORM_TEXT_LABEL = D3DCOLOR_ARGB(255, 255, 255, 255);

		constexpr DWORD FORM_BORDER = D3DCOLOR_ARGB(255, 64, 64, 64);
		constexpr DWORD FORM_BORDER_GRADIENT = D3DCOLOR_ARGB(255, 70, 70, 70);

		constexpr DWORD FORM_UNFOCUS = D3DCOLOR_ARGB(100, 0, 0, 0);

		constexpr DWORD FORM_CONTENTS = D3DCOLOR_ARGB(255, 200, 200, 200);
		constexpr DWORD FORM_CONTENTS_PINNED = D3DCOLOR_ARGB(120, 70, 70, 70);

		constexpr DWORD CONFIG_TAB_FILL1 = D3DCOLOR_ARGB(255, 200, 200, 200);
		constexpr DWORD CONFIG_TAB_FILL2 = D3DCOLOR_ARGB(255, 130, 130, 130);

		// text ui stuff
		constexpr DWORD TEXT_TEXT_LABEL = D3DCOLOR_ARGB(255, 210, 210, 210);

		// console stuff
		constexpr DWORD CONSOLE_FILL = D3DCOLOR_ARGB(40, 30, 30, 30);

		// control stuff
		constexpr DWORD CONTROL_OUTLINE = D3DCOLOR_ARGB(255, 90, 90, 90);
		constexpr DWORD CONTROL_FILL = D3DCOLOR_ARGB(255, 174, 174, 174);
		constexpr DWORD CONTROL_FILL_2 = D3DCOLOR_ARGB(255, 166, 166, 166);
		constexpr DWORD CONTROL_FILL_3 = D3DCOLOR_ARGB(255, 200, 200, 200);
	}

	namespace UI_FONTS {

		// hash_t for fonts
		constexpr hash_t CONSOLE_FONT = C_FN1V::getCT("UI_CONSOLE_FONT");
		constexpr hash_t TEXT_UI_FONT = C_FN1V::getCT("UI_TEXT_UI_FONT");
		constexpr hash_t WINDOW_FONT = C_FN1V::getCT("UI_WINDOW_FONT");
		constexpr hash_t CONTROL_FONT = C_FN1V::getCT("CONTROL_FONT");
		constexpr hash_t TAB_FONT = C_FN1V::getCT("UI_TAB_FONT");
	}
}