#include "Element.hpp"
#include "../JS_Access/JS_Man.hpp"
#include <emscripten.h>
#include <cstdlib>

unsigned int getRandom();//from JS_Man, but I don't want it in the header

std::unordered_map<uint32_t, std::function<void()>>* globalFunctorTable = new std::unordered_map<uint32_t, std::function<void()>>();

Element::Element(){
	id = GLOBAL_ACCESS->allocateVar();
}

Element::Element(uint32_t i){
	id = i;
}

Element::~Element(){
	if(id != 0){
		GLOBAL_ACCESS->freeVar(id);
	}
}

EM_JS(void, Element_getById, (uint32_t hash, const char* id), {
	JS_Man["A" + hash] = document.getElementById(UTF8ToString(id));
});

std::shared_ptr<Element> Element::getById(std::string id){
	std::shared_ptr<Element> newElm = std::make_shared<Element>();
	Element_getById(newElm->id, id.c_str());
	return(newElm);
}

EM_JS(void, Element_getVal, (uint32_t hash, char* id, uint32_t length), {
	stringToUTF8(JS_Man["A" + hash].value, id, length+1);
});

EM_JS(unsigned int, Element_getValLen, (uint32_t hash), {
	return(lengthBytesUTF8(JS_Man["A" + hash].value));
});

std::string Element::get_dom_value(){
	std::string output;
	unsigned int maxLength = Element_getValLen(id);
	output.resize(maxLength);
	Element_getVal(id, output.data(), maxLength);
	output.shrink_to_fit();
	return(output);
}

EM_JS(void, Element_setVal, (uint32_t hash, const char* id), {
	JS_Man["A" + hash].value = UTF8ToString(id);
});

void Element::set_dom_value(std::string newVal){
	Element_setVal(id, newVal.c_str());
}

EM_JS(void, Element_getInnerHTML, (uint32_t hash, char* id, uint32_t length), {
	stringToUTF8(JS_Man["A" + hash].innerHTML, id, length+1);
});

EM_JS(unsigned int, Element_getInnerHTMLLen, (uint32_t hash), {
	return(lengthBytesUTF8(JS_Man["A" + hash].innerHTML));
});

std::string Element::get_dom_innerHtml(){
	std::string output;
	unsigned int maxLength = Element_getInnerHTMLLen(id);
	output.resize(maxLength);
	Element_getInnerHTML(id, output.data(), maxLength);
	output.shrink_to_fit();
	return(output);
}

EM_JS(void, Element_setInnerHTML, (uint32_t hash, const char* id), {
	JS_Man["A" + hash].innerHTML = UTF8ToString(id);
});

void Element::set_dom_innerHTML(std::string newVal){
	Element_setInnerHTML(id, newVal.c_str());
}


extern "C" {
	void EMSCRIPTEN_KEEPALIVE callStdFunc(uint32_t hash);
}

void callStdFunc(uint32_t hash){
	(*globalFunctorTable)[hash]();
}

EM_JS(void, Element_setOnclick, (uint32_t hash, uint32_t funcHash), {
	JS_Man["A" + hash].onclick = function(){
		var callStdFuncWrap = Module.cwrap('callStdFunc', '', 'number');
		callStdFuncWrap(funcHash);
	}
});

void Element::set_dom_onclick(std::function<void()> func){
	uint32_t funcHash = getRandom();//really, just needs to be unique
	(*globalFunctorTable)[funcHash] = func;//make sure its stored somewhere(by value) so it won't leave memory.
	dom_onclick_hash = funcHash;
	Element_setOnclick(id, funcHash);
}

EM_JS(void, Element_callOnclick, (uint32_t hash),{
	JS_Man["A" + hash].onclick();
});

std::function<void()> Element::get_dom_onclick(){
	std::function<void()> output = [this](){
		Element_callOnclick(id);
	};
	return(output);
}

EM_JS(unsigned int, Element_getClassNameLength, (uint32_t hash, const char* classname), {
	JS_Man["A" + hash] = document.getElementsByClassName(UTF8ToString(classname));
	return(JS_Man["A" + hash].length);
});

EM_JS(void, Element_AssignListElement, (uint32_t hash, uint32_t newHash, uint32_t index), {
	JS_Man["A" + newHash] = JS_Man["A" + hash][index];
});

std::vector<std::shared_ptr<Element>> Element::getByClassName(std::string classname){
	uint32_t tempID = GLOBAL_ACCESS->allocateVar();
	unsigned int length = Element_getClassNameLength(tempID, classname.c_str());
	std::vector<std::shared_ptr<Element>> output;
	for(int i=0;i<length;i++){
		std::shared_ptr<Element> newElm = std::make_shared<Element>();
		Element_AssignListElement(tempID, newElm->id, i);
		output.push_back(newElm);
	}
	GLOBAL_ACCESS->freeVar(tempID);
	return(output);
}
