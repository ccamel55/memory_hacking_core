#pragma once

#include "UI_BaseElement.hpp"

namespace CORE {

	namespace UI_CONTROL {

		// spacing between form and groupbox
		constexpr POINT_INT GROUPBOX_PADDING = { 10, 10 };

		// spacing between form and groupbox
		constexpr size_t LISTBOX_ITEMS = 12;

		// spacing between form and groupbox
		constexpr POINT_INT LISTBOX_ITEM_SPACING = { 0, 16 };

		// spacing between groupbox and controls
		constexpr POINT_INT CONTROL_PADDING = { 10, 10 };

		// spacing between controls within groupboxes
		constexpr POINT_INT CONTROL_SPACING = { 20, 10 };

		// console logger stuff
		constexpr POINT_INT CONSOLE_LOG_PADDING = { 10, 10 };
		constexpr POINT_INT CONSOLE_LOG_SPACING = { 0, 12 };

		// numer of suggested to choose from
		constexpr size_t CONSOLE_INPUT_COUNT = 10;

		// size and position of groupbox selector
		constexpr POINT_INT COMBO_SELECTOR_OFFSET = { 14, 0 };
		constexpr POINT_INT COMBO_SELECTOR_RADIUS = { 6, 4 };
	}

	namespace UI_TEXTUI {

		// size of grab box
		constexpr POINT_INT GRAB_SIZE = { 100, 20 };

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
				_color = UI_COLORS::WHITE;
				_name = "NULL";
			}

			CONTROL_TEXT(const std::string& name, DWORD colour) :
				_name(name),
				_color(colour) { }

			DWORD _color;
			std::string _name;
		};
	}

	using INT_CONTROL_TEXT = std::vector<UI_TEXTUI::CONTROL_TEXT>;
	using BOOL_CONTROL_TEXT = std::array<UI_TEXTUI::CONTROL_TEXT, 2u>;

	class UI_BaseControl : public UI_BaseElement {
	public:
		void setParent(std::shared_ptr<UI_BaseControl> parent);
		std::shared_ptr<UI_BaseControl> getParent();
	protected:
		std::shared_ptr<UI_BaseControl> _parent{};
	};
 }