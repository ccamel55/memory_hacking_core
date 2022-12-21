#pragma once

#include <map>

#include "../../interfaces/UI_FormElement.hpp"

namespace CORE {

	namespace CONSOLE_CONSTANTS {

		// size of input box
		constexpr POINT_INT INPUT_BOX_SIZE = { 0, 20 };

	}

	enum E_CONSOLE_VAR_TYPE : uint8_t {
		VAR_INTERNAL, // used for help etc.
		VAR_CALLBACK,
		VAR_FLOAT,
		VAR_INT,
	};

	struct T_ConsoleVar {

		T_ConsoleVar(E_CONSOLE_VAR_TYPE type, std::string_view name, std::string_view description, float min = 0.f, float max = 0.f, float defaultVal = 0.f, void* varPtr = nullptr) : 
			_name(name),
			_description(description),
			_min(min),
			_max(max),
			_default(defaultVal),
			_varPtr(varPtr),
			_type(type) {

		}

		std::string_view _name{};
		std::string_view _description{};

		float _min{}; // min val
		float _max{}; // max val

		float _default{};
		E_CONSOLE_VAR_TYPE _type{};

		// can be callback, can be pointer to int, etc.
		void* _varPtr{};
	};

	class Console_Form : public UI_FormElement {
	public:
		Console_Form(int w, int h);
		~Console_Form();

		void onRender(bool open) override;
		void onUpdate() override;
		void* getDataBuffer() override;
		void addChild(const std::shared_ptr<UI_BaseElement>& c) override;
		void addCommand(std::string_view name, T_ConsoleVar var);
	private:
		std::map<std::string_view, T_ConsoleVar> _commands{};
	};
}