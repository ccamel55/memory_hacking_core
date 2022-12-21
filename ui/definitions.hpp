#pragma once

#include "../rendering/directx9/Directx9Render.hpp"
#include "../win32/InputHandler.hpp"
#include "../cryptography/fn1v.hpp"

#include <functional>
#include <vector>
#include <string>
#include <algorithm>

// a bunch of wrapper bs so it makes using this with another sdk much easier
namespace CORE {

	struct POINT_INT {
		int x;
		int y;
	};

	namespace CONTROL {

		constexpr size_t K_EXPAND_TEXTUI = VK_INSERT;
		constexpr size_t K_EXPAND_FORM = VK_HOME;
		constexpr size_t K_SELECT = VK_DELETE;

		constexpr size_t K_UP = VK_UP;
		constexpr size_t K_DOWN = VK_DOWN;
		constexpr size_t K_LEFT = VK_LEFT;
		constexpr size_t K_RIGHT = VK_RIGHT;

		static __forceinline POINT& mousePos() {
			return C_InputHandler::get().getMousePos();
		}

		static __forceinline POINT& mouseDelta() {
			return C_InputHandler::get().getMouseDelta();
		}

		static __forceinline bool isPressed(size_t k) {
			return C_InputHandler::get().keyPressed(k);
		}

		static __forceinline bool isDown(size_t k) {
			return C_InputHandler::get().keyDown(k);
		}

		static __forceinline bool mouseInBounds(long x, long y, long w, long h) {
			return C_InputHandler::get().mouseInBounds(x, y, w, h);
		}
	}

	namespace RENDER {

		static __forceinline POINT& screenSize() {
			return DX9::C_DX9Render::get().getScreenSize();
		}

		static __forceinline void addFont(hash_t hash, const std::string& family, size_t height, size_t weight) {
			return DX9::C_DX9Render::get().addFont(hash, family, height, weight);
		}

		static __forceinline void drawRect(int x, int y, int w, int h, DWORD col) {
			DX9::C_DX9Render::get().drawRect(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), col);
		}

		static __forceinline void drawRectFilled(int x, int y, int w, int h, DWORD col) {
			DX9::C_DX9Render::get().drawRectFill(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), col);
		}

		static __forceinline void drawRectGradientH(int x, int y, int w, int h, DWORD colL, DWORD colR) {
			DX9::C_DX9Render::get().drawRectFillGradientH(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), colL, colR);
		}

		static __forceinline void drawRectGradientV(int x, int y, int w, int h, DWORD colT, DWORD colB) {
			DX9::C_DX9Render::get().drawRectFillGradientV(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), colT, colB);
		}

		static __forceinline void drawCircle(int x, int y, int r, DWORD col) {
			DX9::C_DX9Render::get().drawCircle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(r), col);
		}

		static __forceinline void drawCircleFilled(int x, int y, int r, DWORD col) {
			DX9::C_DX9Render::get().drawCircleFill(static_cast<float>(x), static_cast<float>(y), static_cast<float>(r), col);
		}

		static __forceinline void drawCircleGradient(int x, int y, int r, DWORD colI, DWORD colO) {
			DX9::C_DX9Render::get().drawCircleFillGradient(static_cast<float>(x), static_cast<float>(y), static_cast<float>(r), colO, colI);
		}

		static __forceinline void drawText(int x, int y, hash_t font, DWORD col, const std::string& str, uint8_t flags = 0) {
			DX9::C_DX9Render::get().drawString(static_cast<float>(x), static_cast<float>(y), font, col, str, flags);
		}

		static __forceinline void drawTextOutlined(int x, int y, hash_t font, DWORD col, DWORD colOutline, const std::string& str, uint8_t flags = 0) {
			DX9::C_DX9Render::get().drawStringOutline(static_cast<float>(x), static_cast<float>(y), font, col, colOutline, str, flags);
		}
	}

	namespace COLORS {

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
		constexpr DWORD BLACK = D3DCOLOR_ARGB(255, 0, 0, 0);

		// clickable stuff
		constexpr DWORD FORM_TEXT_LABEL = D3DCOLOR_ARGB(255, 255, 255, 255);

		constexpr DWORD FORM_BORDER = D3DCOLOR_ARGB(255, 64, 64, 64);
		constexpr DWORD FORM_BORDER_GRADIENT = D3DCOLOR_ARGB(255, 70, 70, 70);

		constexpr DWORD FORM_UNFOCUS = D3DCOLOR_ARGB(100, 0, 0, 0);

		constexpr DWORD FORM_CONTENTS = D3DCOLOR_ARGB(255, 200, 200, 200);
		constexpr DWORD FORM_CONTENTS_PINNED = D3DCOLOR_ARGB(120, 70, 70, 70);

		// text ui stuff
		constexpr DWORD TEXT_TEXT_LABEL = D3DCOLOR_ARGB(255, 210, 210, 210);
	}

	namespace FONTS {

		// hash_t for fonts
		constexpr hash_t TEXT_UI_FONT = C_FN1V::getCT("UI_TEXT_UI_FONT");
		constexpr hash_t WINDOW_FONT = C_FN1V::getCT("UI_WINDOW_FONT");
	}
}
