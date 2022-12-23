#pragma once

#include "../../interfaces/UI_BaseText.hpp"
#include "Text_Drawgroup.hpp"

namespace CORE {

	class Text_Int : public UI_BaseText {
	public:
		Text_Int(const std::string& name, uint32_t var, const INT_CONTROL_TEXT& displayText);
		~Text_Int();

		void render();
		void update();
		void input();
	private:
		int* _var{};
		POINT_INT _drawPosition{};
		INT_CONTROL_TEXT _displayText{};
	};
}

/*
namespace CORE {

	class Text_Int : public UI_BaseControl {
	public:
		Text_Int(const std::string& name, uint32_t var, const INT_CONTROL_TEXT& displayText);
		~Text_Int();

		void render();
		void update();
		void input();

		std::shared_ptr<Text_Drawgroup> addDrawGroup();
	private:
		int* _var;
		INT_CONTROL_TEXT _displayText{};
		std::shared_ptr<Text_Drawgroup> _drawGroup{};
	};
}
*/