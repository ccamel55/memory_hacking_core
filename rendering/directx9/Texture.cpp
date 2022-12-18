#include "Texture.hpp"

using namespace CORE::DX9;

C_Texture::C_Texture() {
	m_pTexture = NULL;
}

C_Texture::~C_Texture() {
	release();
}

void C_Texture::release() {

	if (m_pTexture) {
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

void C_Texture::bindBitmap(IDirect3DDevice9* device, const DWORD* bitmap, int bitmapWidth, int bitmapHeight) {

	if (FAILED(device->CreateTexture(bitmapWidth, bitmapHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_pTexture, NULL))) {
		throw std::exception("Failed to create texture");
	}

	// map bitmap to texture
	D3DLOCKED_RECT rect = {};
	m_pTexture->LockRect(0, &rect, 0, 0);

	// oop D3DFMT_A8R8G8B8 = 4 x 8bits or just 4 bytes
	auto texData = reinterpret_cast<unsigned int*>(rect.pBits);

	for (int y = 0; y < bitmapHeight; y++) {

		for (int x = 0; x < bitmapWidth; x++) {

			const auto alpha = (unsigned char)((bitmap[bitmapWidth * y + x] & 0xff) >> 4);

			if (alpha > 0) {

				// draw with color and full alpha
				texData[bitmapWidth * y + x] = static_cast<DWORD>(0xFF000000 | bitmap[bitmapWidth * y + x]);
			}
			else {
				texData[bitmapWidth * y + x] = 0x00000000;
			}
		}
	}

	m_pTexture->UnlockRect(0);
}

IDirect3DTexture9* C_Texture::getTexture() {
	return m_pTexture;
}