#include "Notifications.hpp"

using namespace CORE;

void C_Notifications::addNotification(const std::string& name, E_NOTIFICATION_TYPE type) {

	_notificationForm->addNotification(T_Notification{
		._text = name,
		._creationTime = std::format("{:%H:%M:%S}", std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now())), // using std::format because fmt::format has an msvc erro
		._type = type,
	});
}

void C_Notifications::setNotificationWindowPtr(std::shared_ptr<Notifications_Form> notificationForm) {

	// must be called on before using notifications
	_notificationForm = notificationForm;
}