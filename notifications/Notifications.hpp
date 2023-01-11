#pragma once

#include "../rendering/RenderImpl.hpp"
#include "../singleton.hpp"

#include "../ui/derived/notifications/Notifications_Form.hpp"

#include <chrono>
#include <vector>

namespace CORE {

	class C_Notifications : public Singleton<C_Notifications> {
	public:
		void addNotification(const std::string& name, E_NOTIFICATION_TYPE type = E_NOTIFICATION_TYPE::NOTIFICATION_INFO);
		void setNotificationWindowPtr(std::shared_ptr<Notifications_Form> notificationForm);
	private:
		std::shared_ptr<Notifications_Form> _notificationForm{};
	};
}