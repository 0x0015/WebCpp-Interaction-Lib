#pragma once
#include <iostream>
#include <vector>
#include <set>

class JS_Man{
public:
	JS_Man();
	~JS_Man();
	std::set<uint32_t> vars;
	uint32_t allocateVar(std::string& name);
	uint32_t allocateVar();
	bool freeVar(std::string& name);
	bool freeVar(uint32_t get);
};

extern JS_Man* GLOBAL_ACCESS;
