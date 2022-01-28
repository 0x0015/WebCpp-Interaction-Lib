#include "JS_Man.hpp"
#include <functional>
#include <emscripten.h>

JS_Man* GLOBAL_ACCESS = new JS_Man();

EM_JS(void, JS_Man_construct, (), {
	window.JS_Man = {};
});

EM_JS(void, JS_Man_allocateVar, (unsigned int hash), {
	JS_Man["A" + hash] = undefined;
});

EM_JS(bool, JS_Man_freeVar, (unsigned int hash), {
	return(delete JS_Man["A" + hash]);
});

JS_Man::JS_Man(){
	srand(time(0));
	JS_Man_construct();
}

JS_Man::~JS_Man(){
	
}

uint32_t JS_Man::allocateVar(std::string& name){
	uint32_t strHash = std::hash<std::string>{}(name);
	if(vars.count(strHash) == 1){
		return(0);
	}
	JS_Man_allocateVar(strHash);
	std::string result = "JS_Man.A" + std::to_string(strHash);
	vars.insert(strHash);
	return(strHash);
}

bool JS_Man::freeVar(uint32_t get){
	if(vars.count(get) == 1){
		uint32_t strHash = get;
		bool r = JS_Man_freeVar(strHash);
		if(r){
			vars.erase(strHash);
		}
		return(r);
	}
	return(false);
}

bool JS_Man::freeVar(std::string& name){
	uint32_t strHash = std::hash<std::string>{}(name);
	return(freeVar(strHash));
}

unsigned int getRandom(){
	return(rand());
}

uint32_t JS_Man::allocateVar(){
	unsigned int strHash = getRandom();
	if(vars.count(strHash) == 1){
		return(0);
	}
	std::string name = std::to_string(strHash);
	JS_Man_allocateVar(strHash);
	vars.insert(strHash);
	return(strHash);
}

