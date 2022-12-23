#pragma once

#include "../../win32/InputHandler.hpp"

#include "UI_Definitions.hpp"

namespace CORE {

	namespace UI_INPUT {

		static __forceinline POINT& mousePos() {
			return C_InputHandler::get().getMousePos();
		}

		static __forceinline POINT& mouseDelta() {
			return C_InputHandler::get().getMouseDelta();
		}

		static __forceinline bool isPressed(size_t k) {
			return C_InputHandler::get().keyPressed(k);
		}

		static __forceinline bool isReleased(size_t k) {
			return C_InputHandler::get().keyReleased(k);
		}

		static __forceinline bool isDown(size_t k) {
			return C_InputHandler::get().keyDown(k);
		}

		static __forceinline bool mouseInBounds(long x, long y, long w, long h) {
			return C_InputHandler::get().mouseInBounds(x, y, w, h);
		}

		static __forceinline int scrollState() {
			return C_InputHandler::get().getScrollState();
		}
	}

	namespace UI_RENDER {

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

		static __forceinline void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, DWORD col) {
			DX9::C_DX9Render::get().drawTriangle(static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(x3), static_cast<float>(y3), col);
		}

		static __forceinline void drawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3, DWORD col) {
			DX9::C_DX9Render::get().drawTriangleFill(static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(x3), static_cast<float>(y3), col);
		}

		static __forceinline void drawText(int x, int y, hash_t font, DWORD col, const std::string& str, uint8_t flags = E_UI_FONT_FLAGS::UI_FONT_NONE) {
			
			uint8_t drawFlags = 0;

			if (flags & UI_FONT_CENTER_X) {
				drawFlags |= DX9::E_FONT_FLAGS::CENTER_X;
			}

			if (flags & UI_FONT_CENTER_Y) {
				drawFlags |= DX9::E_FONT_FLAGS::CENTER_Y;
			}

			if (flags & UI_FONT_RIGHT_ALIGN) {
				drawFlags |= DX9::E_FONT_FLAGS::ALIGN_R;
			}

			if (flags & UI_FONT_OUTLINE) {
				DX9::C_DX9Render::get().drawStringOutline(static_cast<float>(x), static_cast<float>(y), font, col, D3DCOLOR_ARGB(255, 0, 0, 0), str, drawFlags);
			}
			else {
				DX9::C_DX9Render::get().drawString(static_cast<float>(x), static_cast<float>(y), font, col, str, drawFlags);
			}
		}
	}
}