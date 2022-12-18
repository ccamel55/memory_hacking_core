#pragma once

#include "../../interfaces/UI_FormElement.hpp"

namespace CORE {

	class Config_Form : public UI_FormElement {
	public:
		Config_Form();
		~Config_Form();

		void onRender(bool open) override;
		void onUpdate() override;
		void addChild(const std::shared_ptr<UI_BaseElement>& c) override;
		void* getDataBuffer() override;
	private:

	};
}