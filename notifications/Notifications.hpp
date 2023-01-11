#pragma once

#include "../rendering/RenderImpl.hpp"
#include "../singleton.hpp"

namespace CORE {

	class C_Notifications : public Singleton<C_Notifications> {
	public:
		void render();
	};
}