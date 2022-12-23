#pragma once

#include <vector>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Form_Groupbox : public UI_BaseControl {
	public:
		Form_Groupbox();
		~Form_Groupbox();

		void render() override;
		void update() override;
		void input() override;

		void addControl(std::shared_ptr<UI_BaseControl> control);
		const POINT_INT& getControlPosition();
	private:
		POINT_INT _controlPosition{};
		POINT_INT _controlOffset{};

		std::vector<std::shared_ptr<UI_BaseControl>> _controls{};
	};
}

