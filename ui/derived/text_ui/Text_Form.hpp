#pragma once

#include "../../interfaces/UI_BaseDragBar.hpp"
#include "Text_Drawgroup.hpp"

#include "Text_Bool.hpp"
#include "Text_Int.hpp"

namespace CORE {

	class Text_Form : public UI_BaseDragBar {
	public:
		Text_Form(const std::string& name);
		~Text_Form();

		void render();
		void update();
		void input();

		std::shared_ptr<Text_Drawgroup> addDrawgroup();
		std::shared_ptr<Text_Drawgroup> getDrawGroup();
	private:
		bool _expanded{};
		std::shared_ptr<Text_Drawgroup> _drawGroup{};
	};
}