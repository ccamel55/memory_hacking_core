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
		POINT_INT _pos;
		POINT_INT _size;

		bool _isFocused;
		bool _blocking;

		std::shared_ptr<UI_BaseElement> _parent;
	};
}