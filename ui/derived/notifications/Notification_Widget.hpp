#pragma once

#include "../../interfaces/UI_BaseText.hpp"

namespace CORE {

	class Notifications_Form;

	class Notifications_Widget : public UI_BaseControl {
	public:
		Notifications_Widget(const std::shared_ptr<Notifications_Form> _notificationsPtr);

		void render();
		void update();
		void input();
	private:
		bool _dragging{};
		const std::shared_ptr<Notifications_Form> _notificationsPtr{};

		POINT_INT _drawPos{};
	};
}