#pragma once
#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>
#include "../../property.hpp"
#include "../../property_sb.hpp"

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
	std::string get_dom_innerHtml();
	void set_dom_innerHTML(std::string newVal);
	property<std::string> dom_innerHTML = {
		([&]() -> std::string {
			return(get_dom_innerHtml());
		 }),
		([&](std::string& i){
			set_dom_innerHTML(i);
		 })
	};
	bool get_dom_disabled();
	void set_dom_disabled(bool newVal);
	property<bool> dom_disabled = {
		([&]() -> bool {
			return(get_dom_disabled());
		 }),
		([&](bool& i){
			set_dom_disabled(i);
		 })
	};
	bool get_dom_checked();
	void set_dom_checked(bool newVal);
	property<bool> dom_checked = {
		([&]() -> bool {
			return(get_dom_checked());
		 }),
		([&](bool& i){
			set_dom_checked(i);
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
	std::shared_ptr<Element> get_dom_child(int index);
	unsigned int get_dom_childCount();
	property_sb<std::shared_ptr<Element>, unsigned int> dom_child = {
		([&](unsigned int i) -> std::shared_ptr<Element>{
			return(get_dom_child(i));
		 })
	};
	void set_dom_style(std::string style, std::string value);
	std::string get_dom_style(std::string style);
	property_sb<property<std::string>, std::string> dom_style = {
		([&](std::string i) -> property<std::string>{
			property<std::string> returnVal = {
				([&]() -> std::string {
					return(get_dom_style(i));
				 }),
				([&](std::string& i2){
					set_dom_style(i, i2);
				 })
			};
			return(returnVal);
		 })
	};
	Element();
	Element(uint32_t i);
	~Element();
private:
	uint32_t dom_onclick_hash;
};
