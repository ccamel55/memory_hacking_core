#pragma once

#include "UI_Element.hpp"
#include "UI_FormElement.hpp"

namespace CORE {

	namespace UI_CONTROL_CONSTANTS {

		// spacing between form and groupbox
		constexpr POINT_INT GROUPBOX_PADDING = { 10, 10 };
		
		// spacing between controls within groupboxes
		constexpr POINT_INT CONTROL_SPACING = { 0, 15 };
	}

	// used for controls such as check boxes etc.
	class UI_ControlElement : public UI_BaseElement {
	public:
		UI_ControlElement();
		~UI_ControlElement();

		virtual POINT_INT& getDrawPos();
		virtual void setDrawPos(POINT_INT& p);

		virtual POINT_INT& getControlPos();
		virtual void setControlPos(POINT_INT& p);
	protected:

		POINT_INT _drawPos{};
		POINT_INT _controlPos{};

		std::vector<std::shared_ptr<UI_ControlElement>> _children{};
	};
}