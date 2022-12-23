#pragma once

#include "UI_BaseControl.hpp"

namespace CORE {

	class Text_Drawgroup;

	class UI_BaseText : public UI_BaseControl {
	public:
		void render() {};
		void update() {};
		void input() {};

		const POINT_INT& getDrawGroupPosition();
		void setDrawGroupPosition(const POINT_INT& drawGroupPosition);

		std::shared_ptr<Text_Drawgroup> getDrawGroup();
		virtual std::shared_ptr<Text_Drawgroup> addDrawgroup();
	protected:

		POINT_INT _drawGroupPosition{};
		std::shared_ptr<Text_Drawgroup> _drawGroup{};
	};
}