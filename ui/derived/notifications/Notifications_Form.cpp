#include "Notifications_Form.hpp"

#include "../../../macos.hpp"
#include "../../../notifications/Notifications.hpp"

#define FMT_HEADER_ONLY
#include "../../../deps/fmt/include/fmt/core.h"

using namespace CORE;

Notifications_Form::Notifications_Form() {

	_name = "Notifications";
	_type = E_UI_ELEMENT_TYPE::UI_ELEMENT_NOTIFICATIONS;

	_size = UI_NOTIFICATIONS::FORM_SIZE;
	_position = { 50, 50 }; // default position

	_numPages = 0;
	_curPage = 0;

	_pageCount = fmt::format("{} / {}", _curPage, _numPages);
}

Notifications_Form::~Notifications_Form() {

}

void Notifications_Form::render() {

	UI_BaseForm::render();

	// render log window
	UI_RENDER::drawRectFill(_logPosition._x, _logPosition._y, _logSize._x, _logSize._y, UI_COLORS::CONTROL_FILL);

	// idk if loop can be optimized so do it manually rip!!
	{
		// column
		UI_RENDER::drawRect(_logPosition._x + _logSize._x - UI_NOTIFICATIONS::LOG_TIME_WIDTH - UI_NOTIFICATIONS::LOG_TYPE_WIDTH, _logPosition._y, 0, _logSize._y, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x + _logSize._x - UI_NOTIFICATIONS::LOG_TIME_WIDTH, _logPosition._y, 0, _logSize._y, UI_COLORS::CONTROL_FILL_2);

		// row
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 1), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 2), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 3), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 4), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 5), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 6), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 7), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 8), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
		UI_RENDER::drawRect(_logPosition._x, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * 9), _logSize._x, 0, UI_COLORS::CONTROL_FILL_2);
	}

	UI_RENDER::drawRect(_logPosition._x, _logPosition._y, _logSize._x, _logSize._y, UI_COLORS::CONTROL_OUTLINE);

	// render scroll L and R
	UI_RENDER::drawRectFill(_scrollPositionL._x, _scrollPositionL._y, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y, UI_COLORS::CONTROL_FILL);
	UI_RENDER::drawRect(_scrollPositionL._x, _scrollPositionL._y, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y, UI_COLORS::CONTROL_OUTLINE);

	UI_RENDER::drawRectFill(_scrollPositionR._x, _scrollPositionR._y, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y, UI_COLORS::CONTROL_FILL);
	UI_RENDER::drawRect(_scrollPositionR._x, _scrollPositionR._y, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y, UI_COLORS::CONTROL_OUTLINE);

	// draw the logs lol
	for (size_t i = _scroll; i < std::clamp<size_t>(_scroll + UI_NOTIFICATIONS::LOG_COUNT, 0, _notifications.size()); i++) {

		const auto& curNotification = _notifications.at(i);
		const auto endPos = POINT_INT(_logPosition._x + _logSize._x - UI_NOTIFICATIONS::LOG_TIME_WIDTH, _logPosition._y + (UI_NOTIFICATIONS::LOG_SIZE * (i - _scroll)) + 4);

		// text
		UI_RENDER::drawString(_logPosition._x + 8, endPos._y, UI_FONTS::WINDOW_FONT, UI_COLORS::WHITE, STRING::TRUNCATE(curNotification._text, 75));
		UI_RENDER::drawString(endPos._x + 8, endPos._y, UI_FONTS::WINDOW_FONT, UI_COLORS::WHITE, curNotification._creationTime);

		// type
		switch (curNotification._type)
		{
		case CORE::NOTIFICATION_INFO:
			UI_RENDER::drawString(endPos._x + 8 - UI_NOTIFICATIONS::LOG_TYPE_WIDTH, endPos._y, UI_FONTS::WINDOW_FONT, UI_COLORS::WHITE, "Info");
			break;
		case CORE::NOTIFICATION_DEBUG:
			UI_RENDER::drawString(endPos._x + 8 - UI_NOTIFICATIONS::LOG_TYPE_WIDTH, endPos._y, UI_FONTS::WINDOW_FONT, UI_COLORS::LIGHT_BLUE, "Debug");
			break;
		case CORE::NOTIFICATION_WARNING:
			UI_RENDER::drawString(endPos._x + 8 - UI_NOTIFICATIONS::LOG_TYPE_WIDTH, endPos._y, UI_FONTS::WINDOW_FONT, UI_COLORS::YELLOW, "Warning");
			break;
		case CORE::NOTIFICATION_ERROR:
			UI_RENDER::drawString(endPos._x + 8 - UI_NOTIFICATIONS::LOG_TYPE_WIDTH, endPos._y, UI_FONTS::WINDOW_FONT, UI_COLORS::RED, "Error");
			break;
		}
	}

	// render arrow and page count
	UI_RENDER::drawString(_scrollArrowPositionL._x, _scrollArrowPositionL._y, UI_FONTS::CONTROL_FONT, _curPage <= 0 ? UI_COLORS::CONFIG_TAB_FILL2 : UI_COLORS::TEXT_TEXT_LABEL, "prev", E_FONT_FLAGS::FONT_CENTER_X | E_FONT_FLAGS::FONT_CENTER_Y);
	UI_RENDER::drawString(_scrollArrowPositionR._x, _scrollArrowPositionR._y, UI_FONTS::CONTROL_FONT, _curPage >= _numPages ? UI_COLORS::CONFIG_TAB_FILL2 : UI_COLORS::TEXT_TEXT_LABEL, "next", E_FONT_FLAGS::FONT_CENTER_X | E_FONT_FLAGS::FONT_CENTER_Y);

	UI_RENDER::drawString(_scrollPositionL._x + (_logSize._x / 2), _scrollPositionL._y + (UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y / 2), UI_FONTS::CONTROL_FONT, UI_COLORS::WHITE, _pageCount, E_FONT_FLAGS::FONT_CENTER_X | E_FONT_FLAGS::FONT_CENTER_Y);
}

