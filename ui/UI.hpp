#pragma once

#include <vector>
#include <memory>

#include "../singleton.hpp"
#include "interfaces/UI_BaseElement.hpp"

#include "derived/console/Console_Form.hpp"
#include "derived/settings/Setting_Form.hpp"
#include "derived/text_ui/Text_Form.hpp"

namespace CORE {

	class C_UI : public Singleton<C_UI> {
	public:
		void render();
		void input();
		bool shouldBlockInput();

		template<class T>
		std::shared_ptr<T> addWindow(std::shared_ptr<T>&& newWindow) {

			auto window = _windows.emplace_back(std::move(newWindow));
	
			if (_focused == nullptr) {
				_focused = window;
			}

			window->update();

			return dynamic_pointer_cast<T>(window);
		}

	private:
		bool _blockInput{};
		bool _isDragging{};

		std::shared_ptr<UI_BaseElement> _focused{};
		std::vector<std::shared_ptr<UI_BaseElement>> _windows{};
	};
}