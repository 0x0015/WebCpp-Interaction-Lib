#include "Element.hpp"
#include "../JS_Access/JS_Man.hpp"
#include <emscripten.h>
#include <cstdlib>

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
	stringToUTF8(JS_Man["A" + hash].value, id, length);
});

EM_JS(unsigned int, Element_getValLen, (uint32_t hash), {
	return(lengthBytesUTF8(JS_Man["A" + hash].value));
});

std::string Element::getValue(){
	std::string output;
	unsigned int maxLength = Element_getValLen(id);
	output.reserve(maxLength);
	Element_getVal(id, output.data(), maxLength);
	output.shrink_to_fit();
	return(output);
}

EM_JS(void, Element_setVal, (uint32_t hash, const char* id), {
	JS_Man["A" + hash].value = UTF8ToString(id);
});

void Element::setValue(std::string newVal){
	Element_setVal(id, newVal.c_str());
}

std::vector<std::shared_ptr<Element>> Element::getByClassName(std::string classname){
	//unimplimented so far
}
