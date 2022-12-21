#pragma once

#include "../../interfaces/UI_TextElement.hpp"
#include "TextUI_DrawGroup.hpp"

namespace CORE {

	class TextUI_Int : public UI_TextElement {
	public:
		TextUI_Int(const std::string& name, uint32_t var, const INT_CONTROL_TEXT& displayText);
		~TextUI_Int();

		void onRender(bool open) override;
		void onUpdate() override;
		void processKeys() override;
		POINT_INT& getDrawPos() override;
		void setDrawPos(POINT_INT& pos) override;
		POINT_INT& getControlPos() override;
		void setControlPos(POINT_INT& pos) override;
		void addChild(const std::shared_ptr<UI_TextElement>& c) override;
	public:
		int* _var;

		POINT_INT _drawPos;
		POINT_INT _controlPos;

		INT_CONTROL_TEXT _displayText;
	};
}