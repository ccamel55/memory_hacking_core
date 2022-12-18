#pragma once

#include "../singleton.hpp"

#include "interfaces/UI_FormElement.hpp"
#include "interfaces/UI_TextElement.hpp"

#include "../threading/TrippleBuffer.hpp"

#include <algorithm>

namespace CORE {

	struct T_UI_Data {

	};

	class UI_MainForm : public UI_FormElement {
	public:
		UI_MainForm();
		~UI_MainForm();

		void onRender(bool open) override;
		void onUpdate() override;
		void* getDataBuffer() override;
		void addChild(const std::shared_ptr<UI_BaseElement>& c) override;
		bool getOpen();
	public:
		void addTextUI(const std::shared_ptr<UI_TextElement>& t);
		void setOpen(bool b);
	private:
		bool _open;

		T_UI_Data _dataBuffer;
		std::shared_ptr<UI_TextElement> _textUI;
	};

	class C_UI : public Singleton<C_UI> {
	public:
		C_UI();
		~C_UI();

		void draw();
		void input();
		bool isOpen();

		T_UI_Data* getDataBuffer();
	private:
		std::shared_ptr<UI_MainForm> _mainForm;
	};
}