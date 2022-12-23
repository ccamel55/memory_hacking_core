#pragma once

#include <functional>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Form_Button : public UI_BaseControl {
	public:
		Form_Button(const std::string name, std::function<void()> callback);
		~Form_Button();

		void render();
		void update();
		void input();
	private:
		bool _clicked = false;

		POINT_INT _absolutePosition{};
		std::function<void()> _callback{};
	};
}