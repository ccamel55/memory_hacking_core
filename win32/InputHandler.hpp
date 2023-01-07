#pragma once

#include "../singleton.hpp"

#include <Windows.h>
#include <windowsx.h>

#include <array>
#include <functional>

#include <string>

namespace CORE {

	class C_InputHandler : public Singleton<C_InputHandler> {
	public:
		void attatch(HWND windowHandle, std::function<bool()> callback);
		void detatch();

		void wndProcStart(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void wndProcEnd();

		int getScrollState();
		size_t getLastKey();

		POINT& getMousePos();
		POINT& getMouseDelta();

		bool keyDown(size_t key);
		bool keyPressed(size_t key);
		bool keyReleased(size_t key);
		bool mouseInBounds(long x, long y, long w, long h);
		
		static LRESULT __stdcall HK_WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);
	private:
		HWND _windowHandle{};
		WNDPROC _wndProcOriginal{};

		int _scrollState{};

		POINT _mousePos{};
		POINT _mouseDelta{};

		size_t _curKey{};
		bool _curState{};

		std::function<bool()> _callback{};

		std::array<bool, 256> _keyState{};
		std::array<bool, 256> _oldKeyState{};
	};
}