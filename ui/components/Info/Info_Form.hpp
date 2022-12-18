#pragma once

#include "../../interfaces/UI_FormElement.hpp"

namespace CORE {

	class Info_Form : public UI_FormElement {
	public:
		Info_Form();
		~Info_Form();

		void onRender(bool open) override;
		void onUpdate() override;
		void addChild(const std::shared_ptr<UI_BaseElement>& c) override;
		void* getDataBuffer() override;
	private:

	};
}