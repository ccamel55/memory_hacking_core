#pragma once

#include <Windows.h>

#include <string>
#include <array>

namespace CORE {

	struct T_TexCoOrd {
		float _x1;
		float _y1;
		float _x2;
		float _y2;
		float _w;
		float _h;
	};

	class C_BitmapFont {
	public:
		C_BitmapFont();
		~C_BitmapFont();
		void release();
		void setFont(const std::string& fontFamily, size_t height, size_t weight);
		float getStringHeight();
		float getStringWidth(const std::string& text);
		DWORD* getFontBitmap();
		int getWidth();
		int getHeight();
		DWORD getSpacing();
		T_TexCoOrd& getTextCoords(size_t c);
	private:
		DWORD* _bitmapPtr;
		HBITMAP _bitmapHandle;

		int _width;
		int _height;
		DWORD _spacing;

		std::array<T_TexCoOrd, 128 - 32> _texCoOrds;
	};
}