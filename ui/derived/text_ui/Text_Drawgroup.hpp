#pragma once

#include "Text_BaseControl.hpp"

namespace CORE {

	class Text_Drawgroup : public Text_BaseControl {
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

			control->setParent(dynamic_pointer_cast<Text_BaseControl>(shared_from_this()));
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

		std::shared_ptr<Text_BaseControl> _active{};
		std::vector<std::shared_ptr<Text_BaseControl>> _controls{};
	};
}
