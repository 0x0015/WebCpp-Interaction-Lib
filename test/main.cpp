#include <iostream>
#include "../DOM.hpp"

void printTest(){
	std::cout<<"printed Test!"<<std::endl;
}

int main(){
	std::cout<<"Hello World"<<std::endl;
	std::shared_ptr<Element> input = Element::getById("in");
	std::cout<<"Input value: "<<(std::string)input->dom_value<<"/"<<input->get_dom_value()<<" id: "<<input->id<<std::endl;
	input->dom_value = "New value";
	std::shared_ptr<Element> button = Element::getById("button");
	button->dom_onclick = printTest;
	std::shared_ptr<Element> button2 = Element::getById("button2");
	std::function<void()> b2oncl = button2->dom_onclick;
	b2oncl();
	std::vector<std::shared_ptr<Element>> buttons = Element::getByClassName("abutton");
	for(auto& i : buttons){
		i->dom_innerHTML = "haha new value";
	}
}
