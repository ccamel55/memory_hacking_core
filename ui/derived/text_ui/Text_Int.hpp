#pragma once

#include "Text_BaseControl.hpp"
#include "Text_Drawgroup.hpp"

namespace CORE {

	class Text_Int : public Text_BaseControl {
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