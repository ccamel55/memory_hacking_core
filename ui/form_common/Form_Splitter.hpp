#pragma once

#include <functional>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Form_Splitter : public UI_BaseControl {
	public:
		Form_Splitter(const std::string& name);
		~Form_Splitter();

		void render();
		void update();
		void input();
	protected:
		POINT_INT _absolutePosition{};
		POINT_INT _drawSize{};
	};
}