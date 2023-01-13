#include "Notification_Widget.hpp"
#include "Notifications_Form.hpp"

#include "../../interfaces/UI_BaseForm.hpp"

using namespace CORE; 

Notifications_Widget::Notifications_Widget(const std::shared_ptr<Notifications_Form> notifications) : _notificationsPtr{ notifications } {

	_name = "Notifications";
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_NOTIFICATION_WIDGET;

	_size = { 150, UI_FORM::TITLE_SIZE._y }; // default position
	_position = { 50, 50 }; // default position

	_flags.setFlag(E_UI_FLAGS::UI_PINNED);
}

void Notifications_Widget::render() {

	const auto& size = getSize();
	const auto& position = getPosition();

	if (!(getFlags().hasFlag(E_UI_FLAGS::UI_INPUT_ONLY))) {

		// draw main form
		UI_RENDER::drawRectFill(position._x, position._y, size._x, size._y, UI_COLORS::FORM_BORDER);

		// draw gradient bar for the title
		UI_RENDER::drawRectFillGradientV(position._x, position._y, size._x, UI_FORM::TITLE_SIZE._y, UI_COLORS::FORM_BORDER_GRADIENT, UI_COLORS::FORM_BORDER);

		// form name pinned box
		UI_RENDER::drawString(position._x + UI_FORM::PINNED_OFFSET._x + UI_FORM::CONTENT_POS._x + 8, position._y + (UI_FORM::CONTENT_POS._y / 2), UI_FONTS::WINDOW_FONT, UI_COLORS::FORM_TEXT_LABEL, getName(), E_FONT_FLAGS::FONT_CENTER_Y);

		// draw pinned circle
		UI_RENDER::drawCircleFillGradient(position._x + UI_FORM::PINNED_OFFSET._x, position._y + UI_FORM::PINNED_OFFSET._y, 4, (getFlags().hasFlag(E_UI_FLAGS::UI_PINNED)) ? UI_COLORS::GREEN : UI_COLORS::RED, UI_COLORS::WHITE);
	}

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

	_drawPos = POINT_INT(_position._x, _position._y + UI_FORM::TITLE_SIZE._y + UI_CONTROL::GROUPBOX_PADDING._y);
}

void Notifications_Widget::input() {

	const auto& pos = getPosition();
	const auto& size = getSize();

	if (UI_INPUT::isPressed(VK_LBUTTON)) {

		if (UI_INPUT::mouseInBounds(pos._x + UI_FORM::PINNED_OFFSET._x - 5, pos._y + UI_FORM::PINNED_OFFSET._y - 5, 10, 10)) {

			// pinned stuff here
			getFlags().toggleFlag(E_UI_FLAGS::UI_PINNED);
		}
		else if (UI_INPUT::mouseInBounds(pos._x, pos._y, size._x, UI_FORM::TITLE_SIZE._y)) {

			_dragging = true;
			getFlags().setFlag(E_UI_FLAGS::UI_BLOCKED);
		}
	}
	else if (_dragging) {

		if (UI_INPUT::isDown(VK_LBUTTON)) {

			// move current form and children
			const auto& mouseDelta = UI_INPUT::mouseDelta();
			const auto& screenSize = UI_RENDER::getScreenSize();

			POINT_INT formPos = {
				std::clamp<int>(pos._x + mouseDelta.x, 0, screenSize.x - _size._x) ,
				std::clamp<int>(pos._y + mouseDelta.y, 0, screenSize.y - _size._y) };

			setPosition(formPos);
			update();
		}
		else {

			_dragging = false;
			getFlags().removeFlag(E_UI_FLAGS::UI_BLOCKED);
		}
	}
}