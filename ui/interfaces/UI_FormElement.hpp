#pragma once

#include "UI_Element.hpp"

namespace CORE {

	namespace UI_FORM_CONSTANTS {

		// either side we have 5 pixel border
		constexpr POINT_INT BORDER_SIZE = { 7, 7 };

		// draggable title bar size
		constexpr POINT_INT TITLE_SIZE = { 0, 20 };

		// contents box offsets
		constexpr POINT_INT CONTENT_POS = { BORDER_SIZE.x, TITLE_SIZE.y };
		constexpr POINT_INT CONTENT_SIZE = { -BORDER_SIZE.x * 2, -TITLE_SIZE.y - BORDER_SIZE.y };

		// spacing for our pinned circle
		constexpr POINT_INT PINNED_OFFSET = { -12, TITLE_SIZE.y / 2 };
	}

	// used for drawing windows such as a player list!
	class UI_FormElement : public UI_BaseElement {
	public:
		UI_FormElement();
		~UI_FormElement();

		void onRender(bool open) override;
		void onUpdate() override;
	public:
		bool getPinned();
		void setPinned(bool b);

		POINT_INT& getControlPos();
		void setControlPos();

		POINT_INT& getControlSize();
		void setControlSize();

		std::string& getTitle();
		void setTitle(const std::string& s);

		std::shared_ptr<UI_BaseElement>& getFocused();
		void setFocused(std::shared_ptr<UI_BaseElement>& f);

		std::vector<std::shared_ptr<UI_BaseElement>>& getChildren();
		virtual void addChild(const std::shared_ptr<UI_BaseElement>& c) = 0;
	protected:
		bool m_bPinned;
		bool m_bDragging;

		std::string m_sTitle;

		// where window for where controls can start drawing and how big that window is
		POINT_INT m_cControlPos;
		POINT_INT m_cControlSize;

		std::shared_ptr<UI_BaseElement> m_pFocused;
		std::vector<std::shared_ptr<UI_BaseElement>> m_aChildren;
	};
}