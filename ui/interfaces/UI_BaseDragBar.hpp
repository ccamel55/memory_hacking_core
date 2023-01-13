#pragma once

#include "UI_BaseControl.hpp"

namespace CORE {

	namespace UI_DRAG_BAR {

		constexpr size_t DRAG_BAR_WIDTH = 150;
	}

	class UI_BaseDragBar : public UI_BaseControl {
	public:
		UI_BaseDragBar() = default;
		UI_BaseDragBar(const std::string& name);

		~UI_BaseDragBar();

		void render();
		void update();
		void input();
	protected:
		bool _dragging{};
	};
}