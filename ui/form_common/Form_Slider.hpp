#pragma once

#include <functional>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Form_Slider : public UI_BaseControl {
	public:
		Form_Slider(const std::string& name, uint32_t var, int min, int max);
		~Form_Slider();

		void render();
		void update();
		void input();
	protected:
		int* _var{};
		bool _hovered{};

		int _min{};
		int _max{};

		int _fillWidth{};
		float _sliderDelta{};

		POINT_INT _absolutePosition{};
	};
}