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

EM_JS(bool, Element_getDisabled, (uint32_t hash), {
	return(JS_Man["A" + hash].disabled);
});

bool Element::get_dom_disabled(){
	return(Element_getDisabled(id));
}

EM_JS(void, Element_setDisabled, (uint32_t hash, bool value), {
	JS_Man["A" + hash].disabled = value;
});

void Element::set_dom_disabled(bool newVal){
	Element_setDisabled(id, newVal);
}

EM_JS(bool, Element_getChecked, (uint32_t hash), {
	return(JS_Man["A" + hash].checked);
});

bool Element::get_dom_checked(){
	return(Element_getChecked(id));
}

EM_JS(void, Element_setChecked, (uint32_t hash, bool value), {
	JS_Man["A" + hash].checked = value;
});

void Element::set_dom_checked(bool newVal){
	Element_setChecked(id, newVal);
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

EM_JS(void, Element_AssignChildElement, (uint32_t hash, uint32_t newHash, uint32_t index), {
	JS_Man["A" + newHash] = JS_Man["A" + hash].children[index];
});

std::shared_ptr<Element> Element::get_dom_child(int index){
	std::shared_ptr<Element> output = std::make_shared<Element>();
	Element_AssignChildElement(id, output->id, index);
	return(output);
}

EM_JS(unsigned int, Element_getChildCount, (uint32_t hash), {
	return(JS_Man["A" + hash].childElementCount);
});

unsigned int Element::get_dom_childCount(){
	return(Element_getChildCount(id));
}

EM_JS(void, Element_setStyle, (uint32_t hash, const char* whatStyle, const char* value), {
	JS_Man["A" + hash].style[UTF8ToString(whatStyle)] = UTF8ToString(value);
});

void Element::set_dom_style(std::string style, std::string value){
	Element_setStyle(id, style.c_str(), value.c_str());
}

EM_JS(unsigned int, Element_getStyleLen, (uint32_t hash, const char* whatStyle), {
	return(lengthBytesUTF8(JS_Man["A" + hash].style[UTF8ToString(whatStyle)]));
});

EM_JS(void, Element_getStyle, (uint32_t hash, const char* whatStyle, char* str, uint32_t len), {
	stringToUTF8(JS_Man["A" + hash].style[UTF8ToString(whatStyle)], str, len+1);
});

std::string Element::get_dom_style(std::string style){
	std::string output;
	unsigned int maxLength = Element_getStyleLen(id, style.c_str());
	output.resize(maxLength);
	Element_getStyle(id, style.c_str(), output.data(), maxLength);
	output.shrink_to_fit();
	return(output);
}
