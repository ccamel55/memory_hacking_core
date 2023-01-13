#pragma once

#include "../../interfaces/UI_BaseText.hpp"

namespace CORE {

	class Text_Drawgroup : public UI_BaseText {
	public:
		Text_Drawgroup();
		~Text_Drawgroup();

		void render();
		void update();
		void input();

		template<class T>
		std::shared_ptr<T> addControl(std::shared_ptr<T>&& newControl) {

			auto control = _controls.emplace_back(std::move(newControl));

			if (_controls.size() <= 1) {

				_active = control;
				_active->getFlags().setFlag(E_UI_FLAGS::UI_ACTIVE);
			}

			control->setParent(dynamic_pointer_cast<UI_BaseText>(shared_from_this()));
			control->setPosition(_controlOffset);

			_controlOffset._y += UI_TEXTUI::CONTROL_SPACING._y;

			control->setDrawGroupPosition(_drawGroupPosition);
			control->update();

			return dynamic_pointer_cast<T>(control);
		}

	private:
		int _cursor{};
		int _scroll{};

		POINT_INT _controlOffset{};

		std::shared_ptr<UI_BaseText> _active{};
		std::vector<std::shared_ptr<UI_BaseText>> _controls{};
	};
}
