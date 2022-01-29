#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>
#include "../property.hpp"

extern std::unordered_map<uint32_t, std::function<void()>>* globalFunctorTable;

class Element{
public:
	uint32_t id = 0;
	static std::shared_ptr<Element> getById(std::string id);
	static std::vector<std::shared_ptr<Element>> getByClassName(std::string classname);
	std::string get_dom_value();
	void set_dom_value(std::string newVal);
	property<std::string> dom_value = {
		([&]() -> std::string {
			return(get_dom_value());
		 }),
		([&](std::string& i){
			set_dom_value(i);
		 })
	};
	property<std::function<void()>> dom_onclick = {
		([&]() -> std::function<void()> {
			return(get_dom_onclick());
		 }),
		([&](std::function<void()>& i){
			set_dom_onclick(i);
		 })
	};
	std::function<void()> get_dom_onclick();
	void set_dom_onclick(std::function<void()> func);
	Element();
	Element(uint32_t i);
	~Element();
private:
	uint32_t dom_onclick_hash;
};
