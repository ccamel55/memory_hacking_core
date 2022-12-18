#pragma once

#include "UI_Element.hpp"

namespace CORE {

	namespace UI_TEXT_CONSTANTS {

		// number of items we can draw per group without scrolling
		constexpr size_t DRAWGROUP_ITEM_COUNT = 12;

		// how many items we want want to have left before scrolling
		constexpr size_t DRAWGROUP_ITEM_SCROLL_PADDING = 1;

		// spacing for our drag bar
		constexpr POINT_INT TITLE_SIZE = { 80, 20 };

		constexpr POINT_INT CONTROL_SPACING = { 220, 15 };
		constexpr POINT_INT DRAWGROUP_SPACING = { 250, 0 };

		struct CONTROL_TEXT {

			CONTROL_TEXT() {
				_color = COLORS::WHITE;
				_name = "NULL";
			}

			CONTROL_TEXT(const std::string& name, DWORD colour) :
				_name(name),
				_color(colour) { }

			DWORD _color;
			std::string _name;
		};
	}

	using INT_CONTROL_TEXT = std::vector<UI_TEXT_CONSTANTS::CONTROL_TEXT>;
	using BOOL_CONTROL_TEXT = std::array<UI_TEXT_CONSTANTS::CONTROL_TEXT, 2u>;

	class UI_TextElement : public UI_BaseElement {
	public:
		UI_TextElement();
		~UI_TextElement();

		void* getDataBuffer() override;

		// special function for ingame usage etc.
		virtual void processKeys() = 0;
	public:
		bool hasControl();
		void enableControl();
		void disableControl();

		std::string& getTitle();
		void setTitle(const std::string& s);

		std::shared_ptr<UI_TextElement>& getActive();
		void setActive(const std::shared_ptr<UI_TextElement>& a);

		std::vector<std::shared_ptr<UI_TextElement>>& getChildren();
		virtual void addChild(const std::shared_ptr<UI_TextElement>& c) = 0;

		virtual POINT_INT& getControlPos() = 0;
		virtual void setControlPos(POINT_INT& p) = 0;

		virtual POINT_INT& getDrawPos() = 0;
		virtual void setDrawPos(POINT_INT& p) = 0;
	protected:
		bool _hasControl;
		std::string _title;

		std::shared_ptr<UI_TextElement> _active;
		std::vector<std::shared_ptr<UI_TextElement>> _children;
	};
}