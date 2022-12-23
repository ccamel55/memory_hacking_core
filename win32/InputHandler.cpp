#include "InputHandler.hpp"
#include "Console.hpp"

#include <thread>
#include <chrono>

using namespace CORE;

void C_InputHandler::attatch(const std::string& windowName, std::function<bool()> callback) {

	while (!(_windowHandle = FindWindowA(windowName.c_str(), NULL))) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
	_callback = callback;
	_wndProcOriginal = reinterpret_cast<WNDPROC>(SetWindowLongW(_windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HK_WndProc)));
}

void C_InputHandler::detatch() {

	// restore old wnd proc
	if (_wndProcOriginal) {
		SetWindowLongW(_windowHandle, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(_wndProcOriginal));
	}

	_wndProcOriginal = NULL;
}

LRESULT __stdcall C_InputHandler::HK_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	bool result = false;
	C_InputHandler::get().wndProcStart(uMsg, wParam, lParam); 
	{
		// call our input callback
		if (C_InputHandler::get()._callback) {
			result = C_InputHandler::get()._callback();
		}
	}
	C_InputHandler::get().wndProcEnd();

	if (result) {
		return TRUE;
	}

	return C_InputHandler::get()._wndProcOriginal(hwnd, uMsg, wParam, lParam);
}

void C_InputHandler::wndProcStart(UINT uMsg, WPARAM wParam, LPARAM lParam) {

	// reset
	_curKey = INT_MAX;
	_curState = false;

	switch (uMsg) {
	case WM_MOUSEMOVE: {

		long x = GET_X_LPARAM(lParam);
		long y = GET_Y_LPARAM(lParam);

		// used for dragging ect.
		_mouseDelta.x = x - _mousePos.x;
		_mouseDelta.y = y - _mousePos.y;

		_mousePos.x = x;
		_mousePos.y = y;

		return;
	}
	case WM_MOUSEWHEEL: {

		_scrollState = GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		return;
	}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN: {

		if (wParam < 256U) {

			_curKey = static_cast<UINT>(wParam);
			_curState = true;
		}

		break;
	}
	case WM_KEYUP:
	case WM_SYSKEYUP: {

		if (wParam < 256U) {

			_curKey = static_cast<UINT>(wParam);
			_curState = false;
		}

		break;
	}
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP: {

		_curKey = VK_LBUTTON;
		_curState = uMsg == WM_LBUTTONUP ? false : true;

		break;
	}
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP: {

		_curKey = VK_RBUTTON;
		_curState = uMsg == WM_RBUTTONUP ? false : true;

		break;
	}
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP: {

		_curKey = VK_MBUTTON;
		_curState = uMsg == WM_MBUTTONUP ? false : true;

		break;
	}
	default:
		break;
	}

	// update key state if its a keyboard key
	if (_curKey != INT_MAX) {
		_keyState.at(_curKey) = _curState;
	}
}

void C_InputHandler::wndProcEnd() {

	// reset data and update
	if (_curKey != INT_MAX) {
		_oldKeyState.at(_curKey) = _keyState.at(_curKey);
	}

	_scrollState = 0;

	_mouseDelta.x = 0;
	_mouseDelta.y = 0;
}

int C_InputHandler::getScrollState() {
	return _scrollState;
}

POINT& C_InputHandler::getMousePos() {
	return _mousePos;
}

POINT& C_InputHandler::getMouseDelta() {
	return _mouseDelta;
}

bool C_InputHandler::keyDown(size_t key) {
	return _keyState.at(key);
}

bool C_InputHandler::keyPressed(size_t key) {
	return _keyState.at(key) && !_oldKeyState.at(key);
}

bool C_InputHandler::keyReleased(size_t key) {
	return !_keyState.at(key) && _oldKeyState.at(key);
}

bool C_InputHandler::mouseInBounds(long x, long y, long w, long h) {
	return (_mousePos.x >= x) && (_mousePos.y >= y) && (_mousePos.x <= x + w) && (_mousePos.y <= y + h);
}