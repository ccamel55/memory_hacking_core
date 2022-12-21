#pragma once

#include "../../interfaces/UI_TextElement.hpp"
#include "TextUI_DrawGroup.hpp"

namespace CORE {

	class TextUI_Bool : public UI_TextElement {
	public:
		TextUI_Bool(const std::string& name, uint32_t var, const BOOL_CONTROL_TEXT& displayText);
		~TextUI_Bool();

		void onRender(bool open) override;
		void onUpdate() override;
		void processKeys() override;
		POINT_INT& getDrawPos() override;
		void setDrawPos(POINT_INT& pos) override;
		POINT_INT& getControlPos() override;
		void setControlPos(POINT_INT& pos) override;
		void addChild(const std::shared_ptr<UI_TextElement>& c) override;
	public:
		bool* _var;

		POINT_INT _drawPos;
		POINT_INT _controlPos;

		BOOL_CONTROL_TEXT _displayText;
	};
}