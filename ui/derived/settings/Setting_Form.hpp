#pragma once

#include "../../interfaces/UI_BaseForm.hpp"

namespace CORE {

	namespace UI_SETTINGS {

		constexpr POINT_INT FORM_SIZE = { 400, 300 };

	}

	class Settings_Form : public UI_BaseForm {
	public:
		Settings_Form();
		~Settings_Form();

		void render();
		void update();
		void input();
	private:

	};
}