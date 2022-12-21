#pragma once

#include "../../interfaces/UI_ControlElement.hpp"

namespace CORE {

	class Common_GroupBox : public UI_ControlElement {
	public:
		Common_GroupBox(bool tab = false);
		~Common_GroupBox();

		void onRender(bool open) override;
		void onUpdate() override;
		void* getDataBuffer() override;

		void addChild(const std::shared_ptr<UI_ControlElement>& c);
	private:
		bool _isTab{}; // tab groups will have multiple groupboxes, only draw outline if not tab

		POINT_INT _controlPos{};
		POINT_INT _drawPos{};

		POINT_INT _controlOffset{};
		std::vector<std::shared_ptr<UI_ControlElement>> _children{};
	};
}

