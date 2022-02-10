#include "JS_Man.hpp"
#include <functional>
#include <emscripten.h>

JS_Man* GLOBAL_ACCESS = new JS_Man();

class uniqueVarHelper{
public:
	static inline uint32_t currentID = 1;//starting at 0 doesn't work for some reason
	static inline uint32_t getUniqueID(){
		return(currentID++);
	}
};

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
	JS_Man_construct();
}

JS_Man::~JS_Man(){
	for(auto& i : vars){
		freeVar(i);
	}
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
	}else{
		std::cerr<<"Failed to free var with ID: "<<get<<" as it does not exist."<<std::endl;
		return(false);
	}
}

bool JS_Man::freeVar(std::string& name){
	uint32_t strHash = std::hash<std::string>{}(name);
	return(freeVar(strHash));
}

uint32_t getRandom(){
	return(uniqueVarHelper::getUniqueID());
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

EM_JS(void, JS_Man_evalJS, (const char* code), {
	let func = new Function(UTF8ToString(code));
	func();
});

void JS_Man::evalJS(std::string& code){
	JS_Man_evalJS(code.c_str());
}
