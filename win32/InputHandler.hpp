#pragma once

#include "../../Singleton.hpp"

#include <Windows.h>
#include <windowsx.h>

#include <array>
#include <functional>

namespace CORE {

	class C_InputHandler : public Singleton<C_InputHandler> {
	public:
		C_InputHandler() {
			m_pWindowHandle = NULL;
			m_oWndProc = NULL;

			m_iScrollState = 0;

			m_cMousePos;
			m_cMouseDelta;

			m_iCurKey = 0;
			m_curState = 0;

			m_pCallback = NULL;

			std::memset(&m_aKeyState, 0, sizeof(m_aKeyState));
			std::memset(&m_aOldKeyState, 0, sizeof(m_aOldKeyState));
		}

		~C_InputHandler() {

		}

		void attatch(const std::string& windowName, std::function<bool()> callback);
		void detatch();

		void wndProcStart(UINT uMsg, WPARAM wParam, LPARAM lParam);
		void wndProcEnd();

		POINT& getMousePos();
		POINT& getMouseDelta();

		bool keyDown(size_t key);
		bool keyPressed(size_t key);
		bool keyReleased(size_t key);
		bool mouseInBounds(long x, long y, long w, long h);
		
		static LRESULT __stdcall HK_WndProc(HWND hwnd, UINT message, WPARAM w_param, LPARAM l_param);
	private:
		HWND m_pWindowHandle;
		WNDPROC m_oWndProc;

		int m_iScrollState;

		POINT m_cMousePos;
		POINT m_cMouseDelta;

		size_t m_iCurKey;
		bool m_curState;

		std::function<bool()> m_pCallback;

		std::array<bool, 256> m_aKeyState;
		std::array<bool, 256> m_aOldKeyState;
	};
}