#pragma once

#include "../../interfaces/UI_BaseControl.hpp"

namespace CORE {

	class Text_Drawgroup;

	class Text_BaseControl : public UI_BaseControl {
	public:
		const POINT_INT& getDrawGroupPosition();
		void setDrawGroupPosition(const POINT_INT& drawGroupPosition);

		std::shared_ptr<Text_Drawgroup> getDrawGroup();
		virtual std::shared_ptr<Text_Drawgroup> addDrawgroup();
	protected:

		POINT_INT _drawGroupPosition{};
		std::shared_ptr<Text_Drawgroup> _drawGroup{};
	};
}