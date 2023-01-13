#pragma once

#include <algorithm>

#include "../../cryptography/fn1v.hpp"
#include "../../win32/InputHandler.hpp"

#include "../../type/Bitflag.hpp"
#include "../../type/point/Point_Int.hpp"

namespace CORE {

	constexpr DWORD ARGB_DWORD(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
		return (((a) & 0xff) << 24) | (((r) & 0xff) << 16) | (((g) & 0xff) << 8) | ((b) & 0xff);
	}

	enum E_UI_FLAGS : bit_flag_t {
		UI_NONE = 0,
		UI_PINNED = 1 << 0,
		UI_BLOCKED = 1 << 1,
		UI_INPUT_ONLY = 1 << 2,
		UI_ACTIVE = 1 << 3,
		UI_DRAWGROUP_ACTIVE = 1 << 4,
	};

	enum E_UI_ELEMENT_TYPE : uint8_t {
		UI_ELEMENT_NONE,
		UI_ELEMENT_FORM,
		UI_ELEMENT_CONSOLE,
		UI_ELEMENT_SETTINGS,
		UI_ELEMENT_NOTIFICATIONS,
		UI_ELEMENT_NOTIFICATION_WIDGET,
		UI_ELEMENT_TEXT,
		UI_ELEMENT_CONTROL,
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

		constexpr DWORD WHITE = ARGB_DWORD(255, 255, 255, 255);
		constexpr DWORD BLUE = ARGB_DWORD(255, 45, 125, 215);
		constexpr DWORD LIGHT_BLUE = ARGB_DWORD(255, 95, 160, 250);
		constexpr DWORD GREEN = ARGB_DWORD(255, 20, 195, 55);
		constexpr DWORD RED = ARGB_DWORD(255, 215, 40, 25);
		constexpr DWORD YELLOW = ARGB_DWORD(255, 245, 245, 60);
		constexpr DWORD GRAY = ARGB_DWORD(255, 90, 90, 90);
		constexpr DWORD LIGHT_GRAY = ARGB_DWORD(255, 100, 100, 100);
		constexpr DWORD BLACK = ARGB_DWORD(255, 0, 0, 0);

		// clickable stuff
		constexpr DWORD FORM_TEXT_LABEL = ARGB_DWORD(255, 255, 255, 255);

		constexpr DWORD FORM_BORDER = ARGB_DWORD(255, 64, 64, 64);
		constexpr DWORD FORM_BORDER_GRADIENT = ARGB_DWORD(255, 70, 70, 70);

		constexpr DWORD FORM_UNFOCUS = ARGB_DWORD(100, 0, 0, 0);

		constexpr DWORD FORM_CONTENTS = ARGB_DWORD(255, 190, 190, 190);
		constexpr DWORD FORM_CONTENTS_PINNED = ARGB_DWORD(120, 70, 70, 70);

		constexpr DWORD CONFIG_TAB_FILL1 = ARGB_DWORD(255, 200, 200, 200);
		constexpr DWORD CONFIG_TAB_FILL2 = ARGB_DWORD(255, 130, 130, 130);

		// text ui stuff
		constexpr DWORD TEXT_TEXT_LABEL = ARGB_DWORD(255, 210, 210, 210);

		// control stuff
		constexpr DWORD CONTROL_OUTLINE = ARGB_DWORD(255, 90, 90, 90);
		constexpr DWORD CONTROL_OUTLINE_2 = ARGB_DWORD(255, 160, 160, 160);
		constexpr DWORD CONTROL_FILL = ARGB_DWORD(255, 174, 174, 174);
		constexpr DWORD CONTROL_FILL_2 = ARGB_DWORD(255, 166, 166, 166);
		constexpr DWORD CONTROL_FILL_3 = ARGB_DWORD(255, 200, 200, 200);
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