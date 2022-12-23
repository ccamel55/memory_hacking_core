#include "Config.hpp"

#include <shlobj.h>

#include <exception>
#include <fstream>

#include "../deps/json/single_include/nlohmann/json.hpp"

using namespace CORE;

C_Config::C_Config() {

}

C_Config::~C_Config() {

}

void C_Config::setup(const std::string& folder) {

	_folder_name = folder;
	_directory = getConfigDirectory(_folder_name);

	fetchConfigs();
}

void C_Config::fetchConfigs() {

	_configs.clear();

	for (const auto& it : std::filesystem::directory_iterator(_directory)) {

		if (it.path().filename().extension() == CONFIG_EXTENSION) {
			_configs.push_back(it.path().filename().string());
		}
	}
}

void C_Config::remove(size_t filenameIndex) {

	const auto& fileName = _configs.at(filenameIndex);
	const auto filePath = std::filesystem::path(_directory / fileName).string();

	if (!std::filesystem::remove(filePath)) {
		throw std::exception("could not remove config");
	}

	_configs.erase(_configs.cbegin() + static_cast<std::ptrdiff_t>(filenameIndex));
}

void C_Config::load(size_t filenameIndex) {

	const auto& fileName = _configs.at(filenameIndex);
	const auto filePath = std::filesystem::path(_directory / fileName).string();

	std::ifstream inputFileStream(filePath, std::ios::in);

	if (!inputFileStream.good()) {
		throw std::exception("could not open file");
	}

	const auto config = nlohmann::json::parse(inputFileStream, nullptr, false);

	if (config.is_discarded()) {
		throw std::exception("could not open file");
	}
		
	inputFileStream.close();

	for (const auto& variable : config) {
		
		const auto varIdx = getVarIndex(variable["name-id"].get<hash_t>());

		if (varIdx == SIZE_MAX) {
			continue;
		}

		auto& entry = _vars.at(varIdx);

		switch (variable["type-id"].get<hash_t>())
		{
		case C_FN1V::getCT("bool"):
		{
			entry.set<bool>(variable["value"].get<bool>());
			break;
		}
		case C_FN1V::getCT("float"):
		{
			entry.set<float>(variable["value"].get<float>());
			break;
		}
		case C_FN1V::getCT("int"):
		{
			entry.set<int>(variable["value"].get<int>());
			break;
		}
		case C_FN1V::getCT("std::string"):
		{
			entry.set<std::string>(variable["value"].get<std::string>());
			break;
		}
		case C_FN1V::getCT("Color"):
		{
			const nlohmann::json vector = nlohmann::json::parse(variable["value"].get<std::string>());

			entry.set<Color>(Color(
				vector.at(0).get<unsigned int>(),
				vector.at(1).get<unsigned int>(),
				vector.at(2).get<unsigned int>(),
				vector.at(3).get<unsigned int>()
			));

			break;
		}
		case C_FN1V::getCT("std::vector<bool>"):
		{
			const nlohmann::json vector = nlohmann::json::parse(variable["value"].get<std::string>());
			auto& vecBools = entry.get<std::vector<bool>>();

			for (std::size_t i = 0U; i < vector.size(); i++) {
		
				if (i < vecBools.size()) {
					vecBools.at(i) = vector.at(i).get<bool>();
				}
			}

			break;
		}
		case C_FN1V::getCT("std::vector<int>"):
		{
			const nlohmann::json vector = nlohmann::json::parse(variable["value"].get<std::string>());
			auto& vecInts = entry.get<std::vector<int>>();

			for (std::size_t i = 0U; i < vector.size(); i++) {

				if (i < vecInts.size()) {
					vecInts.at(i) = vector.at(i).get<int>();
				}
			}

			break;
		}
		case C_FN1V::getCT("std::vector<float>"):
		{
			const nlohmann::json vector = nlohmann::json::parse(variable["value"].get<std::string>());
			auto& vecFloats = entry.get<std::vector<float>>();

			for (std::size_t i = 0U; i < vector.size(); i++) {

				if (i < vecFloats.size()) {
					vecFloats.at(i) = vector.at(i).get<float>();
				}		
			}

			break;
		}
		default:
			break;
		}
	}
}

void C_Config::save(const std::string& configName) {

	nlohmann::json config{};

	for (auto& variable : _vars) {

		nlohmann::json entry{};

		entry["name-id"] = variable._name;
		entry["type-id"] = variable._type;

		switch (variable._type)
		{
		case C_FN1V::getCT("int"):
		{
			entry["value"] = variable.get<int>();
			break;
		}
		case C_FN1V::getCT("float"):
		{
			entry["value"] = variable.get<float>();
			break;
		}
		case C_FN1V::getCT("bool"):
		{
			entry["value"] = variable.get<bool>();
			break;
		}
		case C_FN1V::getCT("std::string"):
		{
			entry["value"] = variable.get<std::string>();
			break;
		}
		case C_FN1V::getCT("Color"):
		{
			const auto& colVariable = variable.get<Color>();

			nlohmann::json sub = { };

			sub.push_back(colVariable._r);
			sub.push_back(colVariable._g);
			sub.push_back(colVariable._b);
			sub.push_back(colVariable._a);

			entry["value"] = sub.dump();
			break;
		}
		case C_FN1V::getCT("std::vector<bool>"):
		{
			const auto& vecBools = variable.get<std::vector<bool>>();

			nlohmann::json sub = { };

			for (const auto&& bValue : vecBools) {
				sub.push_back(static_cast<bool>(bValue));
			}
		
			entry["value"] = sub.dump();
			break;
		}
		case C_FN1V::getCT("std::vector<int>"):
		{
			const auto& vecInts = variable.get<std::vector<int>>();

			nlohmann::json sub = { };

			for (const auto& iValue : vecInts) {
				sub.push_back(iValue);
			}
	
			entry["value"] = sub.dump();
			break;
		}
		case C_FN1V::getCT("std::vector<float>"):
		{
			const auto& vecFloats = variable.get<std::vector<float>>();

			nlohmann::json sub = { };

			for (const auto& flValue : vecFloats) {
				sub.push_back(flValue);
			}
		
			entry["value"] = sub.dump();
			break;
		}
		default:
			break;
		}

		config.push_back(entry);
	}

	std::filesystem::path configPath(configName);

	if (configPath.extension() != CONFIG_EXTENSION) {
		configPath.replace_extension(CONFIG_EXTENSION);
	}

	const auto filePath = std::filesystem::path(_directory / configPath).string();
	std::ofstream outFileStream(filePath, std::ios::out | std::ios::trunc);

	if (!outFileStream.good()) {
		throw std::exception("could not save config");
	}

	outFileStream << config.dump(4);
	outFileStream.close();

	fetchConfigs();
}

size_t C_Config::getVarIndex(const hash_t name)
{
	for (std::size_t i = 0; i < _vars.size(); i++) {

		if (_vars.at(i)._name == name) {
			return i;
		}
	}

	return SIZE_MAX;
}

const std::vector<std::string>& C_Config::getConfigs() const {
	return _configs;
}

std::filesystem::path C_Config::getConfigDirectory(const std::string& folderName) {

	// configs will be stored in Documents folder

	PWSTR pathToDocuments{};
	std::filesystem::path ret{};

	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0UL, nullptr, &pathToDocuments))) {
		
		ret.assign(pathToDocuments);
		ret.append(folderName);
	}

	// make sure it exists
	if (!std::filesystem::is_directory(ret)) {

		if (!std::filesystem::create_directories(ret)) {
			throw std::exception("could not create directory, check permissions");
		}
	}
	 
	return ret;
}