#pragma once
#include <iostream>
#include <vector>

class Base64{
public:
	static std::string encode(std::vector<char>& data);
	static std::vector<char> decode(std::string& data);
};
