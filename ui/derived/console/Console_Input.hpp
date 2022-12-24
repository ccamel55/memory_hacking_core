#pragma once

#include <map>
#include "../../form_common/Form_TextInput.hpp"

namespace CORE {

	struct T_ConsoleVar;

	class Console_Input : public Form_TextInput {
	public:
		Console_Input(const std::map<std::string_view, T_ConsoleVar>* cmds);
		~Console_Input();

		void render();
		void update();
		void input();

		const std::string& getInput() const;
		void clear();
	protected:
		POINT_INT _suggestionPos{};
		std::string _curInput{};

		bool _useHistory{};

		int _historyIndex{};
		int _suggestedIndex{};

		std::vector<std::string> _inputHistory{};
		std::vector<std::string> _suggestedInputs{};

		const std::map<std::string_view, T_ConsoleVar>* _commandsPtr{};
	};
}