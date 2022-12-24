#pragma once

#include <map>
#include "../../interfaces/UI_BaseForm.hpp"

#include "Console_Input.hpp"
#include "Console_Log.hpp"

namespace CORE {

	namespace UI_CONSOLE {

		constexpr POINT_INT FORM_SIZE = { 500, 340 };

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

		std::string_view _name{};
		std::string_view _description{};

		E_CONSOLE_VAR_TYPE _type{};
	
		union U_DATA {
			
			struct T_DATA_INT {
				int _min{};
				int _max{};
				int* _data{};
			}_int;

			struct T_DATA_FLOAT {
				float _min{};
				float _max{};
				float* _data{};
			}_float;

		} _data{};

		std::function<void()> _callback{};
	};

	class Console_Form : public UI_BaseForm {
	public:
		Console_Form();
		~Console_Form();

		void render();
		void update();
		void input();

		void addCommand(std::string_view name, std::string_view description);
		void setData(std::string_view name, uint32_t var, float min, float max);
		void setData(std::string_view name, uint32_t var, int min, int max);
		void setData(std::string_view name, std::function<void()> callback);
	protected:
		size_t _selectorIdx{};

		std::shared_ptr<Console_Input> _inputBox{};
		std::shared_ptr<Console_Log> _logBox{};

		std::map<std::string_view, T_ConsoleVar> _commands{};
	}; 
}