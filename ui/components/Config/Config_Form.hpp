#pragma once

#include "../../interfaces/UI_FormElement.hpp"
#include "../Common/Common_GroupBox.hpp"

namespace CORE {

	namespace UI_CONFIG_CONSTANTS {

		// location of groubox selector
		constexpr POINT_INT SELECTOR_OFFSET = { -25, 0 };
		constexpr POINT_INT SELECTOR_SPACING = { 100, 0 };
		constexpr POINT_INT SELECTOR_RADIUS = { 6, 4 };

	}

	class Config_Form : public UI_FormElement {
	public:
		Config_Form();
		~Config_Form();

		void onRender(bool open) override;
		void onUpdate() override;
		void addChild(const std::shared_ptr<UI_BaseElement>& c) override;
		void* getDataBuffer() override;
		void setControlPos() override;

		void addGroupbox(const std::string& name, const std::shared_ptr<Common_GroupBox>& c);
	private:

		size_t _curGroupbox{};
		std::vector<std::string> _groupboxes{};
	};
}