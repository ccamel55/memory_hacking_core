#pragma once

#include "../../interfaces/UI_BaseText.hpp"
#include "Text_Drawgroup.hpp"

namespace CORE {

	class Text_Bool : public UI_BaseText {
	public:
		Text_Bool(const std::string& name, uint32_t var, const BOOL_CONTROL_TEXT& displayText);
		~Text_Bool();

		void render();
		void update();
		void input();
	private:
		bool* _var{};
		POINT_INT _drawPosition{};
		BOOL_CONTROL_TEXT _displayText{};
	};
}