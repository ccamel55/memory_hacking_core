#pragma once

#include <functional>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Form_Combobox : public UI_BaseControl {
	public:
		Form_Combobox(const std::string& name, uint32_t var, std::vector<std::string>* comboItems);
		~Form_Combobox();

		void render();
		void update();
		void input();
	protected:
		int* _var{};
		bool _hovered{};

		POINT_INT _leftPosition{};
		POINT_INT _rightPosition{};

		POINT_INT _absolutePosition{};

		size_t _curItem{};
		std::vector<std::string>* _comboItems{};
	};
}