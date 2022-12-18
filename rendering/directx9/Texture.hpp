#pragma once

#include <d3d9.h>
#include <exception>

namespace CORE::DX9 {

	class C_Texture {
	public:
		C_Texture();
		~C_Texture();
		void release();
		void bindBitmap(IDirect3DDevice9* device, const DWORD* bitmap, int bitmapWidth, int bitmapHeight);
		IDirect3DTexture9* getTexture();
	private:
		IDirect3DTexture9* m_pTexture;
	};
}