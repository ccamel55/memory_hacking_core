#pragma once

#include <functional>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Form_Checkbox : public UI_BaseControl {
	public:
		Form_Checkbox(const std::string& name, uint32_t var);
		~Form_Checkbox();

		void render();
		void update();
		void input();
	protected:
		bool* _var{};

		POINT_INT _drawSize{};
		POINT_INT _boxPosition{};
		POINT_INT _absolutePosition{};
	};
}