#pragma once

#include <array>
#include <exception>

#include "../singleton.hpp"

namespace CORE {

	enum E_BIND_TYPE : size_t{
		BIND_INVALID,
		BIND_HOLD,
		BIND_TOGGLE
	};

	struct T_KeyBind {
		bool* _var{};
		E_BIND_TYPE _type{};
	};

	class C_Keybinds : public Singleton<C_Keybinds> {
	public:
		void input();
		void registerBind(size_t key, bool* var, E_BIND_TYPE type);
		void changeBindType(size_t key, E_BIND_TYPE type);
		void removeBind(size_t key);
	private:
		std::array<T_KeyBind, 256> _keyBind{};
	};
}