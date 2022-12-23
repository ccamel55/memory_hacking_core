#pragma once

#include "../../interfaces/UI_BaseText.hpp"
#include "Text_Drawgroup.hpp"

#include "Text_Bool.hpp"
#include "Text_Int.hpp"

namespace CORE {

	class Text_Form : public UI_BaseText {
	public:
		Text_Form();
		~Text_Form();

		void render();
		void update();
		void input();
		std::shared_ptr<Text_Drawgroup> addDrawgroup();
	private:
		bool _dragging{};
		bool _expanded{};
	};
}