#pragma once

// credits https://github.com/rollraw/qo0-base/blob/master/base/core/config.h

#include "../singleton.hpp"
#include "../macos.hpp"

#include "../type/Color.hpp"
#include "../cryptography/fn1v.hpp"

#include <any>
#include <vector>
#include <string>
#include <filesystem>

#define C_ADD_VARIABLE( Type, szName, pDefault ) const std::uint32_t szName = CORE::C_Config::get().addVar<Type>(CORE::C_FN1V::getCT(#szName), CORE::C_FN1V::getCT(#Type), pDefault);
#define C_ADD_VARIABLE_VECTOR( Type, uSize, szName, pDefault ) const std::uint32_t szName = CORE::C_Config::get().addVar<std::vector<Type>>(CORE::C_FN1V::getCT(#szName), CORE::C_FN1V::getCT("std::vector<" #Type ">"), FILLED_VECTOR<Type, uSize>(pDefault));

namespace CORE {

	constexpr const char* CONFIG_EXTENSION = ".abc";

	// actually used to specify how to save the variable in the json
	// if NONE, dont save variable

	struct T_Variable {

		T_Variable(hash_t name, hash_t type, std::any&& defaultVal) :
			_name(name),
			_type(type),
			_var(std::move(defaultVal)) {

		}

		template<typename T>
		T& get() {
			return *static_cast<T*>(std::any_cast<T>(&_var));
		}

		template<typename T>
		void set(T value) {
			_var.emplace<T>(value);
		}

		hash_t _name{};
		hash_t _type{};
		std::any _var{};
	};

	class C_Config : public Singleton<C_Config> {
	public:
		C_Config();
		~C_Config();

		void setup(const std::string& folder);
		void fetchConfigs();
		void remove(size_t filenameIndex);
		void load(size_t filenameIndex);
		void save(const std::string& configName);
		size_t getVarIndex(const hash_t name);

		template <typename T>
		T& getVar(const std::uint32_t nIndex) {
			return _vars.at(nIndex).get<T>();
		}

		/* add new configuration variable to massive, and return index of it */
		template <typename T>
		std::uint32_t addVar(hash_t name, hash_t type, T defaultVal) {
			_vars.emplace_back(name, type, std::make_any<T>(defaultVal));
			return _vars.size() - 1U;
		}

		static std::filesystem::path getConfigDirectory(const std::string& folderName);
	private:
		std::string _folder_name{};
		std::filesystem::path _directory{};

		std::vector<T_Variable> _vars{};
		std::vector<std::string> _configs{};
	};
}