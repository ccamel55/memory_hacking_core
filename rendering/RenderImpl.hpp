#pragma once

#include <memory>
#include <string>

#include "../singleton.hpp"
#include "../cryptography/fn1v.hpp"

#include "../type/Bitflag.hpp"

namespace CORE {

	enum E_FONT_FLAGS : bit_flag_t {
		FONT_ALIGN_L = 1 << 0,
		FONT_ALIGN_R = 1 << 1,
		FONT_OUTLINE = 1 << 2,
		FONT_CENTER_X = 1 << 3,
		FONT_CENTER_Y = 1 << 4,
	};

	/* contians API functions for drawing specefic geomerty */
	class C_RenderImpl {
	public:
		virtual POINT& getScreenSize() = 0;
		virtual void addFont(hash_t font, const std::string& family, size_t height, size_t weight) = 0;

		virtual size_t getStringWidth(hash_t font, const std::string& text) = 0;
		virtual size_t getStringHeight(hash_t font) = 0;
		virtual float getFrameTime() = 0;

		virtual void drawString(float x, float y, hash_t font, DWORD col, const std::string& text, bit_flag_t flags = 0) = 0;
		virtual void drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, bit_flag_t flags = 0) = 0;

		virtual void drawRect(float x, float y, float w, float h, DWORD col) = 0;
		virtual void drawRectFill(float x, float y, float w, float h, DWORD col) = 0;
		virtual void drawRectFillGradientH(float x, float y, float w, float h, DWORD colL, DWORD colR) = 0;
		virtual void drawRectFillGradientV(float x, float y, float w, float h, DWORD colT, DWORD colB) = 0;
		virtual void drawCircle(float x, float y, float r, DWORD col) = 0;
		virtual void drawCircleFill(float x, float y, float r, DWORD col) = 0;
		virtual void drawCircleFillGradient(float x, float y, float r, DWORD colO, DWORD colI) = 0;
		virtual void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) = 0;
		virtual void drawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) = 0;
	};
}