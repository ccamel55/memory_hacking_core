#pragma once

#include <functional>

#include "../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Form_Listbox : public UI_BaseControl {
	public:
		Form_Listbox(const std::vector<std::string>* items, size_t* selected);
		~Form_Listbox();

		void render();
		void update();
		void input();
	protected:
		int _cursor{};
		int _scroll{};
		int _selected{};

		size_t* _selectedVar{};
	
		POINT_INT _absolutePosition{};
		POINT_INT _textPosition{};

		const std::vector<std::string>* _items{};
	};
}