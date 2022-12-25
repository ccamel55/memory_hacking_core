#pragma once

#include "UI_Definitions.hpp"

#include "../../rendering/directx9/Directx9Render.hpp"
#include "../../rendering/directx11/Directx11Render.hpp"
#include "../../rendering/opengl3/OpenGL3Render.hpp"

namespace CORE {

	class UI_RenderFactory : public Singleton<UI_RenderFactory> {
	public:
		void setImpl(C_RenderImpl& impl) {
			_renderImpl = &impl;
		}

		C_RenderImpl* getImpl() {
			return _renderImpl;
		}
	private:
		C_RenderImpl* _renderImpl{};
	};

	namespace UI_INPUT {

		/* maybe do the same thing we did with the renderer? but doubt there wil be different render systems */
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

		static __forceinline size_t lastKey() {
			return C_InputHandler::get().getLastKey();
		}
	}

	namespace UI_RENDER {

		static __forceinline POINT& getScreenSize() {
			return UI_RenderFactory::get().getImpl()->getScreenSize();
		}

		static __forceinline void addFont(hash_t hash, const std::string& family, size_t height, size_t weight) {
			return UI_RenderFactory::get().getImpl()->addFont(hash, family, height, weight);
		}

		static __forceinline void drawRect(int x, int y, int w, int h, DWORD col) {
			UI_RenderFactory::get().getImpl()->drawRect(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), col);
		}

		static __forceinline void drawRectFill(int x, int y, int w, int h, DWORD col) {
			UI_RenderFactory::get().getImpl()->drawRectFill(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), col);
		}

		static __forceinline void drawRectFillGradientH(int x, int y, int w, int h, DWORD colL, DWORD colR) {
			UI_RenderFactory::get().getImpl()->drawRectFillGradientH(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), colL, colR);
		}

		static __forceinline void drawRectFillGradientV(int x, int y, int w, int h, DWORD colT, DWORD colB) {
			UI_RenderFactory::get().getImpl()->drawRectFillGradientV(static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h), colT, colB);
		}

		static __forceinline void drawCdrawCircleircle(int x, int y, int r, DWORD col) {
			UI_RenderFactory::get().getImpl()->drawCircle(static_cast<float>(x), static_cast<float>(y), static_cast<float>(r), col);
		}

		static __forceinline void drawCircleFill(int x, int y, int r, DWORD col) {
			UI_RenderFactory::get().getImpl()->drawCircleFill(static_cast<float>(x), static_cast<float>(y), static_cast<float>(r), col);
		}

		static __forceinline void drawCircleFillGradient(int x, int y, int r, DWORD colI, DWORD colO) {
			UI_RenderFactory::get().getImpl()->drawCircleFillGradient(static_cast<float>(x), static_cast<float>(y), static_cast<float>(r), colI, colO);
		}

		static __forceinline void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, DWORD col) {
			UI_RenderFactory::get().getImpl()->drawTriangle(static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(x3), static_cast<float>(y3), col);
		}

		static __forceinline void drawTriangleFill(int x1, int y1, int x2, int y2, int x3, int y3, DWORD col) {
			UI_RenderFactory::get().getImpl()->drawTriangleFill(static_cast<float>(x1), static_cast<float>(y1), static_cast<float>(x2), static_cast<float>(y2), static_cast<float>(x3), static_cast<float>(y3), col);
		}

		static __forceinline void drawString(int x, int y, hash_t font, DWORD col, const std::string& str, uint8_t flags = 0) {
			UI_RenderFactory::get().getImpl()->drawString(static_cast<float>(x), static_cast<float>(y), font, col, str, flags);
		}

		static __forceinline size_t getStringWidth(hash_t hash, const std::string& str) {
			return UI_RenderFactory::get().getImpl()->getStringWidth(hash, str);
		}

		static __forceinline size_t getStringHeight(hash_t hash) {
			return UI_RenderFactory::get().getImpl()->getStringHeight(hash);
		}
	}
}