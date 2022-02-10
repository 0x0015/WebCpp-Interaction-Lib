#include "Storage.hpp"
#include "Base64.hpp"
#include <functional>
#include <emscripten.h>

EM_JS(void, Storage_getData, (uint32_t hash, char* id, uint32_t length), {
	stringToUTF8(localStorage["A" + hash], id, length);
});

EM_JS(unsigned int,  Storage_getDataLen, (uint32_t hash), {
	return(lengthBytesUTF8(localStorage["A" + hash]));
});

std::vector<char> Storage::getData(std::string name){
	uint32_t nameHash = std::hash<std::string>{}(name);
	std::string preDecoded;
	unsigned int maxLength = Storage_getDataLen(nameHash);
	preDecoded.resize(maxLength);
	Storage_getData(nameHash, preDecoded.data(), maxLength);
	std::vector<char> output = Base64::decode(preDecoded);
	return(output);
}

EM_JS(void, Storage_saveData, (uint32_t hash, const char* id), {
	localStorage["A" + hash] = UTF8ToString(id);
});

void Storage::saveData(std::string name, std::vector<char>& data){
	uint32_t nameHash = std::hash<std::string>{}(name);
	std::string newData = Base64::encode(data);
	Storage_saveData(nameHash, newData.c_str());
}

EM_JS(void, Storage_deleteData, (uint32_t hash), {
	delete localStorage["A" + hash];
});

void Storage::deleteData(std::string name){
	uint32_t nameHash = std::hash<std::string>{}(name);
	Storage_deleteData(nameHash);
}
