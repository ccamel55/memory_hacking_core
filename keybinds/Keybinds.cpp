#include "Keybinds.hpp"

#include "../win32/InputHandler.hpp"

using namespace CORE;

C_Keybinds::C_Keybinds() {

}

C_Keybinds::~C_Keybinds() {

}

void C_Keybinds::input() {

	// handle the inputs!!!
	const auto lastKey = CORE::C_InputHandler::get().getLastKey();
	const auto& curBind = _keyBind.at(lastKey);

	if (curBind._type == E_BIND_TYPE::BIND_INVALID) {
		return;
	}
	else if (curBind._type == E_BIND_TYPE::BIND_TOGGLE) {
		
		if (CORE::C_InputHandler::get().keyPressed(lastKey)) {

			// flip flop here comes the flip flops
			*curBind._var ^= 1;
		}
	}
	else if (curBind._type == E_BIND_TYPE::BIND_HOLD) {

		if (CORE::C_InputHandler::get().keyPressed(lastKey)) {

			// on down we toggle on
			*curBind._var = true;
		}
		else if (CORE::C_InputHandler::get().keyReleased(lastKey)) {

			// on up we toggle off
			*curBind._var = false;
		}
	}
}

void C_Keybinds::registerBind(size_t key, bool* var, E_BIND_TYPE type) {

	auto& curKey = _keyBind.at(key);

	// make sure not bind
	if (curKey._type != E_BIND_TYPE::BIND_INVALID) {
		throw std::exception("key already bound");
	}

	curKey._type = type;
	curKey._var = var;
}

void C_Keybinds::changeBindType(size_t key, E_BIND_TYPE type) {

	auto& curKey = _keyBind.at(key);

	// make sure bind
	if (curKey._type == E_BIND_TYPE::BIND_INVALID) {
		throw std::exception("key not bound");
	}

	curKey._type = type;
}

void C_Keybinds::removeBind(size_t key) {

	auto& curKey = _keyBind.at(key);

	curKey._type = E_BIND_TYPE::BIND_INVALID;
	curKey._var = nullptr;
}