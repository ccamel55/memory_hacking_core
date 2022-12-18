#pragma once

#include <Windows.h>

#include <string>
#include <array>

namespace CORE {

	struct T_TexCoOrd {
		float x1;
		float y1;
		float x2;
		float y2;
		float w;
		float h;
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
		DWORD* m_pBitmap;
		HBITMAP m_hBitmap;

		int m_iWidth;
		int m_iHeight;
		DWORD m_iSpacing;

		std::array<T_TexCoOrd, 128 - 32> m_aTexCoOrds;
	};
}