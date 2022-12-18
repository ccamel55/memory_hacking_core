#pragma once

#include "../../interfaces/UI_TextElement.hpp"

namespace CORE {

	class TextUI_DrawGroup : public UI_TextElement {
	public:
		TextUI_DrawGroup(int x, int y);
		~TextUI_DrawGroup();

		void onRender(bool open) override;
		void onUpdate() override;
		void processKeys() override;
		void addChild(const std::shared_ptr<UI_TextElement>& c) override;
		POINT_INT& getDrawPos() override;
		void setDrawPos(POINT_INT& p) override;
		POINT_INT& getControlPos() override;
		void setControlPos(POINT_INT& p) override;
	private:
		int m_iCursor;
		int m_iScroll;

		POINT_INT m_cControlPos;
		POINT_INT m_cControlOffset;

		POINT_INT m_cDrawPos;
	};
}