#include "Directx11Render.hpp"

using namespace CORE::DX11;

void C_DX11Render::addFont(hash_t font, const std::string& family, size_t height, size_t weight) {

}

POINT& C_DX11Render::getScreenSize() {
	return _screenSize;
}

size_t C_DX11Render::getStringWidth(hash_t font, const std::string& text) {
	return 0;
}

size_t C_DX11Render::getStringHeight(hash_t font) {
	return 0;
}

void C_DX11Render::drawString(float x, float y, hash_t font, DWORD col, const std::string& text, uint8_t flags) {

}

void C_DX11Render::drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, uint8_t flags) {

}

void C_DX11Render::drawRect(float x, float y, float w, float h, DWORD col) {

}

void C_DX11Render::drawRectFill(float x, float y, float w, float h, DWORD col) {

}

void C_DX11Render::drawRectFillGradientH(float x, float y, float w, float h, DWORD colL, DWORD colR) {

}

void C_DX11Render::drawRectFillGradientV(float x, float y, float w, float h, DWORD colT, DWORD colB) {

}

void C_DX11Render::drawCircle(float x, float y, float r, DWORD col) {

}

void C_DX11Render::drawCircleFill(float x, float y, float r, DWORD col) {

}

void C_DX11Render::drawCircleFillGradient(float x, float y, float r, DWORD colO, DWORD colI) {

}

void C_DX11Render::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) {

}

void C_DX11Render::drawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) {

}
