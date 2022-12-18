#pragma once

#include "../definitions.hpp"

namespace CORE {

	class UI_BaseElement : public std::enable_shared_from_this<UI_BaseElement> {
	public:
		UI_BaseElement();
		~UI_BaseElement();

		virtual void onRender(bool open) = 0;
		virtual void onUpdate() = 0;

		virtual void* getDataBuffer() = 0;
	public:
		bool isBlocking();
		void setBlocking(bool b);

		bool isFocused();
		void setIsFocused(bool b);

		POINT_INT& getPos();
		void setPos(POINT_INT& p);

		POINT_INT& getSize();
		void setSize(POINT_INT& s);

		std::shared_ptr<UI_BaseElement>& getParent();
		void setParent(const std::shared_ptr<UI_BaseElement>& p);
	protected:
		POINT_INT m_cPos;
		POINT_INT m_cSize;

		bool m_bIsFocused;
		bool m_bBlocking;

		std::shared_ptr<UI_BaseElement> m_pParent;
	};
}