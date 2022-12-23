#pragma once

#include <vector>

#include "UI_BaseControl.hpp"

#include "../form_common/Form_Groupbox.hpp"
#include "../form_common/Form_Button.hpp"
#include "../form_common/Form_Checkbox.hpp"
#include "../form_common/Form_Combobox.hpp"
#include "../form_common/Form_Slider.hpp"
#include "../form_common/Form_TextInput.hpp"
#include "../form_common/Form_Listbox.hpp"

namespace CORE {

	namespace UI_FORM {

		// either side we have 5 pixel border
		constexpr POINT_INT BORDER_SIZE = { 7, 7 };

		// draggable title bar size
		constexpr POINT_INT TITLE_SIZE = { 0, 20 };

		// contents box offsets
		constexpr POINT_INT CONTENT_POS = { BORDER_SIZE._x, TITLE_SIZE._y };
		constexpr POINT_INT CONTENT_SIZE = { -BORDER_SIZE._x * 2, -TITLE_SIZE._y - BORDER_SIZE._y };

		// spacing for our pinned circle
		constexpr POINT_INT PINNED_OFFSET = { 10, TITLE_SIZE._y / 2 };

		// size and position of groupbox selector
		constexpr POINT_INT SELECTOR_OFFSET = { -20, 0 };
		constexpr POINT_INT SELECTOR_SPACING = { 70, 0 };
		constexpr POINT_INT SELECTOR_RADIUS = { 6, 4 };
	}

	class UI_BaseForm : public UI_BaseControl {
	public:
		void render() override;
		void update() override;
		void input() override;

		std::shared_ptr<Form_Groupbox> getFocused();
		void setFocused(std::shared_ptr<Form_Groupbox> focused);

		std::shared_ptr<Form_Groupbox> addGroupbox(const std::string& name);
	protected:
		POINT_INT _controlSize{};
		POINT_INT _controlPosition{};

		bool _dragging{};
		size_t _focusedIdx{};

		std::shared_ptr<Form_Groupbox> _focused{};

		std::vector<std::string> _groupboxNames{};
		std::vector<std::shared_ptr<Form_Groupbox>> _groupboxes{};
	};
}