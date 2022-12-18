#pragma once

#include "../../Singleton.hpp"

#include <Windows.h>

#include <iostream>
#include <format>

namespace CORE {

	class C_Console : public Singleton<C_Console> {
	public:
		C_Console() {
			m_pHandle = nullptr;
		}

		~C_Console() {
			m_pHandle = nullptr;
		}

		void attatch();
		void detatch();
		void println(const std::string& str);
	private:
		HANDLE m_pHandle;
	};
}