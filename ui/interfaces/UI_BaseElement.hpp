#pragma once

#include "../definitions/UI_Definitions.hpp"
#include "../definitions/UI_Wrapper.hpp"

#include <string>
#include <memory>
#include <exception>

namespace CORE {

	class UI_BaseElement : public std::enable_shared_from_this<UI_BaseElement> {
	public:
		/* used to draw elements */
		virtual void render() = 0;

		/* used to update state of elements */
		virtual void update() = 0;

		/* used to process input within elements */
		virtual void input() = 0;
	public:
		void setName(const std::string& name);
		const std::string& getName() const;

		void setType(size_t type);
		size_t getType();

		void setSize(const POINT_INT& size);
		const POINT_INT& getSize() const;

		void setPosition(const POINT_INT& position);
		const POINT_INT& getPosition() const;

		size_t& getFlags();
	protected:
		std::string _name{};

		size_t _type{};
		size_t _flags{};

		POINT_INT _size{};
		POINT_INT _position{};
	};
}