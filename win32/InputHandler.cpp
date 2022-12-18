#include "InputHandler.hpp"
#include "Console.hpp"

#include <thread>
#include <chrono>

using namespace CORE;

void C_InputHandler::attatch(const std::string& windowName, std::function<bool()> callback) {

	while (!(m_pWindowHandle = FindWindowA(windowName.c_str(), NULL))) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
	m_pCallback = callback;
	m_oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongW(m_pWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HK_WndProc)));
}

void C_InputHandler::detatch() {

	// restore old wnd proc
	if (m_oWndProc) {
		SetWindowLongW(m_pWindowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(m_oWndProc));
	}

	m_oWndProc = NULL;
}

LRESULT __stdcall C_InputHandler::HK_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	bool result = false;
	C_InputHandler::get().wndProcStart(uMsg, wParam, lParam); 
	{
		// call our input callback
		if (C_InputHandler::get().m_pCallback) {		  
			result = C_InputHandler::get().m_pCallback();
		}
	}
	C_InputHandler::get().wndProcEnd();

	if (result) {
		return TRUE;
	}

	return C_InputHandler::get().m_oWndProc(hwnd, uMsg, wParam, lParam);
}

void C_InputHandler::wndProcStart(UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// reset
	m_iCurKey = INT_MAX;
	m_curState = false;

	switch (uMsg) {
	case WM_MOUSEMOVE: {

		long x = GET_X_LPARAM(lParam);
		long y = GET_Y_LPARAM(lParam);

		// used for dragging ect.
		m_cMouseDelta.x = x - m_cMousePos.x;
		m_cMouseDelta.y = y - m_cMousePos.y;

		m_cMousePos.x = x;
		m_cMousePos.y = y;

		return;
	}
	case WM_MOUSEWHEEL: {

		m_iScrollState = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		return;
	}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN: {

		if (wParam < 256U) {

			m_iCurKey = static_cast<UINT>(wParam);
			m_curState = true;
		}

		break;
	}
	case WM_KEYUP:
	case WM_SYSKEYUP: {

		if (wParam < 256U) {

			m_iCurKey = static_cast<UINT>(wParam);
			m_curState = false;
		}

		break;
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP: {

		m_iCurKey = VK_LBUTTON;
		m_curState = uMsg == WM_LBUTTONUP ? false : true;

		break;
	}
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP: {

		m_iCurKey = VK_RBUTTON;
		m_curState = uMsg == WM_RBUTTONUP ? false : true;

		break;
	}
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP: {

		m_iCurKey = VK_MBUTTON;
		m_curState = uMsg == WM_MBUTTONUP ? false : true;

		break;
	}
	default:
		break;
	}

	// update key state if its a keyboard key
	if (m_iCurKey != INT_MAX) {
		m_aKeyState.at(m_iCurKey) = m_curState;
	}
}

void C_InputHandler::wndProcEnd() {

	// reset data and update
	if (m_iCurKey != INT_MAX) {
		m_aOldKeyState.at(m_iCurKey) = m_aKeyState.at(m_iCurKey);
	}

	m_iScrollState = 0;

	m_cMouseDelta.x = 0;
	m_cMouseDelta.y = 0;
}

POINT& C_InputHandler::getMousePos() {
	return m_cMousePos;
}

POINT& C_InputHandler::getMouseDelta() {
	return m_cMouseDelta;
}

bool C_InputHandler::keyDown(size_t key) {
	return m_aKeyState.at(key);
}

bool C_InputHandler::keyPressed(size_t key) {
	return m_aKeyState.at(key) && !m_aOldKeyState.at(key);
}

bool C_InputHandler::keyReleased(size_t key) {
	return !m_aKeyState.at(key) && m_aOldKeyState.at(key);
}

bool C_InputHandler::mouseInBounds(long x, long y, long w, long h) {
	return (m_cMousePos.x >= x) && (m_cMousePos.y >= y) && (m_cMousePos.x <= x + w) && (m_cMousePos.y <= y + h);
}