void Notifications_Form::update() {

	UI_BaseForm::update();

	_logPosition = POINT_INT(_controlPosition._x + UI_CONTROL::GROUPBOX_PADDING._x, _controlPosition._y + UI_CONTROL::GROUPBOX_PADDING._y);
	_logSize = POINT_INT(_controlSize._x - (UI_CONTROL::GROUPBOX_PADDING._x * 2), (UI_NOTIFICATIONS::LOG_COUNT * UI_NOTIFICATIONS::LOG_SIZE));

	_scrollPositionL = POINT_INT(_logPosition._x, _logPosition._y + _logSize._y + UI_CONTROL::GROUPBOX_PADDING._y);
	_scrollArrowPositionL = POINT_INT(_scrollPositionL._x + (UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x / 2), _scrollPositionL._y + (UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y / 2));

	_scrollPositionR = POINT_INT(_logPosition._x + _logSize._x - UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x, _scrollPositionL._y);
	_scrollArrowPositionR = POINT_INT(_scrollPositionR._x + (UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x / 2), _scrollPositionR._y + (UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y / 2));
}

void Notifications_Form::input() {

	UI_BaseForm::input();

	// handle scroll clicks
	if (UI_INPUT::mouseInBounds(_scrollPositionL._x, _scrollPositionL._y, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y)) {

		if (UI_INPUT::isPressed(VK_LBUTTON) && _curPage > 0) {
			_pageCount = fmt::format("{} / {}", --_curPage, _numPages);
			_scroll = _curPage * UI_NOTIFICATIONS::LOG_COUNT;
		}
	}
	else if (UI_INPUT::mouseInBounds(_scrollPositionR._x, _scrollPositionR._y, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._x, UI_NOTIFICATIONS::SCROLL_BUTTON_SIZE._y)) {

		if (UI_INPUT::isPressed(VK_LBUTTON) && _curPage < _numPages) {
			_pageCount = fmt::format("{} / {}", ++_curPage, _numPages);
			_scroll = _curPage * UI_NOTIFICATIONS::LOG_COUNT;
		}
	}
}

void Notifications_Form::addNotification(const T_Notification& notification) {

	_notifications.emplace_front(notification);

	if (_notifications.size() > UI_NOTIFICATIONS::MAX_NOTIFICATIONS) {
		_notifications.pop_back();
	}

	// update notification count
	_numPages = static_cast<size_t>(std::floor(_notifications.size() / UI_NOTIFICATIONS::LOG_COUNT));
	_pageCount = fmt::format("{} / {}", _curPage, _numPages);
}

const std::deque<T_Notification>* Notifications_Form::getNotifications() const {
	return &_notifications;
}