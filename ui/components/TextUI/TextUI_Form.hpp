#pragma once

#include "TextUI_DrawGroup.hpp"

#include "../../interfaces/UI_TextElement.hpp"

namespace CORE {

	class TextUI_Form : public UI_TextElement {
	public:
		TextUI_Form(int x, int y);
		~TextUI_Form();

		void onRender(bool open) override;
		void onUpdate() override;
		void processKeys() override;
		void addChild(const std::shared_ptr<UI_TextElement>& c) override;
		POINT_INT& getDrawPos() override;
		void setDrawPos(POINT_INT& p) override;
		POINT_INT& getControlPos() override;
		void setControlPos(POINT_INT& p) override;
	private:
		bool m_bOpen;
		bool m_bForceOpen;
		bool m_bDragging;

		POINT_INT m_cDrawPos;

		std::shared_ptr<TextUI_DrawGroup> m_pDrawGroup;
	};
}