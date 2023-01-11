#pragma once

#include "../../interfaces/UI_BaseForm.hpp"
#include "Notification_Widget.hpp"

#include <chrono>
#include <deque>

namespace CORE {

	namespace UI_NOTIFICATIONS {

		constexpr SIZE_T MAX_NOTIFICATIONS = 90;

		constexpr SIZE_T LOG_COUNT = 10;
		constexpr SIZE_T LOG_SIZE = 25;
		constexpr SIZE_T LOG_TIME_WIDTH = 90;
		constexpr SIZE_T LOG_TYPE_WIDTH = 70;

		constexpr SIZE_T WIDGET_LOG_COUNT = 8;
		constexpr SIZE_T WIDGET_LOG_SIZE = 15;

		constexpr POINT_INT SCROLL_BUTTON_SIZE = { 50, 20 };
		constexpr POINT_INT FORM_SIZE = { 700, (LOG_COUNT * LOG_SIZE) + (UI_CONTROL::GROUPBOX_PADDING._y * 5) + SCROLL_BUTTON_SIZE._y + 6 };
	}

	enum E_NOTIFICATION_TYPE : size_t {

		NOTIFICATION_INFO,
		NOTIFICATION_WARNING,
		NOTIFICATION_ERROR,
		NOTIFICATION_DEBUG,
	};

	struct T_Notification {

		std::string _text{};
		std::string _creationTime{};
		E_NOTIFICATION_TYPE _type{};
	};

	class Notifications_Form : public UI_BaseForm {
	public:
		Notifications_Form();
		~Notifications_Form();

		void render();
		void update();
		void input();

		void addNotification(const T_Notification& notification);
		const std::deque<T_Notification>* getNotifications() const;
	private:
		std::deque<T_Notification> _notifications{};
	
		POINT_INT _logPosition{};
		POINT_INT _logSize{};

		POINT_INT _scrollPositionL{};
		POINT_INT _scrollArrowPositionL{};

		POINT_INT _scrollPositionR{};
		POINT_INT _scrollArrowPositionR{};

		std::string _pageCount{};

		size_t _numPages{};
		size_t _curPage{};
		size_t _scroll{};
	};
}
