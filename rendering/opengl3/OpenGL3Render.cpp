#include "OpenGL3Render.hpp"

using namespace CORE::GL3;

void C_GL3Render::addFont(hash_t font, const std::string& family, size_t height, size_t weight) {

}

POINT& C_GL3Render::getScreenSize() {
	return _screenSize;
}

size_t C_GL3Render::getStringWidth(hash_t font, const std::string& text) {
	return 0;
}

size_t C_GL3Render::getStringHeight(hash_t font) {
	return 0;
}

float C_GL3Render::getFrameTime() {
	return 0.f;
}

void C_GL3Render::drawString(float x, float y, hash_t font, DWORD col, const std::string& text, bit_flag_t flags) {

}

void C_GL3Render::drawStringOutline(float x, float y, hash_t font, DWORD col, DWORD colOutline, const std::string& text, bit_flag_t flags) {

}

void C_GL3Render::drawRect(float x, float y, float w, float h, DWORD col) {

}

void C_GL3Render::drawRectFill(float x, float y, float w, float h, DWORD col) {

}

void C_GL3Render::drawRectFillGradientH(float x, float y, float w, float h, DWORD colL, DWORD colR) {

}

void C_GL3Render::drawRectFillGradientV(float x, float y, float w, float h, DWORD colT, DWORD colB) {

}

void C_GL3Render::drawCircle(float x, float y, float r, DWORD col) {

}

void C_GL3Render::drawCircleFill(float x, float y, float r, DWORD col) {

}

void C_GL3Render::drawCircleFillGradient(float x, float y, float r, DWORD colO, DWORD colI) {

}

void C_GL3Render::drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) {

}

void C_GL3Render::drawTriangleFill(float x1, float y1, float x2, float y2, float x3, float y3, DWORD col) {

}
