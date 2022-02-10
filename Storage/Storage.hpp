#pragma once
#include <iostream>

class Storage{
	static void saveData(std::string name, std::vector<char>& data);
	static std::vector<char> getData(std::string name);
	static void deleteData(std::string name);
};
