#include "Notification_Widget.hpp"
#include "Notifications_Form.hpp"

#include "../../interfaces/UI_BaseForm.hpp"

using namespace CORE; 

Notifications_Widget::Notifications_Widget(const std::shared_ptr<Notifications_Form> notifications) : UI_BaseDragBar("Notifications"), _notificationsPtr{ notifications } {

	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_NOTIFICATION_WIDGET;
	_flags.setFlag(E_UI_FLAGS::UI_PINNED);
}

void Notifications_Widget::render() {

	UI_BaseDragBar::render();

	if ((!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY)) || (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED))) && _notificationsPtr) {

		const auto& notifications = *_notificationsPtr->getNotifications();

		// draw notifications
		for (size_t i = 0; i < std::min <size_t>(UI_NOTIFICATIONS::WIDGET_LOG_COUNT, notifications.size()); i++) {

			const auto& curNotification = notifications.at(i);
			const auto drawString = "[" + curNotification._creationTime + "]: " + curNotification._text;

			switch (curNotification._type)
			{
			case CORE::NOTIFICATION_INFO:
				UI_RENDER::drawString(_drawPos._x, _drawPos._y + (UI_NOTIFICATIONS::WIDGET_LOG_SIZE * i), UI_FONTS::WINDOW_FONT, UI_COLORS::WHITE, drawString);
				break;
			case CORE::NOTIFICATION_DEBUG:
				UI_RENDER::drawString(_drawPos._x, _drawPos._y + (UI_NOTIFICATIONS::WIDGET_LOG_SIZE * i), UI_FONTS::WINDOW_FONT, UI_COLORS::LIGHT_BLUE, drawString);
				break;
			case CORE::NOTIFICATION_WARNING:
				UI_RENDER::drawString(_drawPos._x, _drawPos._y + (UI_NOTIFICATIONS::WIDGET_LOG_SIZE * i), UI_FONTS::WINDOW_FONT, UI_COLORS::YELLOW, drawString);
				break;
			case CORE::NOTIFICATION_ERROR:
				UI_RENDER::drawString(_drawPos._x, _drawPos._y + (UI_NOTIFICATIONS::WIDGET_LOG_SIZE * i), UI_FONTS::WINDOW_FONT, UI_COLORS::RED, drawString);
				break;
			}
		}
	}
}

void Notifications_Widget::update() {

	UI_BaseDragBar::update();

	_drawPos = POINT_INT(_position._x, _position._y + UI_FORM::TITLE_SIZE._y + UI_CONTROL::GROUPBOX_PADDING._y);
}

void Notifications_Widget::input() {

	UI_BaseDragBar::input();
}