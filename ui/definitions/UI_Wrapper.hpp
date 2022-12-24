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
}