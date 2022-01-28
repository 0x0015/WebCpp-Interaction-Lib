#pragma once
#include <iostream>
#include <memory>
#include "../property.hpp"

class Element{
public:
	uint32_t id = 0;
	std::string dom_class;
	std::string dom_id;
	bool dom_hidden;
	static std::shared_ptr<Element> getById(std::string id);
	static std::vector<std::shared_ptr<Element>> getByClassName(std::string classname);
	std::string getValue();
	void setValue(std::string newVal);
	property<std::string> value = {
		([&]() -> std::string {
			return(getValue());
		 }),
		([&](std::string& i){
			setValue(i);
		 })
	};
	Element();
	Element(uint32_t i);
	~Element();
};
