#pragma once

#include "UI_Element.hpp"

namespace CORE {

	// used for controls such as check boxes etc.
	class UI_ControlElement : public UI_BaseElement {
	public:
		UI_ControlElement();
		~UI_ControlElement();
	protected:
		// form this element is rendering from
		std::shared_ptr<UI_BaseElement> _form;
	};
}