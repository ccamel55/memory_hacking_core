#pragma once

#include "../../interfaces/UI_FormElement.hpp"

namespace CORE {

	struct T_Console_Command {

	};

	class Console_Form : public UI_FormElement {
	public:
		Console_Form(int w, int h);
		~Console_Form();

		void onRender(bool open) override;
		void onUpdate() override;
		void* getDataBuffer() override;
		void addChild(const std::shared_ptr<UI_BaseElement>& c) override;
	private:

	};
}